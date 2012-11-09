////////////////////////////////////////////////////////
// CRAP Library
//	memoryblock.cpp
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 	Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		Contains class MemoryBlock.
//		MemoryBlock is allocationg a series of memoryblocks,
//		and uses 12-bytes frames for storing size informations.
//		It manages Memory requests und deletions.
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////
#include "control/asserts.h"
#include "memory/memorytracker.h"
#include "threading/mutex.h"
#include "threading/scopelock.h"
#include "control/converter.h"

#include "memory/memoryblock.h"

namespace crap
{
namespace memory
{

// Constructor
MemoryBlock::MemoryBlock( u64 size, i32 extensions ) :  _size(size), _extension(0), _extensionCount( extensions )
{
	// Should be at least be the size of one header
	CRAP_ASSERT_DEBUG( size > sizeof( MemoryHeader ), "Memory size too low" );
	_blockStart = malloc(size);

	//setting everything to zero
	//@TODO: Check if zero is necessary - maybe BitMask cares about it.
	memset( _blockStart, 0, size );

	// Casting initial header on blockstart and setting vars
	MemoryHeader* startInfo = static_cast<MemoryHeader*>( _blockStart );
	startInfo->accessCounter = 0;
	startInfo->allocatedSize = 0;
	startInfo->followingFreeSize = crap::control::convert<u64, u32>( size - sizeof(MemoryHeader) );

	// current size...
	_currentSize = startInfo->followingFreeSize;

	// Tracking memory if activated
	#if defined(CRAP_MEMORY_TRACKER)
	MemoryTracker::instance().addAllocatedBlock( size );
	#endif
}

//Destructor, deletes following extensions recursivley
//@TODO: Check if Mutex can be deleted in locked condition on Win and Mac
//@TODO: Is it smart to delete recursivley?
MemoryBlock::~MemoryBlock( void )
{
	SCOPE_MUTEX( &_mutex );
	delete _extension;
	free( _blockStart );

	// Tracking memory if activated
	#if defined(CRAP_MEMORY_TRACKER)
	MemoryTracker::instance().removeAllocatedBlock( _size );
	#endif
}

// Memory allocation
void* MemoryBlock::allocate( u64 space )
{
	// space + header size
	u64 spaceToAllocate = sizeof(MemoryHeader) + space;

	//if size is too big in general we extend with necessary space
	if( _size < sizeof(MemoryHeader) + spaceToAllocate )
	{
		extend( sizeof(MemoryHeader) + spaceToAllocate );
		return _extension->allocate( space ); //RETURN
	}
	if( _currentSize < spaceToAllocate )
	{
		if( _extension == 0 )
		{
			extend( _size );
		}
		return _extension->allocate( space );
	}

	//locking mutex while allocating
	SCOPE_MUTEX( &_mutex );

	//parse the first header
	MemoryHeader* allocationInfo = static_cast<MemoryHeader*>(_blockStart);

	//amount of bytes checked in following loop
	u64 checkedSize = 0;

	//parsing until enough space is found
	while ( allocationInfo->followingFreeSize < spaceToAllocate )
	{
		//we reached the end of the block
		if( checkedSize >= _size )
			break;

		//moving on to next pointer - header+alloc. space + freespace
		u32 tempSize = sizeof(MemoryHeader) + allocationInfo->allocatedSize + allocationInfo->followingFreeSize;
		allocationInfo = reinterpret_cast<MemoryHeader*>( movePointer( allocationInfo, tempSize ) );

		//updating checked bytes
		checkedSize += tempSize;
	}

	//in case not enough space was found - extend
	//or simply use attached extension
	if( checkedSize >= _size )
	{
		extend( sizeof(MemoryHeader) + spaceToAllocate );
		return _extension->allocate( space );
	}

	//move the pointer to the beginning of free size
	void* pointer = movePointer( allocationInfo, sizeof( MemoryHeader ) + allocationInfo->allocatedSize );

	//casting new MemoryHeader
	MemoryHeader* newAllocation = static_cast< MemoryHeader* >( pointer );

	//setting values of new header
	newAllocation->accessCounter = 1;
	newAllocation->allocatedSize = control::convert<u64, u32>( space );
	newAllocation->followingFreeSize = crap::control::convert<u64, u32>( allocationInfo->followingFreeSize - spaceToAllocate );

	//setting info in previous header
	allocationInfo->followingFreeSize = 0;

	// reducing current size
	_currentSize -= spaceToAllocate;

	// Tracking memory if activated
	#if defined(CRAP_MEMORY_TRACKER)
	MemoryTracker::instance().addUsedMemory(  spaceToAllocate );
	#endif

	//move pointer to beginning of space and return it
	return movePointer( pointer, sizeof( MemoryHeader ) );
}

//set allocated memory as "ready to use again" for other memory reuqests
void MemoryBlock::deallocate( void* address )
{
	//locking mutex
	SCOPE_MUTEX( &_mutex );

	//parsing pointer value ( 64bit for 64 bit system )
	u64 blockStart =  reinterpret_cast<u64>( _blockStart );

	//last byte of block
	u64 blockEnd = blockStart + _size;

	//if pointer is in this block...
	if( blockStart < reinterpret_cast<u64>( address ) && blockEnd > reinterpret_cast<u64>( address ) )
	{
		// parse intro header
		MemoryHeader* previousAllocationInfo = static_cast<MemoryHeader*>(_blockStart);

		//move pointer to first allocation and parse header again
		u32 tempSize = sizeof(MemoryHeader) + previousAllocationInfo->allocatedSize + previousAllocationInfo->followingFreeSize;
		void* pointer = movePointer( previousAllocationInfo, tempSize );
		MemoryHeader* currentAllocationInfo = static_cast< MemoryHeader* >( pointer );

		// loop parsing while found adresses are smaller then searched value
		// working with previous and current block - current gets checked
		// previous is for updating space values in case of adress was found
		while( movePointer(currentAllocationInfo, sizeof(MemoryHeader)) < address )
		{
			//current to previous headerinfo
			previousAllocationInfo = currentAllocationInfo;

			//moving to next block
			tempSize = sizeof(MemoryHeader) + currentAllocationInfo->allocatedSize + currentAllocationInfo->followingFreeSize;
			void* pointer = movePointer( currentAllocationInfo, tempSize );

			//updating current header
			currentAllocationInfo = static_cast< MemoryHeader* >( pointer );
		}

		//if loop ends the adress should be found...
		CRAP_ASSERT_DEBUG( movePointer(currentAllocationInfo, sizeof(MemoryHeader)) == address, "Memory address not found" );

		//we write into previous header that this allocation is free now
		//(dont worry - mutex is still locked)
		previousAllocationInfo->followingFreeSize += sizeof(MemoryHeader) + currentAllocationInfo->allocatedSize + currentAllocationInfo->followingFreeSize;

		// reducing current size
		_currentSize += sizeof(MemoryHeader) + currentAllocationInfo->allocatedSize;

		// Tracking memory if activated
		#if defined(CRAP_MEMORY_TRACKER)
		MemoryTracker::instance().removeUsedMemory( sizeof(MemoryHeader) + currentAllocationInfo->allocatedSize );
		#endif
	}
	else // pointer is not in this block's address scope
	{
		//do we have an extension to move on?
		CRAP_ASSERT_DEBUG( _extension != 0, "Memory address for freeing not found" );

		//forward request to extension
		_extension->deallocate( address );
	}
}

//returns block's extension
MemoryBlock* MemoryBlock::extension( void )
{
	return _extension;
}

//extends block with extensionblock using input size
// if there is no extension already
void MemoryBlock::extend( u64 size )
{
	if( _extension != 0 )
		return;

	CRAP_ASSERT_DEBUG( _extensionCount != 0, "Limit of memory-extensions reached" );

	//reducing max. extension number by 1
	i32 nextExtensionCount = ( _extensionCount > 0) ? _extensionCount-1 : _extensionCount;
	_extension = new MemoryBlock( size, nextExtensionCount);
}

// force new extension - asserts if old was not 0
void MemoryBlock::setExtension( MemoryBlock* add )
{
	SCOPE_MUTEX( &_mutex );

	CRAP_ASSERT_DEBUG( _extension == 0, "Falied to set extension, already set" );
	_extension = add;
}

//adds extension into list of extensions
void MemoryBlock::addExtension( MemoryBlock* add )
{
	SCOPE_MUTEX( &_mutex );

	if( _extension != 0 )
		_extension->addExtension( add );
	else
		_extension = add;
}

//removes attached extension and replace it wit extension of removed extension
MemoryBlock* MemoryBlock::removeExtension( void )
{
	SCOPE_MUTEX( &_mutex );

	MemoryBlock* rtn = _extension;
	if( _extension != 0 )
	{
		_extension = _extension->extension();
		rtn->_extension = 0;
	}

	return rtn;
}

//removes attached extension and replace it with zero
MemoryBlock* MemoryBlock::removeAllExtensions( void )
{
	SCOPE_MUTEX( &_mutex );
	MemoryBlock* rtn = _extension;
	_extension = 0;
	return rtn;
}

//returns size of block
u64 MemoryBlock::size() const
{
	return _size;
}

//returns size of block
u64 MemoryBlock::space() const
{
	return _currentSize;
}

// help method to move pointer along bytes
void* MemoryBlock::movePointer( void* ptr, u64 bytes ) const
{
	u8* pointer = reinterpret_cast<u8*>(ptr);
	pointer += bytes;
	return pointer;
}
/*
	Following: operate new/delete - simlpe mallocing
*/
inline void* MemoryBlock::operator new (std::size_t size) throw (std::bad_alloc)
{
	return malloc( size );
}

inline void* MemoryBlock::operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
{
	return malloc( size );
}

inline void* MemoryBlock::operator new[] (std::size_t size) throw (std::bad_alloc)
{
	return malloc( size );
}

inline void* MemoryBlock::operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
{
	return malloc( size );
}

inline void MemoryBlock::operator delete (void* pointer) throw ()
{
	free( pointer );
}

inline void MemoryBlock::operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw()
{
	free( pointer );
}

inline void MemoryBlock::operator delete[] (void* pointer) throw ()
{
	free( pointer );
}

inline void MemoryBlock::operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw()
{
	free( pointer );
}

// print memory for debugging
std::ostream& operator<<( std::ostream& out, const MemoryBlock& memBlock )
{
	out << std::endl << "[block]" << std::endl;
	MemoryBlock::MemoryHeader* memInfo = static_cast<MemoryBlock::MemoryHeader*>( memBlock._blockStart );
	void* endOfMemory = memBlock.movePointer( memBlock._blockStart, memBlock._size );
	while( memBlock.movePointer( memInfo, sizeof(MemoryBlock::MemoryHeader) + memInfo->allocatedSize + memInfo->followingFreeSize ) <= endOfMemory )
	{
//		for( u32 i=0; i< sizeof(MemoryBlock::MemoryHeader); ++i)
//		{
//			out << '-';
//		}
		out << "C:" << memInfo->accessCounter << " S:" << memInfo->allocatedSize << " F:" << memInfo->followingFreeSize << std::endl;

//		for( u32 i=0; i< memInfo->allocatedSize; ++i)
//		{
//			out << '1';
//		}
//
//		out << " ";
//
//		for( u32 i=0; i< memInfo->followingFreeSize; ++i)
//		{
//			out << '0';
//		}
//
//		out << " ";

		void* tmp_ptr = memBlock.movePointer( memInfo, sizeof(MemoryBlock::MemoryHeader) + memInfo->allocatedSize + memInfo->followingFreeSize );
		memInfo = static_cast<MemoryBlock::MemoryHeader*>(tmp_ptr);
	}

	if( memBlock._extension != 0 )
		out << *memBlock._extension;

	return out;
}

}	// namespace memory
}	// namespace crap

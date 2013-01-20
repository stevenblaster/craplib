////////////////////////////////////////////////////////
// CRAP Library
//	memorytracker.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		Keeps track of allocations. Offers passivly methods to store
// 	information, which can be used by memory management
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////


#include "memory/memorytracker.h"


namespace crap
{

MemoryTracker* MemoryTracker::_instance = 0;

MemoryTracker::MemoryTracker() : _memoryblocks(0),
													  _allocations(0),
													  _memoryblocks_max(0),
													  _allocations_max(0),
													  _memoryblocks_all(0),
													  _allocations_all(0),
													  _allocatedMemory(0),
													  _usedMemory(0),
													  _biggestMemoryBlock(0),
													  _biggestAllocation(0)
{

}

MemoryTracker::~MemoryTracker()
{
	//dtor
}

MemoryTracker& MemoryTracker::instance( void )
{
	if( _instance == 0 )
		_instance = new MemoryTracker();

	return *_instance;
}

void MemoryTracker::addAllocatedBlock( u64 size )
{
	++_memoryblocks;
	_memoryblocks_max = ( _memoryblocks_max < _memoryblocks ) ? _memoryblocks : _memoryblocks_max;
	++_memoryblocks_all;
	_allocatedMemory += size;
	_allocatedMemory_max = ( _allocatedMemory_max < _allocatedMemory ) ? _allocatedMemory : _allocatedMemory_max;
	_biggestMemoryBlock = ( size > _biggestMemoryBlock ) ? size : _biggestMemoryBlock;
}

void MemoryTracker::removeAllocatedBlock( u64 size )
{
	--_memoryblocks;
	_allocatedMemory -= size;
}

u64 MemoryTracker::allocatedMemoryBlocks( void ) const
{
	return _memoryblocks;
}

u64 MemoryTracker::allocatedMemoryBlocksMax( void ) const
{
	return _memoryblocks_max;
}

u64 MemoryTracker::allocatedMemoryBlocksAll( void ) const
{
	return _memoryblocks_all;
}

u64 MemoryTracker::allocatedMemoryBlocksMem( void ) const
{
	return _allocatedMemory;
}

u64 MemoryTracker::allocatedMemoryBlocksMemMax( void ) const
{
	return _allocatedMemory_max;
}

u64 MemoryTracker::allocatedMemoryBlocksBig( void ) const
{
	return _biggestMemoryBlock;
}

void MemoryTracker::addUsedMemory( u64 size )
{
	++_allocations;	//number of allocations done by MemoryBlocks
	_allocations_max = ( _allocations_max < _allocations ); // maxinum allocations assigned by memblocks at same time
	++_allocations_all; // all allocations handled by Memoryblocks
	_usedMemory += size;	// used space of memory blocks
	_usedMemory_max = ( _usedMemory_max < _usedMemory ) ? _usedMemory : _usedMemory_max;	// max used space of memory blocks
	_biggestAllocation = ( _biggestAllocation < size) ? size : _biggestAllocation; // biggest amount of requested memory from Memoryblocks
}
void MemoryTracker::removeUsedMemory( u64 size )
{
	--_allocations;
	_usedMemory -= size;
}

u64 MemoryTracker::usedMemory( void ) const
{
	return _allocations;
}

u64 MemoryTracker::usedMemoryMax( void ) const
{
	return _allocations_max;
}

u64 MemoryTracker::usedMemoryAll( void ) const
{
	return _allocations_all;
}

u64 MemoryTracker::usedMemoryMem( void ) const
{
	return _usedMemory;
}

u64 MemoryTracker::usedMemoryMemMax( void ) const
{
	return _usedMemory_max;
}

u64 MemoryTracker::usedMemoryBig( void ) const
{
	return _biggestAllocation;
}

std::ostream& operator<<( std::ostream& out, const MemoryTracker& tracker )
{
	out << "Current MemoryBlocks: @t@t" << tracker._memoryblocks << std::endl
		  << "Max. Blocks at same time: @t" << tracker._memoryblocks_max << std::endl
		  << "Total allocated Memoryblocks:@t" << tracker._memoryblocks_all << std::endl
		  << "Current allocations: @t@t" << tracker._allocations << std::endl
		  << "Max. allocations at same time: @t" << tracker._allocations_max << std::endl
		  << "Total allocations: @t@t" << tracker._allocations_all << std::endl
		  << "Currently allocated memory:@t" << tracker._allocatedMemory << std::endl
		  << "Maximum allocated memory: @t" << tracker._allocatedMemory_max << std::endl
		  << "Currently used Memory: @t@t" << tracker._usedMemory << std::endl
		  << "Biggest MemoryBlock: @t@t" << tracker._biggestMemoryBlock << std::endl
		  << "Biggest allocation: @t@t" << tracker._biggestAllocation << std::endl;
	return out;
}

/*
	Following: operate new/delete - simlpe mallocing
*/
inline void* MemoryTracker::operator new (std::size_t size) throw ()
{
	return malloc( size );
}

inline void* MemoryTracker::operator new[] (std::size_t size) throw ()
{
	return malloc( size );
}

inline void MemoryTracker::operator delete (void* pointer) throw ()
{
	free( pointer );
}

inline void MemoryTracker::operator delete[] (void* pointer) throw ()
{
	free( pointer );
}


}	// namespace crap

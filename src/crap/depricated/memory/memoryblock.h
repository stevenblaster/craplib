////////////////////////////////////////////////////////
// CRAP Library
//	memoryblock.h
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
#pragma once

#ifndef CRAP_MEMORY_MEMORYBLOCK_H
#define CRAP_MEMORY_MEMORYBLOCK_H


namespace crap
{
namespace threading
{
	class Mutex;
}
namespace memory
{

class MemoryBlock
{
private:

	/*
	 * 12 byte header struct used as memoryinformation
	 * accessCounter: can be used by reference counter
	 * allocatedSize: Memory in use
	 * followingFreeSize: Free block until next header or end of block.
	 */
    typedef
    struct MemInfo
    {
        u32 accessCounter;
        u32 allocatedSize;
        u32 followingFreeSize;
    }
    MemoryHeader;

	// Start of memory, including first header
    void* _blockStart;

	// total size of memory
    u64 _size;

    // current size of memory
    u64 _currentSize;

	// pointer to next block
    MemoryBlock* _extension;

    // max. following extension blocks
    i32 _extensionCount;

	// Mutex for avoiding parallel access
    threading::Mutex _mutex;

public:

	// Optional garbage collector declared as friend
	friend class GarbageCollector;

	/* Constructor:
	 * Input: size as size of memory to allocate
	 * 		  extensions as number of maximum extensions */
    MemoryBlock( u64 size, i32 extensions );

    /* Destructor */
    ~MemoryBlock( void );

	/* allocate:
	 * Input: space as amount of bytes to allocate
	 * Output: void pointer to allocated address
	 * Description: Uses info of headers to find sufficiant
	 * 	amount of memory in its block, or forwards the
	 * 	request to it's extension. If there's no extension
	 * 	it will be added with  either standard size or at
	 * 	least the requested size + header */
	void* allocate( u64 space );

	/* deallocate:
	 * Input: address of memory to delete
	 * Description: Looks up if memoryblock contains
	 * 	the address and updates space as free in other
	 *		headers. Attempts to forward request to
	 *		extensions. */
    void deallocate( void* address );

	/* extension:
	 * Output: Pointer to extending MemoryBlock
	 * Description: Returns pointer to current extension */
    MemoryBlock* extension( void );

    /* extend:
     * Input: size of extension
     * Description: adds extension to block or quits if an
     * 	extension already exists. */
     //@TODO: Should be used privately only!
	void extend( u64 size );

	/* setExtension:
	 * Input: Pointer to existing MemoryBlock
	 * Description: Sets extension if none is set (assert) */
    void setExtension( MemoryBlock* add );

    /* addExtension:
     * Input: Pointer to exisiting MemoryBlock
     * Description: Adds extension at the end of list
     * 	(recursive) */
    void addExtension( MemoryBlock* add );

    /* removeExtension:
     * Output: Pointer to former extension
     * Description: Removes extension from list and connects
     * 	MemoryBlock in front with following Memoryblock
     *		as extension. */
    MemoryBlock* removeExtension( void );

	/* removeExtension:
     * Output: Pointer to first extension
     * Description: Removes extension and linked extensions
     		and sets memberpointer to zero*/
    MemoryBlock* removeAllExtensions( void );

	/* size:
	 * Output: Size of MemoryBlock
	 * Description: Returns size of Block. */
    u64 size() const;

    	/* size:
	 * Output: Current size of MemoryBlock
	 * Description: Returns current space of Block. */
    u64 space() const;

    /* movePointer:
     * Input: ptr as pointer to be moved
     * 		  bytes as amount of bytes the pointer should be shifted
     * Output: Void pointer as new position */
    //@TODO: Should be used privately only!
    void* movePointer( void* ptr, u64 bytes ) const;

	/* operator new/delete
	 * Description: Default overloading of operator new and
	 * 	delete using malloc and free to avoid memory-management */
    void* operator new (std::size_t size) throw (std::bad_alloc);
	void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
	void* operator new[] (std::size_t size) throw (std::bad_alloc);
	void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
	void operator delete (void* pointer) throw ();
	void operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw();
	void operator delete[] (void* pointer) throw ();
	void operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw();

	/* operator<<:
	 * Description: Overloading stream opator thus setting function as friend
	 * 	for more easy usage. */
	friend std::ostream& operator<<( std::ostream& out, const MemoryBlock& memBlock );
};

} // namespace memory
} // namespace crap

#endif // CRAP_MEMORY_MEMORYBLOCK_H

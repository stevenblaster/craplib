////////////////////////////////////////////////////////
// CRAP Library
//	memorytracker.h
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
//		Keeps track of allocations. Offers passivly methods to store
// 	information, which can be used by memory management
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MEMORY_MEMORYTRACKER_H
#define CRAP_MEMORY_MEMORYTRACKER_H

namespace crap
{

class MemoryTracker
{
	private:
		u64 _memoryblocks; // number of MemoryBlock objects
		u64 _allocations;	//number of allocations done by MemoryBlocks

		u64 _memoryblocks_max; // maximum MemoryBlocks at same time
		u64  _allocations_max; // maxinum allocations assigned by memblocks at same time

		u64 _memoryblocks_all; // all MemoryBlocks allocated during runtime
		u64  _allocations_all; // all allocations handled by Memoryblocks

		u64 _allocatedMemory; // amount of allocated Memory from System by MemoryBlocks
		u64 _usedMemory;	// used space of memory blocks

		u64 _allocatedMemory_max; // max amount of allocated Memory from System by MemoryBlocks
		u64 _usedMemory_max;	// max used space of memory blocks

		u64 _biggestMemoryBlock; // biggest allocated Memoryblock
		u64 _biggestAllocation; // biggest amount of requested memory from Memoryblocks

		//Constructor
		MemoryTracker( void );

		//Singelton, thus static instance
		static MemoryTracker* _instance;

	public:

		//Destructor
		~MemoryTracker( void );

		//Static instance method (singelton)
		static MemoryTracker& instance( void );

		/* addAllocatedBlock
		 * Input: size as allocated space
		 * Description:
		 */
		void addAllocatedBlock( u64 size );

		/* removeAllocatedBlock
		 * Input: size as allocated space
		 * Description:
		 */
		void removeAllocatedBlock( u64 size );

		/*
		 *
		 */
		u64 allocatedMemoryBlocks( void ) const;

		/*
		 *
		 */
		u64 allocatedMemoryBlocksMax( void ) const;

		/*
		 *
		 */
		u64 allocatedMemoryBlocksAll( void ) const;

		/*
		 *
		 */
		u64 allocatedMemoryBlocksMem( void ) const;

		/*
		 *
		 */
		u64 allocatedMemoryBlocksMemMax( void ) const;

		/*
		 *
		 */
		u64 allocatedMemoryBlocksBig( void ) const;

		/*
		 *
		 */
		void addUsedMemory( u64 size );

		/*
		 *
		 */
		void removeUsedMemory( u64 size );

		/*
		 *
		 */
		u64 usedMemory( void ) const;

		/*
		 *
		 */
		u64 usedMemoryMax( void ) const;

		/*
		 *
		 */
		u64 usedMemoryAll( void ) const;

		/*
		 *
		 */
		u64 usedMemoryMem( void ) const;

		/*
		 *
		 */
		u64 usedMemoryMemMax( void ) const;

		/*
		 *
		 */
		u64 usedMemoryBig( void ) const;

		/*
		 *
		 */
		friend std::ostream& operator<<( std::ostream& out, const MemoryTracker& tracker );

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
};

}	// namespace crap

#endif // CRAP_MEMORY_MEMORYTRACKER_H

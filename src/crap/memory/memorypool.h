////////////////////////////////////////////////////////
//  CRAP Library
//		@file memorypool.h
//
//	Creator:
//		Steffen Kopany <steffen@kopany.at>
//
//	Author(s):
// 		@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright (c) 2012 Steffen Kopany
//
//	Description:
//		@brief Static pool of bytes using headers for
//		seperating allocated blocks.
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MEMORYPOOL_H
#define CRAP_MEMORYPOOL_H

#include "memory/allocatormalloc.h"

// lib namespace
namespace crap
{

/*
 * @brief memory pool class
 */

class memory_pool
{
	
private:

	/*
	 * @brief memory header for each allocated block, containing
	 * a memory offset to the previous allocation, amount of allocated
	 * memory and the following free space (if there is any)
	 */
	
	struct memory_block
	{
		size_t32 offset_prev;
		size_t32 used_memory;
		size_t32 free_memory;
	};
	
	// @brief starting pointer for initial header
	memory_block* _block_start;
	
	// @brief pointer to the block containing biggest free block
	memory_block* _biggest_block;
	
	// @brief internal method for parsing memory for biggest free block
	void update_biggest_block(void);
	
	// @brief general size of allocated pool
	size_t32 _size;
	
	// @brief current free size all together in pool
	size_t32 _current_size;

public:

	// @brief default constructor
	memory_pool(void);
	
	// @brief constructor with initial size
	memory_pool(size_t32 size);

	// @brief destructor
	~memory_pool(void);
	
	// @brief initializing function - when default constructor was used
	inline void init(size_t32 size);
	
	// @brief allocate specific amount of bytes
	inline void* allocate(size_t32 size);
	
	// @brief allocate quickly by using biggest free block pointer
	inline void* quick_allocate(size_t32 size);
	
	// @brief deallocating memory, by taking header out of list
	inline void deallocate(void* address);
	
	// @brief returns void pointer on first block
	inline void* block_start(void) const { return _block_start; }
	
	// @brief returns total size
	inline size_t32 total_size(void) const { return _size; }

	// @brief returns current free space in pool (at all)
	inline size_t32 size(void) const { return _current_size; }
	
	// @brief return size of biggest block (free memory)
	inline size_t32 biggest_block(void) const { return _biggest_block->free_memory; }
	
	// @brief test if a pointer is in this pool
	inline bool is_in_range(void* address) const { 
		return (_block_start < address && address < reinterpret_cast<u8*>(_block_start) + _size); }
};

/*
 * definitiona
 */

// constructor
memory_pool::memory_pool(void) : _block_start(0), _biggest_block(0), _size(0)
{
	
}

// constructor with initialization
memory_pool::memory_pool(size_t32 size)
{
	init(size);
}

// initialization
void memory_pool::init(size_t32 size)
{
	CRAP_ASSERT_DEBUG( _block_start = 0, "Memory pool already initialized" );
	
	CRAP_ASSERT_DEBUG( size > sizeof(memory_block), "Size of memory pool is too low" );
	
	_block_start = (memory_block*)malloc(size);
	
	_block_start->offset_prev = 0;
	_block_start->used_memory = 0;
	_block_start->free_memory = size - sizeof(memory_block);
	
	_size = size;
	
	_current_size = size - sizeof(memory_block);
	
	_biggest_block = _block_start;
}
	
// destructor
memory_pool::~memory_pool(void)
{
	CRAP_ASSERT_DEBUG( _size == _current_size + sizeof(memory_block), "Still allocations in memory pool" );
	
	delete (u8*)_block_start;
}

// allocate memory
void* memory_pool::allocate(size_t32 size)
{
	//size to allocate is space + header size
	size_t32 allocation_size = sizeof(memory_block) + size;
	
	//assert there is space at all AND if there's a block being big enough
	CRAP_ASSERT_DEBUG( _current_size >= allocation_size, "Not enough space for allocation" );
	CRAP_ASSERT_DEBUG( _biggest_block->free_memory >= allocation_size, "Not enough space for allocation" );
	
	//pointer to the block containing enough free space, init. with zero
	memory_block* found_block = 0;
	
	//check if the very first block has enough space - if it doesnt...
	if( _block_start->free_memory < allocation_size )
	{
		//the parsed memory - init. with the complete size of the first block
		size_t32 parsed_memory = sizeof(memory_block) + _block_start->used_memory + _block_start->free_memory;
		
		//this size will be updated each step of folling loop - should extend pool's size
		while( parsed_memory < _size )
		{
			//pointer to position we expect the next block
			memory_block* parsed_block = (memory_block*)(reinterpret_cast<u8*>(_block_start) + parsed_memory);
			
			//check if this block has enough free space for the wanted allocation
			if( parsed_block->free_memory >= allocation_size )
			{
				//it has enough space, lets set the found_block variable and break the loop
				found_block = parsed_block;
				break;
			}
			else
			{
				//not enough space, lets update parsed memory for the next step in loop
				parsed_memory += sizeof(memory_block) + parsed_block->used_memory + parsed_block->free_memory;
			}
		}
	}
	else
	{
		//the very first block has enough space
		found_block = _block_start;
	}
	
	//assert a block was found
	CRAP_ASSERT_DEBUG( found_block != 0, "No free block with space enough found" );
	
	//lets set up the new block on free space's position
	memory_block* new_block = (memory_block*)(reinterpret_cast<u8*>(found_block + 1) + found_block->used_memory);
		
	//insert offset to previous block
	new_block->offset_prev = sizeof(memory_block) + found_block->used_memory;
	
	//insert used (not allocated, since header is not used) space of block
	new_block->used_memory = size;
	
	//reduce free memory bye allocated size (used size +  header size)
	new_block->free_memory = found_block->free_memory - allocation_size;
	
	//previous block has no free memory left (new one overtook rest)	
	found_block->free_memory = 0;
		
	//if used block was the biggest, lets update that one
	if( found_block == _biggest_block )
	{
		update_biggest_block();
	}
		
	//return pointer to used space
	return new_block + 1;
}

// update biggest block (internal)
void memory_pool::update_biggest_block(void)
{
	//init. parsed block with starting block
	memory_block* parsed_block = _block_start;
	
	//init. parsed memory with size of first block
	size_t32 parsed_memory = sizeof(memory_block) + parsed_block->used_memory + parsed_block->free_memory;
	
	//parse whole block
	while( parsed_memory < _size )
	{
		//check next block...
		memory_block* check_block = (memory_block*)(reinterpret_cast<u8*>(_block_start) + parsed_memory);
		
		//if there's more free space, lets update the parsed pointer
		if( parsed_block->free_memory < check_block->free_memory )
			parsed_block = check_block;
			
		//else lets update parsed memory
		parsed_memory += sizeof(memory_block) + check_block->used_memory + check_block->free_memory;
	}
	
	//update biggest block pointer
	_biggest_block = parsed_block;
}

// allocate quick
void* memory_pool::quick_allocate(size_t32 size)
{
	//set complete allocation size
	size_t32 allocation_size = sizeof(memory_block) + size;
	
	//assert there's enough space and if the biggest block is big enough
	CRAP_ASSERT_DEBUG( _current_size >= allocation_size, "Not enough space for allocation" );
	CRAP_ASSERT_DEBUG( _biggest_block->free_memory >= allocation_size, "Not enough space for allocation" );
	
	//set new block as biggest block's free size
	memory_block* new_block = (memory_block*)(reinterpret_cast<u8*>(_biggest_block + 1) + _biggest_block->used_memory);
	
	//set offset to previous block
	new_block->offset_prev = sizeof(memory_block) + _biggest_block->used_memory;
	
	//set allocated size
	new_block->used_memory = size;
	
	//set following free space
	new_block->free_memory = _biggest_block->free_memory - allocation_size;
		
	//set free memory of biggest block to zero - new block got the rest of it
	_biggest_block->free_memory = 0;
	
	//since biggest block ist anymore, lets parse for a new one
	update_biggest_block();
	
	//return pointer to used space of new block
	return new_block + 1;
}

// deallocate
void memory_pool::deallocate(void* address)
{
	//assert the pointer is in range
	CRAP_ASSERT_DEBUG( is_in_range(address) == true, "Address for deallocation out of range" );
		
	//get block info
	memory_block* delete_block = (memory_block*) address;
	
	//parse previous block
	memory_block* previous_block = (memory_block*)(reinterpret_cast<u8*>(delete_block) - delete_block->offset_prev);
	
	//check if previous block is still in range
	CRAP_ASSERT_DEBUG( previous_block >= _block_start, "Previous offset of deallocation pointer out of range" );
	
	//crosscheck if data of previous block is correct
	bool check_offset = reinterpret_cast<memory_block*>(reinterpret_cast<u8*>(previous_block + 1) + 
						previous_block->used_memory + previous_block->free_memory) == delete_block;
	
	// if crosscheck failed - abort
	CRAP_ASSERT_DEBUG( check_offset == true , "Offset check error, previous offset doesn't match" );
	
	//update free memory of previous block with complete size of deleted block
	previous_block->free_memory += sizeof(memory_block) + delete_block->used_memory + delete_block->free_memory;
	
	//update biggest free block
	update_biggest_block();
}
	
}	//namespace crap


#endif // CRAP_MEMORYPOOL_H

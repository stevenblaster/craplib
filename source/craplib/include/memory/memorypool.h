////////////////////////////////////////////////////////
//  CRAP Library
//!		@file memorypool.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Static pool of bytes using headers for
//		seperating allocated blocks.
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MEMORYPOOL_H
#define CRAP_MEMORYPOOL_H

// lib namespace
namespace crap
{

/*
 *! @brief memory pool class
 */

class memory_pool
{

private:

	/*
	 *! @brief memory header for each allocated block, containing
	 * a memory offset to the previous allocation, amount of allocated
	 * memory and the following free space (if there is any)
	 */

	struct memory_block
	{
		size_t32 offset_prev;
		size_t32 used_memory;
		size_t32 free_memory;
	};

	//! @brief starting pointer for initial header
	memory_block* _block_start;

	//! @brief pointer to the block containing biggest free block
	memory_block* _biggest_block;

	//! @brief internal method for parsing memory for biggest free block
	void update_biggest_block(void);

	//! @brief general size of allocated pool
	size_t32 _size;

	//! @brief current free size all together in pool
	size_t32 _current_size;

public:

	//! @brief default constructor
	memory_pool(void);

	//! @brief constructor with initial size
	memory_pool(size_t32 size);

	//! @brief destructor
	~memory_pool(void);

	//! @brief initializing function - when default constructor was used
	void init(size_t32 size);

	//! @brief allocate specific amount of bytes
	void* allocate(size_t32 size);

	//! @brief allocate quickly by using biggest free block pointer
	void* quick_allocate(size_t32 size);

	//! @brief deallocating memory, by taking header out of list
	void deallocate(void* address);

	//! @brief returns void pointer on first block
	void* block_start(void) const { return _block_start; }

	//! @brief returns total size
	size_t32 total_size(void) const { return _size; }

	//! @brief returns current free space in pool (at all)
	size_t32 size(void) const { return _current_size; }

	//! @brief return size of biggest block (free memory)
	size_t32 biggest_block(void) const { return _biggest_block->free_memory; }

	//! @brief test if a pointer is in this pool
	bool is_in_range(void* address) const {
		return (_block_start < address && address < reinterpret_cast<u8*>(_block_start) + _size); }
};

}	//namespace crap


#endif // CRAP_MEMORYPOOL_H

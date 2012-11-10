////////////////////////////////////////////////////////
// CRAP Library
//	memorymanager.h
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
//		The description can take
//		more then one line
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_MEMORYMANAGER_H
#define CRAP_MEMORYMANAGER_H


namespace crap
{
namespace memory
{
class GarbageCollector;
class MemoryBlock;

class MemoryManager
{
private:
    MemoryManager();
    ~MemoryManager();

    MemoryBlock* _default;
    MemoryBlock* _special;

    static MemoryManager* _instance;

	bool _gcRunning;
	#if defined(CRAP_GARBAGE_COLLECTOR)
	GarbageCollector* _collector;
	threading::Mutex _mutex;
	#endif

public:

	friend class GarbageCollector;

    static MemoryManager& instance();

    void addSpecial( MemoryBlock* block );

    void* allocate(u64 space);
    void deallocate(void* address);

	void* operator new (std::size_t size) throw (std::bad_alloc);
	void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
	void* operator new[] (std::size_t size) throw (std::bad_alloc);
	void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw();
	void operator delete (void* pointer) throw ();
	void operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw();
	void operator delete[] (void* pointer) throw ();
	void operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw();

    friend std::ostream& operator<<( std::ostream& theStream, const MemoryManager& memman );
};

}	// namespace memory
}	// namespace crap


#endif // CRAP_MEMORYMANAGER_H

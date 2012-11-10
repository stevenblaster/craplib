////////////////////////////////////////////////////////
// CRAP Library
//	memorymanager.cpp
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
#include "threading/mutex.h"
#include "memory/memoryblock.h"
#include "threading/runnable.h"
//#include "memory/garbagecollector.h" TODO: build me
#include "memory/memorymanager.h"
//#include "threading/threadmanager.h" TODO: build me

namespace crap
{
namespace memory
{

MemoryManager* MemoryManager::_instance = 0;

MemoryManager::MemoryManager()
{
	_default = 0; //new MemoryBlock( MEMMAN_SIZE, MEMMAN_EXTENSIONS );
	_special = 0;

	#if defined(CRAP_GARBAGE_COLLECTOR)
//	_collector = new GarbageCollector( CRAP_GC_TICK );
//	_gcRunning = false;
	#endif
}

MemoryManager::~MemoryManager()
{
	delete _default;
	delete _special;
}

MemoryManager& MemoryManager::instance()
{
	if( _instance == 0 )
		_instance = new MemoryManager();

	return *_instance;
}

void MemoryManager::addSpecial( MemoryBlock* add )
{
	if( _special == 0 )
	{
		_special = add;
		return;
	}

	MemoryBlock* ext = _special;
	while( ext->extension() != 0 )
	{
		ext = ext->extension();
	}
	ext->setExtension( add );
}

void* MemoryManager::allocate(u64 space)
{
#if defined(CRAP_GARBAGE_COLLECTOR)
//	if( _gcRunning == false )
//	{
//		_gcRunning = true;
//		threading::ThreadManager::instance().add( _collector );
//	}
#endif

#if defined(CRAP_MEMORY_MANAGER)
	if( _default == 0 )
		_default = new MemoryBlock(space + 24, -1); //TODO - let this be configured...

	return _default->allocate(space);
#else
	return malloc(space);
#endif
}

void MemoryManager::deallocate(void* address)
{
#if defined(CRAP_MEMORY_MANAGER)
	_default->deallocate(address);
#else
	free(space);
#endif
}

inline void* MemoryManager::operator new (std::size_t size) throw (std::bad_alloc)
{
	return malloc( size );
}

inline void* MemoryManager::operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
{
	return malloc( size );
}

inline void* MemoryManager::operator new[] (std::size_t size) throw (std::bad_alloc)
{
	return malloc( size );
}

inline void* MemoryManager::operator new[] (std::size_t size, const std::nothrow_t& nothrow_constant) throw()
{
	return malloc( size );
}

inline void MemoryManager::operator delete (void* pointer) throw ()
{
	free( pointer );
}

inline void MemoryManager::operator delete (void* pointer, const std::nothrow_t& nothrow_constant) throw()
{
	free( pointer );
}

inline void MemoryManager::operator delete[] (void* pointer) throw ()
{
	free( pointer );
}

inline void MemoryManager::operator delete[] (void* pointer, const std::nothrow_t& nothrow_constant) throw()
{
	free( pointer );
}

std::ostream& operator<<( std::ostream& theStream, const MemoryManager& memman )
{
	theStream << *memman._default;
	return theStream;
}

}
}

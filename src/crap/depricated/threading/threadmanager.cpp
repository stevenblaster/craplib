////////////////////////////////////////////////////////
// CRAP Library
//	threadmanager.cpp
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
#include "threading/runnable.h"
#include "threading/thread.h"
#include "threading/threadmanager.h"

namespace crap
{
namespace threading
{

ThreadManager::ThreadManager()
{
}

ThreadManager* ThreadManager::_instance = 0;

ThreadManager& ThreadManager::instance()
{
    if( _instance == 0 )
        _instance = new ThreadManager();

    return *_instance;
}

THREAD_HANDLE ThreadManager::add(Runnable* runnable)
{
    ThreadStarter starter( runnable, false );
    _threads.add( starter.threadID(), runnable );
    return starter.threadID();
}

void ThreadManager::remove(Runnable* runnable)
{
	if( _threads.containsValue(runnable) )
	{
		_threads.remove( runnable );
		if( runnable->deleteOnFinish() )
			delete runnable;
	}
}

void ThreadManager::remove( const THREAD_HANDLE& handle )
{
	Runnable* runnable = findRunnable( handle );
	if( runnable != 0 )
	{
		_threads.remove( runnable );
		if( runnable->deleteOnFinish() )
			delete runnable;
	}
}

void ThreadManager::remove( const types::String64& threadname )
{
	_threads.remove( findRunnable(threadname) );
}

Runnable* ThreadManager::findRunnable( const THREAD_HANDLE& handle )
{
    return *_threads.findValue( handle );
}

Runnable* ThreadManager::findRunnable( const types::String64& threadname )
{
    for( u64 i=0; i<_threads.size(); ++i )
    {
        container::Pair<THREAD_HANDLE, Runnable*> pair = _threads[i];
        types::String64 name = pair.value->name();
        if( name == threadname )
            return pair.value;
    }
    return 0;
}

THREAD_HANDLE ThreadManager::findHandle( Runnable* runnable )
{
    return *_threads.findKey( runnable );
}

THREAD_HANDLE ThreadManager::findHandle( const types::String64& threadname )
{
    for( u64 i=0; i<_threads.size(); ++i )
    {
        container::Pair<THREAD_HANDLE, Runnable*> pair = _threads[i];
        types::String64 name = pair.value->name();
        if( name == threadname )
            return pair.key;
    }
    return 0;
}

bool ThreadManager::killThread( const THREAD_HANDLE& handle )
{
    Runnable* runnable = *(_threads.findValue( handle ));
    if( runnable != 0  && runnable->isRunning() )
    {
        _threads.remove( handle );
        return ( (!THREAD_KILL( handle )) || (THREAD_JOIN( handle ) == THREAD_ZERO) );
    }
    return false;
}

bool ThreadManager::killThread( Runnable* runnable )
{
    if( runnable == 0 )
        return false;

    THREAD_HANDLE handle =   *_threads.findKey( runnable );
    if( handle != 0 && runnable->isRunning() )
    {
        _threads.remove( handle );
        return ( (!THREAD_KILL( handle )) || (THREAD_JOIN( handle ) == THREAD_ZERO) );
    }
    return false;
}

bool ThreadManager::killThread( const types::String64& threadname )
{
    for( u64 i=0; i<_threads.size(); ++i )
    {
        container::Pair<THREAD_HANDLE, Runnable*> pair = _threads[i];
        types::String64 name = pair.value->name();
        if( name == threadname )
            return killThread(pair.key);
    }
    return false;
}

bool ThreadManager::waitForThread( const types::String64& threadname )
{
    for( u64 i=0; i<_threads.size(); ++i )
    {
        container::Pair<THREAD_HANDLE, Runnable*> pair = _threads[i];
        types::String64 name = pair.value->name();
        if( name == threadname )
            return waitForThread(pair.value);
    }
    return false;
}

bool ThreadManager::waitForThread( const THREAD_HANDLE& handle )
{
    Runnable* runnable = *_threads.findValue(handle);
    if( runnable != 0 && runnable->isRunning() )
        return waitForThread( *_threads.findValue(handle) );
    else
        return false;
}

bool ThreadManager::waitForThread( Runnable* runnable )
{
    THREAD_HANDLE thread = *_threads.findKey(runnable);

    if( thread != 0 && runnable->isRunning() )
        return THREAD_JOIN( thread ) == THREAD_ZERO;
    else
        return false;
}

bool ThreadManager::isRunning( const types::String64& threadname )
{
    for( u64 i=0; i<_threads.size(); ++i )
    {
        container::Pair<THREAD_HANDLE, Runnable*> pair = _threads[i];
        types::String64 name = pair.value->name();
        if( name == threadname )
            return pair.value->isRunning();
    }
    return false;
}

bool ThreadManager::isRunning( const THREAD_HANDLE& handle )
{
    Runnable* runnable = *_threads.findValue( handle );
    if( runnable != 0 && runnable->isRunning() )
        return true;
    else
        return false;
}

}	// namespace threading
}	// threading crap


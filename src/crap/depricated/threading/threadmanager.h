////////////////////////////////////////////////////////
// CRAP Library
//	threadmanager.h
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

#ifndef CRAP_THREADING_THREADMANAGER_H
#define CRAP_THREADING_THREADMANAGER_H

#include "types/staticstring.h"
#include "container/map.h"

namespace crap
{
namespace threading
{

class Runnable;

class ThreadManager
{
private:
    ThreadManager();
    container::StaticMap<THREAD_HANDLE, Runnable*, 500> _threads;
    static ThreadManager* _instance;

public:
    static ThreadManager& instance();

    THREAD_HANDLE add( Runnable* runnable );

    void remove( Runnable* runnable );
    void remove( const THREAD_HANDLE& handle );
    void remove( const types::String64& threadname );

    Runnable* findRunnable( const THREAD_HANDLE& handle );
    Runnable* findRunnable( const types::String64& threadname );

    THREAD_HANDLE findHandle( Runnable* runnable );
    THREAD_HANDLE findHandle( const types::String64& threadname );

    bool killThread( const types::String64& threadname );
    bool killThread( const THREAD_HANDLE& handle );
    bool killThread( Runnable* runnable );

    bool waitForThread( const types::String64& threadname );
    bool waitForThread( const THREAD_HANDLE& handle );
    bool waitForThread( Runnable* runnable );

    bool isRunning( const types::String64& threadname );
    bool isRunning( const THREAD_HANDLE& handle );
};

}	// namespace threading
}	// namespace crap

#endif // CRAP_THREADING_THREADMANAGER_H

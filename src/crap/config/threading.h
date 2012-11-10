////////////////////////////////////////////////////////
//	CRAP Library
//!		@file threading.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Uses platform / compiler settings to
//		config threading
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_THREADING_H
#define CRAP_CONFIG_THREADING_H

#include "config/platforms.h"

// Use Window or Posix
#if defined(CRAP_PLATFORM_WIN)

//mean and lean
#define WIN32_MEAN_AND_LEAN
#include <windows.h>

//mutex
#define MUTEX_HANDLE CRITICAL_SECTION
#define CONDITION HANDLE
#define SLEEP_MSEC(millisec) Sleep(millisec)
//Semaphore
#define LMAXIMUMCOUNT 99999999 /* Maximum semaphore value in Windows*/
#define SEMAPHORE_HANDLE HANDLE
//Threads
#define THREAD_HANDLE HANDLE
#define THREAD_RETURN DWORD WINAPI
#define THREAD_STARTER( ptr ) starter(LPVOID ptr)
#define THREAD_CREATE( handle, run, runnable) handle = CreateThread( 0x00, 0x00, run, static_cast< void* >( runnable ), 0x00, 0x00 )
#define THREAD_NULL NULL
#define THREAD_JOIN( handle ) WaitForSingleObject( handle, INFINITE )
#define THREAD_ZERO 0x00000000L
#define THREAD_KILL( handle ) TerminateThread( handle, 1 ) && CloseHandle( handle )
#define THREAD_CANCEL_SETUP 0

#else // using posix

#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
//mutex
#define MUTEX_HANDLE pthread_mutex_t
#define CONDITION pthread_cond_t
#define SLEEP_MSEC(millisec) usleep( millisec * 1000 )
//Semaphore
#define SEMAPHORE_HANDLE sem_t
//Threads
#define THREAD_HANDLE pthread_t
#define THREAD_RETURN void*
#define THREAD_STARTER( ptr ) starter(void* ptr)
#define THREAD_CREATE( handle, run, runnable) pthread_create( &handle, NULL, run, static_cast< void* >( runnable ) )
#define THREAD_NULL 0
#define THREAD_JOIN( handle ) pthread_join( handle, NULL )
#define THREAD_ZERO 0
//#define THREAD_KILL( handle ) pthread_kill( handle, SIGKILL ) == 0
//#define THREAD_KILL( handle ) pthread_kill( handle, SIGQUIT ) == 0
#define THREAD_KILL( handle ) pthread_cancel( handle ) == 0
#define THREAD_CANCEL_SETUP pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)

#endif //defined(CRAP_PLATFORM_WIN)


#endif //CRAP_CONFIG_THREADING_H

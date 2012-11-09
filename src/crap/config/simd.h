////////////////////////////////////////////////////////
//  CRAP Library
//		@file simd.h
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
//		@brief Looking for SIMD macros
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONFIG_SIMD_H
#define CRAP_CONFIG_SIMD_H

#include "config/processors.h"
#include "config/compilers.h"

//instruction set types
#define CRAP_SIMD_NONE		0
#define CRAP_SIMD_SSE		1
#define CRAP_SIMD_SSE2		2
#define CRAP_SIMD_SSE3		3
#define CRAP_SIMD_SSSE3		4
#define CRAP_SIMD_SSE41		5
#define CRAP_SIMD_SSE42		6
#define CRAP_SIMD_AVX		7
#define CRAP_SIMD_AVX2		8

//lib namespace
namespace crap
{

//parsing compiler macros or using forced set
#if defined ( __AVX2__ )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_AVX2
#elif defined ( __AVX__ )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_AVX
#elif defined ( __SSE4_2__ )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_SSE42
#elif defined ( __SSE4_1__ )
	#define CRAP_SIMD_VERSION	CRAP_SIMD_SSE41
#elif defined ( __SSSE3__ )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_SSSE3
#elif defined ( __SSE3__ )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_SSE3
#elif defined ( __SSE2__ ) || defined ( CRAP_PROCESSOR_X86_64 )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_SSE2
#elif defined ( __SSE__ )
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_SSE
#elif defined ( _M_IX86_FP )	//VC compiler
	#define CRAP_SIMD_VERSION 	_M_IX86_FP
#else
	#define CRAP_SIMD_VERSION 	CRAP_SIMD_NONE
#endif

/*
 * @brief CPU id macros
 */

#if defined(CRAP_COMPILER_GCC)

   #define CRAP_CPUID(func, reg) __asm__ __volatile__ ("cpuid": "=a" (reg[0]), "=b" (reg[1]), "=c" (reg[2]), "=d" (reg[3]) : "a" (func), "c" (0) : );

#elif (defined(CRAP_COMPILER_VC) || defined(CRAP_COMPILER_INTEL))

	//include <intrin.h> on win (should happen in precompiled.h)
	#define CRAP_CPUID(func, reg) __cpuid((int*)reg, (int)func);

#else

    #define CRAP_CPUID(func, reg)__asm {	\
		mov eax, func										\
		xor ecx, ecx											\
        cpuid;													\
        mov esi, reg											\
        mov [esi],    eax									\
        mov [esi+4],  ebx									\
        mov [esi+8],  ecx									\
        mov [esi+12], edx								\
    }

#endif

/*
 * @brief Includes for detected simd
 */
 
#if defined(CRAP_COMPILER_GCC) && CRAP_SIMD_VERSION == CRAP_SIMD_AVX2
	#define CRAP_SIMD_INCLUDE 		<x86intrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_AVX2
	#define CRAP_SIMD_INCLUDE 		<immintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_AVX
		#define CRAP_SIMD_INCLUDE 	<immintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_SSE42
		#define CRAP_SIMD_INCLUDE 	<nmmintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_SSE41
		#define CRAP_SIMD_INCLUDE 	<smmintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_SSSE3
		#define CRAP_SIMD_INCLUDE 	<tmmintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_SSE3
		#define CRAP_SIMD_INCLUDE 	<pmmintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_SSE2
		#define CRAP_SIMD_INCLUDE 	<emmintrin.h>
#elif CRAP_SIMD_VERSION == CRAP_SIMD_SSE
		#define CRAP_SIMD_INCLUDE 	<xmmintrin.h>
#endif

//other stuff
#if defined (__XOP__) || defined (__FMA4__)
	#if defined(CRAP_COMPILER_GCC) && ( defined (__XOP__) || defined (__FMA4__) )
		#include <x86intrin.h>
	#else
		#include <ammintrin.h>
	#endif
#elif defined (__SSE4A__)
	#include <ammintrin.h>
#endif

#if defined (__FMA__)
	#include <fmaintrin.h>
#endif

#if defined (__FMA4__)
	#include <fma4intrin.h> // must have both x86intrin.h and fma4intrin.h
#endif

} // namespace crap

#endif // CRAP_CONFIG_SIMD_H

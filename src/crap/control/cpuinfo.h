////////////////////////////////////////////////////////
//	CRAP Library
//		@file cpuinfo.h
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
//		@brief Help functions for detecting cpu flags
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTROL_CPUINFO_H
#define CRAP_CONTROL_CPUINFO_H

#if defined(CRAP_COMPILER_VC)
#include <intrin.h>
#endif

#include "types/staticrap::cstring.h"

//MACROS!!!

//functions
#define CRAP_CPUINFO_FUNC_VENDOR 	0x00000000  // usually returns some smart vendor string when read as string
#define CRAP_CPUINFO_FUNC_FEATURE 	0x00000001  // info about family and stuff (also MMX, SSE and stuff)
#define CRAP_CPUINFO_FUNC_CACHE	 	0x00000002  // cache and TBL
#define CRAP_CPUINFO_FUNC_SERIAL	0x00000003 // bottom of serial number
#define CRAP_CPUINFO_FUNC_CORES	 	0x00000004// returns core and additional cach info
#define CRAP_CPUINFO_FUNC_EXT		0x80000000// returns extension info
#define CRAP_CPUINFO_FUNC_EXTFEAT	0x80000001// returns extended features

//feature flags
#define	CRAP_CPUINFO_FPU			0		//Floating Point Unit
#define CRAP_CPUINFO_VME			1		//Virtual 8086 Mode Enhancements
#define CRAP_CPUINFO_DE				2		//Debugging Extensions
#define CRAP_CPUINFO_PSE 			3		//Page Size Extensions
#define	CRAP_CPUINFO_TSC			4		//Time Stamp Counter
#define	CRAP_CPUINFO_MSR			5		//Model Specific Registers
#define	CRAP_CPUINFO_PAE			6		//Physical Address Extension
#define CRAP_CPUINFO_MCE			7		//Machine Check Exception
#define	CRAP_CPUINFO_CX8			8		//COMPXCHG8B Instruction
#define	CRAP_CPUINFO_APIC			9		//On-chip Advanced Programmable Interrupt Controller present and enabled
#define	CRAP_CPUINFO_10				10	//Reserved

#define	CRAP_CPUINFO_SEP			11	//Fast System Call
#define	CRAP_CPUINFO_MTRR			12	//Memory Type Range Registers
#define	CRAP_CPUINFO_PGE			13	//PTE Global Flag
#define	CRAP_CPUINFO_MCA			14	//Machine Check Architecture
#define	CRAP_CPUINFO_CMOV			15	//Conditional Move and Compare Instructions
#define	CRAP_CPUINFO_FGPAT			16	//Page Attribute Table
#define	CRAP_CPUINFO_PSE_36	    	17	//36-bit Page Size Extension
#define	CRAP_CPUINFO_PN				18	//Processor Serial Number present and enabled
#define	CRAP_CPUINFO_CLFSH			19	//CFLUSH instruction
#define	CRAP_CPUINFO_20				20	//reserved

#define	CRAP_CPUINFO_DS				21	//Debug store
#define	CRAP_CPUINFO_ACPI			22	//Thermal Monitor and Clock Ctrl
#define	CRAP_CPUINFO_AMDMMX			22	//AMD MMX Instruction Extensions
#define	CRAP_CPUINFO_MMX			23	//MMX instruction set
#define	CRAP_CPUINFO_FXSR			24	//Fast FP/MMX Streaming SIMD Extensions save/restore
#define	CRAP_CPUINFO_SSE			25	//Streaming SIMD Extensions instruction set
#define	CRAP_CPUINFO_SSE2			26	//SSE2 extensions
#define	CRAP_CPUINFO_SS				27	//Self Snoop
#define	CRAP_CPUINFO_HT				28	//Hyper Threading
#define	CRAP_CPUINFO_TM				29	//Thermal monitor
#define	CRAP_CPUINFO_3DNOW1			30	//3DNow! Instruction Extensions
#define	CRAP_CPUINFO_3DNOW			31	//3DNow instructions

namespace crap
{

enum SIMD
{
	None=0,
	SSE,
	SSE2,
	SSE3,
	SSSE3,
	SSE41,
	SSE42,
	AVX,
	AVX2
};

class cpu_info
{
	private:

		static SIMD _detected;

		// Define interface to xgetbv instruction
		static inline i64 xgetbv (i32 ctr)
		{
		#if defined (CRAP_COMPILER_INTEL) // defined (CRAP_COMPILER_VC)  ||
			return _xgetbv(ctr);
		#elif defined(CRAP_COMPILER_GCC) && !defined(CRAP_PLATFORM_MAC)
		   u32 a, d;
		   __asm("xgetbv" : "=a"(a),"=d"(d) : "c"(ctr) : );
		   return a | (u64(d) << 32);
		#else
		   u32 a, d;
			__asm {
				mov ecx, ctr
				_emit 0x0f
				_emit 0x01
				_emit 0xd0 ; // xgetbv
				mov a, eax
				mov d, edx
			}
		   return a | (u64(d) << 32);
		#endif
		}

		//copied, gotta work on own stuff
		void simd_detect(void)
		{
			_detected = None;
			i32 abcd[4] = {0,0,0,0};
			CRAP_CPUID(0, abcd);

			// no further cpuid function supported
			if (abcd[0] == 0)
				return;

			// call cpuid function 1 for feature flags
			CRAP_CPUID(1,abcd);
			if ((abcd[3] & (1 <<  0)) == 0 || (abcd[3] & (1 << 23)) == 0 || (abcd[3] & (1 << 15)) == 0 || (abcd[3] & (1 << 24)) == 0 || (abcd[3] & (1 << 25)) == 0)
				return;           // no floating point, no MMX, no conditional move, no FXSAVE,  no SSE

			// 1: SSE supported
			_detected = SSE;
			if ((abcd[3] & (1 << 26)) == 0)
				return;           // no SSE2

			// 2: SSE2 supported
			_detected = SSE2;
			if ((abcd[2] & (1 <<  0)) == 0)
				return;           // no SSE3

			// 3: SSE3 supported
			_detected = SSE3;
			if ((abcd[2] & (1 <<  9)) == 0)
				return;           // no SSSE3

			// 4: SSSE3 supported
			_detected = SSSE3;
			if ((abcd[2] & (1 << 19)) == 0)
				return;           // no SSE4.1

			// 5: SSE4.1 supported
			_detected = SSE41;
			if ((abcd[2] & (1 << 23)) == 0 || (abcd[2] & (1 << 20)) == 0 )
				return;           // no POPCNT, no SSE4.2

			// 6: SSE4.2 supported
			_detected = SSE42;
			if ((abcd[2] & (1 << 27)) == 0 || (xgetbv(0) & 6) != 6 || (abcd[2] & (1 << 28)) == 0)
				return;           // no OSXSAVE, AVX not enabled in O.S., no AVX

			// 7: AVX supported
			_detected = AVX;

			// call cpuid leaf 7 for feature flags
			CRAP_CPUID(7, abcd);

			if ((abcd[1] & (1 <<  5)) == 0)
				return;           // no AVX2

			// 8: AVX2 supported
			_detected = AVX2;
			return;
		}

		c8 _bitsetMem[4];

		static cpu_info* _instance;

		u32 _info0[4];
		u32 _info1[4];
		u32 _info2[4];
		u32 _info3[4];
		u32 _info4[4];
		u32 _info80[4];
		u32 _info81[4];

		cpu_info();

	public:

		SIMD detectedSIMD() { return _detected;}

		static cpu_info& instance();

		crap::string16 vendor();

		inline u32 stepping() { return _info1[0] & 0xf; }
		inline u32 model() { return (_info1[0] >> 4) & 0xf; }
		inline u32 family() { return (_info1[0] >> 8) & 0xf; }
		inline u32 type() { return (_info1[0] >> 12) & 0x3; }
		inline u32 clf() { return (_info1[1] >> 8) & 0xff; }
		inline u32 apicID() { return (_info1[1] >> 24) & 0xff; }
		inline u32 silbings() { return (_info1[1] >> 16) & 0xff; }
		crap::string16 type_string();
		crap::string64 family_string();

		inline b8 has_feature( u32 id ) const { return (_info1[3] & (1<<id)); }
		inline b8 has_feature_2( u32 id ) const { return (_info1[2] & (1<<id)); }

		inline b8 hasFPU() const { return has_feature(CRAP_CPUINFO_FPU); }
		inline b8 hasVME() const { return has_feature(CRAP_CPUINFO_VME); }
		inline b8 hasDE() const { return has_feature(CRAP_CPUINFO_DE); }
		inline b8 hasPSE() const { return has_feature(CRAP_CPUINFO_PSE); }
		inline b8 hasTSC() const { return has_feature(CRAP_CPUINFO_TSC); }
		inline b8 hasMSR() const { return has_feature(CRAP_CPUINFO_MSR); }
		inline b8 hasPAE() const { return has_feature(CRAP_CPUINFO_PAE); }
		inline b8 hasMCE() const { return has_feature(CRAP_CPUINFO_MCE); }
		inline b8 hasCX8() const { return has_feature(CRAP_CPUINFO_CX8); }
		inline b8 hasAPIC() const { return has_feature(CRAP_CPUINFO_APIC); }
		inline b8 hasSEP() const { return has_feature(CRAP_CPUINFO_SEP); }
		inline b8 hasMTRR() const { return has_feature(CRAP_CPUINFO_MTRR); }
		inline b8 hasPGE() const { return has_feature(CRAP_CPUINFO_PGE); }
		inline b8 hasMCA() const { return has_feature(CRAP_CPUINFO_MCA); }
		inline b8 hasCMOV() const { return has_feature(CRAP_CPUINFO_CMOV); }
		inline b8 hasFGPAT() const { return has_feature(CRAP_CPUINFO_FGPAT); }
		inline b8 hasPSE36() const { return has_feature(CRAP_CPUINFO_PSE_36); }
		inline b8 hasPN() const { return has_feature(CRAP_CPUINFO_PN); }
		inline b8 hasCLFSH() const { return has_feature(CRAP_CPUINFO_CLFSH); }
		inline b8 hasDS() const { return has_feature(CRAP_CPUINFO_DS); }
		inline b8 hasACPI() const { return has_feature(CRAP_CPUINFO_ACPI); }
		inline b8 hasAMDMMX() const { return has_feature(CRAP_CPUINFO_AMDMMX); }
		inline b8 hasMMX() const { return has_feature(CRAP_CPUINFO_MMX); }
		inline b8 hasFXSR() const { return has_feature(CRAP_CPUINFO_FXSR); }
		inline b8 hasSSE() const { return has_feature(CRAP_CPUINFO_SSE); }
		inline b8 hasSSE2() const { return has_feature(CRAP_CPUINFO_SSE2); }
		inline b8 hasSSE3() const { return has_feature(0); }
		inline b8 hasSS() const { return has_feature(CRAP_CPUINFO_SS); }
		inline b8 hasHT() const { return has_feature(CRAP_CPUINFO_HT); }
		inline b8 hasTM() const { return has_feature(CRAP_CPUINFO_TM); }
		inline b8 has3DNOW1() const { return has_feature(CRAP_CPUINFO_3DNOW1); }
		inline b8 has3DNOW() const { return has_feature(CRAP_CPUINFO_3DNOW); }

};

}	// namespace crap

#endif // CRAP_CONTROL_CPUINFO_H

////////////////////////////////////////////////////////
//	CRAP Library
//!		@file cpuinfo.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Help functions for detecting cpu flags
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#include "container/staticstring.h"
#include "control/cpuinfo.h"

namespace crap
{

SIMD
cpu_info::_detected = None;

cpu_info*
cpu_info::_instance = 0;

cpu_info&
cpu_info::instance()
{
	if( _instance == 0 )
		_instance = new cpu_info();

	return *_instance;
}

cpu_info::cpu_info()
{
	CRAP_CPUID( CRAP_CPUINFO_FUNC_VENDOR , _info0 );
	CRAP_CPUID( CRAP_CPUINFO_FUNC_FEATURE, _info1 );
	CRAP_CPUID( CRAP_CPUINFO_FUNC_CACHE, _info2 );
	CRAP_CPUID( CRAP_CPUINFO_FUNC_SERIAL, _info3 );
	CRAP_CPUID( CRAP_CPUINFO_FUNC_CORES, _info4 );
	CRAP_CPUID( CRAP_CPUINFO_FUNC_EXT, _info80 );
	CRAP_CPUID( CRAP_CPUINFO_FUNC_EXTFEAT, _info81 );
	simd_detect();
}

crap::string16
cpu_info::vendor()
{
	crap::string16 tmp;
	memcpy( &(tmp[0]), _info0 + 1, 4);
	memcpy( &(tmp[4]), _info0 + 3, 4);
	memcpy( &(tmp[8]), _info0 + 2, 4);
	return tmp;
}

crap::string16 cpu_info::simd_string()
{
	switch( _detected )
	{
	case None:
		return "None";
	case SSE:
		return "SSE";
	case SSE2:
		return "SSE2";
	case SSE3:
		return "SSE3";
	case SSE41:
		return "SSE4.1";
	case SSE42:
		return "SSE4.2";
	case AVX:
		return "AVX";
	case AVX2:
		return "AVX2";
	default:
		return "Failure";
	};
}

crap::string16
cpu_info::type_string()
{
	switch( type() )
	{
		case 0:
			return "Original OEM";
			break;

		case 1:
			return "Overdrive";
			break;

		case 2:
			return "Dual-capable";
			break;

		default:
			return "Reserved/Unknown";
			break;
	};
}

crap::string64
cpu_info::family_string()
{

	crap::string64 famString;

	switch( family() )
	{
		case 2:
			return "x286";
			break;

		case 3:
			return "x386";
			break;

		case 4:
			famString += "x486";
			switch( model() )
			{
				case 0:
				case 1:
					famString += ", AMD 1 / Intel DX";
					break;
				case 2:
					famString += ", AMD 2 / Intel SX";
					break;
				case 3:
					famString += ", AMD 3 / Intel 487-DX2";
					break;
				case 4:
					famString += ", AMD 4 / Intel SL";
					break;
				case 5:
				case 6:
					famString += ", AMD 5,6 / Intel SX2";
					break;
				case 7:
					famString += ", AMD 7 / Intel enhanced DX2";
					break;
				case 8:
					famString += ", AMD 8 / Intel DX4";
					break;
			};
			return famString;

		case 5:
			famString += "Intel Pentium";
			switch( model() )
			{
				case 0:
				case 1:
					famString += " 60-66, AMD K6 Model 1";
					break;
				case 2:
					famString += " 75-200, AMD K6 Model 2";
					break;
				case 3:
					famString += " for 486, AMD K6 Model 3";
					break;
				case 4:
					famString += " MMX, AMD K6 Model 4";
					break;
				case 5:
					famString += " MMX, AMD K6 Model 5";
					break;
				case 6:
					famString += " MMX, AMD K6 Model 6";
					break;
				case 7:
					famString += " MMX, AMD K6 Model 7";
					break;
				case 8:
					famString += " MMX, AMD K6-2 Model 8";
					break;
				case 9:
					famString += " MMX, AMD K6-III Model 9";
					break;
			};
			return famString;
			break;

		case 6:
			switch( model() )
			{
				case 0:
				case 1:
					famString += "Intel Pentium Pro, AMD Athlon model 1";
					break;

				case 2:
					famString += "Intel Pentium II, AMD Athlon model 2";
					break;

				case 3:
					famString += "Intel Pentium II Model 3, AMD Duron model 3";
					break;

				case 4:
					famString += "Intel Pentium II Model 4, AMD Athlon model 4";
					break;

				case 5:
					famString += "Intel Pentium II Model 5/Xeon/Celeron, AMD Athlon model 5";
					break;

				case 6:
					famString += "Intel Celeron, AMD Athlon MP/Mobile Athlon model 6";
					break;

				case 7:
					famString += "Intel Pentium III/Pentium III Xeon - external L2 cache, AMD Mobile Duron Model 7";
					break;

				case 8:
					famString += "Intel Pentium III/Pentium III Xeon - internal L2 cache, AMD Athlon/Duron 8";
					break;

				default:
					famString += "Intel Pentium Pro/II/III, AMD Athlon/Duron";
			};
			return famString;
			break;

		case 15:
			return "Pentium 4";
			break;

		default:
			return "Unknown family";
	};
}

}	// namespace crap

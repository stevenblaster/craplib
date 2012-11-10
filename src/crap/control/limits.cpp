////////////////////////////////////////////////////////
//	CRAP Library
//!		@file limits.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Provides info about Type limits
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#include "control/limits.h"

namespace crap
{

const f32 limits<f32>::MIN = F32_MIN;
const f32 limits<f32>::MAX = F32_MAX;


const f64 limits<f64>::MIN = F64_MIN;
const f64 limits<f64>::MAX = F64_MAX;

}	// namespace crap

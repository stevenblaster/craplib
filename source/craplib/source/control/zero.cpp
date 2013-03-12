////////////////////////////////////////////////////////
//	CRAP Library
//!		@file zero.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Provides correct zero value
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "crap.h"

#include "control/zero.h"

const f32 crap::zero<f32>::VALUE = 0.0f;
const f64 crap::zero<f64>::VALUE = 0.0;

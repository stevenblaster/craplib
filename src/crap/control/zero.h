////////////////////////////////////////////////////////
//	CRAP Library
//		@file time.h
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
//		@brief Provides the right zero value
//
//
//	Status (scratch, developed, final):
//		@status scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTROL_ZERO_H
#define CRAP_CONTROL_ZERO_H

//lib namespace
namespace crap
{

template<typename T>
struct zero
{
	static const T VALUE = 0;
};

template<>
struct zero<f32>
{
	static const f32 VALUE;
};

template<>
struct zero<f64>
{
	static const f64 VALUE;
};

}	// namespace crap

#endif // CRAP_CONTROL_ZERO_H

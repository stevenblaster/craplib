////////////////////////////////////////////////////////
//	CRAP Library
//!		@file random.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Random functions
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_MATH_RANDOM_H
#define CRAP_MATH_RANDOM_H

//#include <random>
#include <ctime>

#include "control/limits.h"
#include "control/converter.h"

#pragma warning(disable:4554)
#pragma warning(disable:4146)

//lib namespace
namespace crap
{

static i32 random_seed = 0;

template<typename T>
struct random
{
    static CRAP_INLINE
    void init( void );

    static CRAP_INLINE
    T generate( void );

    static CRAP_INLINE
    T generate_positive( void );

    static CRAP_INLINE
    T generate_negative( void );

    static CRAP_INLINE
    T range( const T& from, const T& to );
};

//definitions
template<typename T>
void random<T>::init( void )
{
    if( crap::random_seed == 0 )
    {
        crap::random_seed = (u32)::time( NULL );
        srand( crap::random_seed );
    }
}

template<typename T>
T random<T>::generate( void )
{
    random<T>::init(); //init if it isnt

    T return_var;
    i32 var = rand();

    //floating point's easy 1 to zero
    if( !crap::limits<T>::IS_INT )
        return_var = (T)var / crap::limits<i16>::MAX;
    else
        return_var = crap::convert<i32, T>( var );

    if( crap::limits<T>::IS_SIGNED )
        return_var = ( var & (0x01) == 1 ) ? return_var : -return_var;

    if( sizeof(T) > 4 && crap::limits<T>::IS_INT )
        return_var = return_var * rand();

    return return_var;
}

template<typename T>
T random<T>::generate_positive( void )
{
    T var = random<T>::generate();
    return ( var < 0 ) ? -var : var;
}

template<typename T>
T random<T>::generate_negative( void )
{
    T var = random<T>::generate();

    if( !crap::limits<T>::IS_SIGNED )
        return 0;

    return ( var > 0 ) ? -var : var;
}

template<typename T>
T random<T>::range( const T& from, const T& to )
{
    T diff = to - from;

    if( crap::limits<T>::IS_INT )
    {
        T var = random<T>::generate_positive();
        T div = var / diff;
        return from + ( var - diff*div );
    }

    return from + diff * random<T>::generate_positive();
}

}

#endif //CRAP_MATH_RANDOM_H

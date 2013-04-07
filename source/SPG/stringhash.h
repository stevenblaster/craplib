#pragma once

#ifndef STRINGHASH_H
#define STRINGHASH_H

#include "precompiled.h"

template<size_t32 S>
CRAP_INLINE
u32 string_to_hash( const crap::fixed_string<S>& str )
{
	u32 rtn = 0;
	for( u32 i = 0; i < str.size(); ++i )
	{
		rtn += (u32)str[i];
	}
	return rtn * str.size();
}

#endif // STRINGHASH_H
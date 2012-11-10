////////////////////////////////////////////////////////
// CRAP Library
//	string.cpp
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
#include "types/string.h"

namespace crap
{
namespace types
{

String::String( void ) : _memory(0)
{
}

String::String( const String& other )
{
	_memory = new c8[ other.size() ];
	memcpy( _memory, other._memory, other.size() );
}

String::String( cstring* cstr )
{
	memset( _memory, 0, alignSize(strlen(cstr)) );
    memcpy( _memory, cstr, strlen(cstr) );
}
/*
String& String::operator=( const String& other );
String& String::operator=( const i8* cstring );

String& String::operator+=( const String& other );
String& String::operator+=( const i8* cstring );

bool String::operator==( const String& other );
bool String::operator==( const i8* cstring );

bool String::operator!=( const String& other );
bool String::operator!=( const i8* cstring );

i8& String::operator[]( u64 index );
const i8& String::operator[]( u64 index ) const;

friend std::ostream& operator<<( std::ostream& theStream, const String& theString );

void String::concat( const String<S>& other );
void String::concat( const i8* cstring );

bool String::compare( const String& other );
bool String::compare( const i8* cstring );

bool String::contains( const String& other );
bool String::contains( const i8* cstring );
bool String::contains( const i8& other );

i64 String::search( const String& other );
i64 String::search( const i8* cstring );
i64 String::search( const i8& other );

String String::substr( u64 start, u64 length );

const container::ArrayList<String> String::split( i8 seperator ) const;
void String::merge( container::ArrayList<String>&, i8 glue );

void String::cut( u64 length );
void String::trim( void );
u64 String::size( void ) const;

void String::extendMemorySize();
void String::reduceMemorySize();
void String::setMemorySize();
*/
u64 String::alignSize( u64 size )
{
	u64 rtn  = 0;
	for(u64 i=1; size>i; i*=2)
	{
		rtn = i;
	}
	return rtn * 2;
}

}
}


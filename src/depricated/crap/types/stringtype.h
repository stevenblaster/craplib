////////////////////////////////////////////////////////
// CRAP Library
//	stringtype.h
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
//		String Interface
//
//	Status (scratch, developed, final):
//		scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_TYPES_STRINGTYPE_H
#define CRAP_TYPES_STRINGTYPE_H

namespace crap
{
namespace types
{

class StringType
{
public:
    virtual StringType& operator=( const StringType& other ) { return *this; }
    virtual StringType& operator=( const i8* cstring ) { return *this; }

    virtual StringType& operator+=( const StringType& other ) { return *this; }
    virtual StringType& operator+=( const i8* cstring ) { return *this; }

    virtual bool operator==( const StringType& other ) { return true; }
    virtual bool operator==( const i8* cstring )  { return true; }

    virtual bool operator!=( const StringType& other )  { return false; }
    virtual bool operator!=( const i8* cstring )  { return false; }

    virtual i8& operator[]( u64 index );
    virtual const i8& operator[]( u64 index ) const;

    friend std::ostream& operator<<( std::ostream& theStream, const StringType& theString )  { return theStream; }

    virtual void concat( const StringType& other ) {}
    virtual void concat( const i8* cstring ) {}

    virtual bool compare( const StringType& other )  { return true; }
    virtual bool compare( const i8* cstring ) { return true; }

    virtual bool contains( const StringType& other ) { return true; }
    virtual bool contains( const i8* cstring ) { return true; }
    virtual bool contains( const i8& other ) { return true; }

    virtual i64 search( const StringType& other ) { return 0; }
    virtual i64 search( const i8* cstring ) { return 0; }
    virtual i64 search( const i8& other ) { return 0; }

    virtual StringType substr( u64 start, u64 length );

	//nenene implement arraylist sucker
    //const container::ArrayList<String<S>, S/2> split( i8 seperator ) const;

    //void merge( container::ArrayList<String<S>, U>&, i8 glue );

    virtual void cut( u64 length ) { }
    virtual void trim( void ) {}
    virtual u64 size( void ) const { return 0; }
};

}
}

#endif // CRAP_TYPES_STRINGTYPE_H

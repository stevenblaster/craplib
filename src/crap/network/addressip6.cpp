////////////////////////////////////////////////////////
// CRAP Library
//!		@file addressip6.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief ip ver 6 address + port
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#include "control/endian.h"
#include "network/sockets.h"
#include "network/addressip6.h"

//lib namespace
namespace crap
{

address_ip6::address_ip6( void )
{
	socket_address.sin6_family = ip_v6;
}

address_ip6::address_ip6( const address_ip6& other )
{
	socket_address.sin6_addr = other.socket_address.sin6_addr;
	socket_address.sin6_port = other.socket_address.sin6_port;
}

address_ip6::address_ip6( const u128& ip, const u16& prt )
{
	in6_addr swapme;
	memcpy(&swapme, &ip, 16);

#if defined CRAP_ENDIAN_LITTLE
	swapme = endian::swap<in6_addr>(swapme);
#endif

	socket_address.sin6_addr = swapme;
	socket_address.sin6_port = htons(prt);
}

address_ip6::address_ip6( const u16& aa, const u16& bb, const u16& cc, const u16& dd,
						  const u16& ee, const u16& ff, const u16& gg, const u16& hh, const u16& prt )
{
	in6_addr swapme;
	u128 ip;

	ip.part_64[0] = ( (u64)aa << 48 ) | ( (u64)bb << 32 ) | ( (u64)cc << 16 ) | dd;
	ip.part_64[1] = ( (u64)ee << 48 ) | ( (u64)ff << 32 ) | ( (u64)gg << 16 ) | hh;
	memcpy(&swapme, &ip, 16);

#if defined CRAP_ENDIAN_LITTLE
	swapme = endian::swap<in6_addr>(swapme);
#endif

	socket_address.sin6_addr = swapme;
	socket_address.sin6_port = htons(prt);
}

address_ip6& address_ip6::operator=( const address_ip6& other )
{
	CRAP_ASSERT_DEBUG(this != &other, "Assignment operator on same object");
	socket_address.sin6_addr = other.socket_address.sin6_addr;
	socket_address.sin6_port = other.socket_address.sin6_port;
	return *this;
}

u128 address_ip6::get_ip( void ) const
{
	u128 swapme;
	memcpy(&swapme, &socket_address.sin6_addr, 16);

#if defined CRAP_ENDIAN_LITTLE
	swapme = endian::swap<u128>(swapme);
#endif

	return swapme;
}

void address_ip6::set_ip( const u128& ip )
{
	in6_addr swapme;
	memcpy(&swapme, &ip, 16);

#if defined CRAP_ENDIAN_LITTLE
	swapme = endian::swap<in6_addr>(swapme);
#endif

	socket_address.sin6_addr = swapme;
}

u16 address_ip6::get_port( void ) const
{
	return ntohs(socket_address.sin6_port);
}

void address_ip6::set_port( const u16& port )
{
	socket_address.sin6_port = htons(port);
}

address_ip6 address_ip6::any = address_ip6(0,0,0,0,0,0,0,0,0);

}	//namespace crap


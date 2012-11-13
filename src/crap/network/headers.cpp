////////////////////////////////////////////////////////
// CRAP Library
//!		@file headers.cpp
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief several headers
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#include "control/asserts.h"
#include "control/endian.h"
#include "network/addressip4.h"
#include "network/addressip6.h"
#include "network/headers.h"

//lib namespace
namespace crap
{

ip_header_v4::ip_header_v4( void )
{
	header_length			= 5;
	version					= 4;
	type_of_service			= 0;
	lenght					= 0;
	identification			= 0;
	offset					= 0;
	more_fragments_flag		= 0;
	fragment_flag			= 1;
	reserved_flag			= 0;
	time_to_live			= 128;
	protocol				= 0; // SET THE PROTOCOL
	checksum				= 0;
	source_address			= 0;
	destination_address		= 0;
}

ip_header_v4::ip_header_v4( const ip_header_v4& other )
{
	header_length			= other.header_length;
	version					= other.version;
	type_of_service			= other.type_of_service;
	lenght					= other.lenght;
	identification			= other.identification;
	offset					= other.offset;
	more_fragments_flag		= other.more_fragments_flag;
	fragment_flag			= other.fragment_flag;
	reserved_flag			= other.reserved_flag;
	time_to_live			= other.time_to_live;
	protocol				= other.protocol;
	checksum				= other.checksum;
	source_address			= other.source_address;
	destination_address		= other.destination_address;
}

ip_header_v4::~ip_header_v4( void )
{

}

//! @brief set header length
void ip_header_v4::set_header_lenght( u32 h_lenght )
{
	CRAP_ASSERT_DEBUG(h_lenght < 16, "IP header lenght more then 4 bits");
	header_length = endian::to_big(h_lenght);
}

//! @brief set version
void ip_header_v4::set_version( u32 ver )
{
	CRAP_ASSERT_DEBUG(ver == 4, "IP version should be 4");
	version = endian::to_big(ver);
}

//! @brief set TOS
void ip_header_v4::set_type_of_service( u8 tos )
{
	type_of_service = endian::to_big(tos);
}

//! @brief set total lenght
void ip_header_v4::set_lenght( u16 t_lenght )
{
	lenght = endian::to_big(t_lenght);
}

//! @brief set identification
void ip_header_v4::set_identification( u16 id )
{
	identification = endian::to_big(id);
}

//! @brief set more fragments flag
void ip_header_v4::set_more_fragments_flag( bool more_frag_flag )
{
	more_fragments_flag = more_frag_flag;
}

//! @brief set do fragment flag
void ip_header_v4::set_fragment_flag( bool frag_flag )
{
	fragment_flag = frag_flag;
}

//! @brief set offset
void ip_header_v4::set_offset( u16 off )
{
	CRAP_ASSERT_DEBUG(off < 4095, "IP offset has only 13 bits (4095)");
	offset = endian::to_big(off);
}

//! @brief set time to live
void ip_header_v4::set_time_to_live( u8 ttl )
{
	time_to_live = endian::to_big(ttl);
}

//! @brief set protocol type
void ip_header_v4::set_protocol( ip_protocol prtcl )
{
	protocol = prtcl;
}

//! @brief create checksum
void ip_header_v4::create_checksum( void )
{
	u32 sum;
	u32 nwords;
	u16* buf = (u16*) this;
	for (sum = 0; nwords > 0; nwords--)
	{
		sum += *buf++;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	checksum =  (u16) (~sum);
}

//! @brief set source address
void ip_header_v4::set_source_address( address_ip4 src_address )
{
	source_address = src_address.ip_to_network();
}

//! @brief set destination address
void ip_header_v4::set_destination_address( address_ip4 dst_address )
{
	destination_address = dst_address.ip_to_network();
}

}

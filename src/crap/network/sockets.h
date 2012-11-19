////////////////////////////////////////////////////////
// CRAP Library
//!		@file sockets.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief several sockets
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_NETWORK_SOCKETS_H
#define CRAP_NETWORK_SOCKETS_H

//lib namespace
namespace crap
{

enum socket_family
{
	ip_v4 = 2,		/* Internet IP Protocol 	*/
	ipx = 4,		/* Novell IPX 			*/
	appletalk = 5,	/* Appletalk DDP 		*/
	ip_v6 = 10		/* IP version 6			*/
};

enum socket_datatype
{
	stream = 1,		/* tcp */
	datagram = 2,	/* udp */
	raw = 3			/* raw */
};

enum socket_type
{
	ip = 0,			/* Dummy protocol for TCP.  */
	icmp = 1,		/* Internet Control Message Protocol.  */
	tcp = 6,		/* Transmission Control Protocol.  */
	udp = 17,		/* User Datagram Protocol.  */
	icmpv6 = 58,	/* ICMPv6.  */
	sctp = 132,		/* Stream Control Transmission Protocol.  */
	udp_lite = 136, /* User Datagram Protocol Lite */
	raw_data = 255		/* Raw IP packets.  */
};

typedef i32 socket_t;

//predefines
struct address_ip4;
struct address_ip6;
template<typename ADDRESS_T, size_t32 S> struct packet;

/*
 *! @brief socket class...
 */

template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
class socket
{
private:
	socket_t _socket;

public:

	//! @brief default constructor
	socket( void );

	//! @brief copy constructor
	socket( const socket& other );

	//! @brief destructor
	~socket( void );

	//! @brief init socket
	u32 init( void );

	//! @brief init socket
	u32 deinit( void );

	//! @brief send data
	template<typename ADDRESS_T, size_t32 S>
	u32 send( const packet<ADDRESS_T,S>& pack );

	//! @brief receive data
	template<typename ADDRESS_T, size_t32 S>
	u32 receive( packet<ADDRESS_T,S>& pack );
};

}

#endif // CRAP_NETWORK_SOCKETS_H

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

//includes
#include "network/addressip4.h"
#include "network/addressip6.h"
#include "network/packet.h"

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

    //! @brief setup blocking mode
    void set_blocking(bool block);

    //! @brief init socket
    i32 init( u16 port );

    //! @brief deinit socket
    void deinit( void );

    //! @brief send data
    template<typename ADDRESS_T, size_t32 S>
    i32 send( const packet<ADDRESS_T,S>& pack );

    //! @brief receive data
    template<typename ADDRESS_T, size_t32 S>
    i32 receive( packet<ADDRESS_T,S>& pack );

    //! @brief set socket listening (tcp/sctp only)
    i32 listen( void );

    //! @brief connect to address (tcp / sctp only )
    template<typename ADDRESS_T>
    i32 connect( const ADDRESS_T& address );

    //! @brief accept incoming connection (tcp / sctp only )
    template<typename ADDRESS_T>
    i32 accept( ADDRESS_T& address );
};

/*
 *! @brief definition
 */

//constructor
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::socket( void )
{
#if defined(CRAP_PLATFORM_WIN)
    WSADATA wsaData;
    int result = WSAStartup( MAKEWORD(2,2), &wsaData );
    CRAP_ASSERT_DEBUG(result == NO_ERROR, "Couldn't setup Windows socket (wsaData)");
#endif
    _socket = ::socket( FAMILY_T, DATATYPE_T, SOCKTYPE_T );

    CRAP_ASSERT_DEBUG( _socket >= 0, "Socket cound't be created" );
}

// copy constructor
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::socket(  const socket& other  )
{
    _socket = other._socket;
}

//destructor
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::~socket( void )
{
    deinit();
}

//set/unset blocking
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
void socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::set_blocking(bool block)
{
#if defined(CRAP_PLATFORM_WIN)

    DWORD nonBlocking = (block) ? 0 : 1;
    int result = ioctlsocket( _socket, FIONBIO, &nonBlocking );
    CRAP_ASSERT_DEBUG(result == 0, "Couldn't set socket non-blocking");

#else

    int nonBlocking = (block) ? 0 : 1;
    int result = fcntl( _socket, F_SETFL, O_NONBLOCK, nonBlocking ); // was 1);
    CRAP_ASSERT_DEBUG(result != -1, "Couldn't set socket non-blocking");

#endif
}

//init (bind) socket
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
i32 socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::init( u16 port )
{
    i32 result = -1;

    if( FAMILY_T == ip_v4 )
    {
        address_ip4 address = address_ip4::any;
        address.set_port(port);

        result = ::bind( _socket, (const sockaddr*) &address.socket_address, sizeof(sockaddr_in) );
    }
    else if( FAMILY_T == ip_v6 )
    {
        address_ip6 address = address_ip6::any;
        address.set_port(port);

        result = ::bind( _socket, (const sockaddr*) &address.socket_address, sizeof(sockaddr_in6) );
    }
    else
    {
        CRAP_ASSERT_ERROR("socket family not implemented yet");
    }

    CRAP_ASSERT_DEBUG(result != -1, "Couldn't bind socket to port");

//#if defined(CRAP_PLATFORM_WIN)
//	WSADATA wsaData;
//	WSAStartup( MAKEWORD(2,2), &wsaData );
//	CRAP_ASSERT_DEBUG(wsaData == NO_ERROR, "Couldn't setup Windows socket (wsaData)");
//#endif

    return result;
}

//deinit (unbind, destroy socket)
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
void socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::deinit( void )
{
#if defined(CRAP_PLATFORM_WIN)
    WSACleanup();
    closesocket( _socket );
#else
    close( _socket );
#endif
}

//send packet
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
template<typename ADDRESS_T, size_t32 S>
i32 socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::send( const packet<ADDRESS_T,S>& pack )
{
    i32 result;
    if(SOCKTYPE_T == udp || SOCKTYPE_T == udp_lite)
    {
        result = ::sendto( _socket, (const c8*)pack.data, S, 0,
                         (sockaddr*)&pack.address.socket_address, sizeof(pack.address.socket_address) );
    }
    else
    {
        result = ::send(_socket, (const c8*)pack.data, S, 0);
    }
    CRAP_ASSERT_DEBUG(result == S, "Couldn't send packet");
    return result;
}

//receive packet
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
template<typename ADDRESS_T, size_t32 S>
i32 socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::receive( packet<ADDRESS_T,S>& pack )
{
    i32 result;
    if(SOCKTYPE_T == udp || SOCKTYPE_T == udp_lite)
    {
#if defined( CRAP_PLATFORM_WIN )
        i32 addr_lenght = sizeof(pack.address.socket_address);
#else
		u32 addr_lenght = sizeof(pack.address.socket_address);
#endif
        result = ::recvfrom( _socket, (c8*)pack.data, S,
                                           0, (sockaddr*)&pack.address.socket_address, &addr_lenght );
    }
    else
    {
        result = ::recv(_socket,(c8*)pack.data, S, 0);
    }
    return result; // in case of non blocking we can receive nothing...
}

//listen socket
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
i32 socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::listen( void )
{
    CRAP_ASSERT_DEBUG(SOCKTYPE_T == tcp || SOCKTYPE_T == sctp, "Only tcp/sctp sockets can listen");
    return ::listen(_socket, CRAP_MAX_BACKLOG);
}

//connect socket
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
template<typename ADDRESS_T>
i32 socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::connect( const ADDRESS_T& address )
{
    CRAP_ASSERT_DEBUG(SOCKTYPE_T == tcp || SOCKTYPE_T == sctp, "Only tcp/sctp sockets can connect");
    i32 addr_lenght = sizeof(address.socket_address);
    return ::connect(_socket, (const sockaddr*)&address.socket_address, addr_lenght);
}

//accept connection
template<socket_family FAMILY_T, socket_datatype DATATYPE_T, socket_type SOCKTYPE_T>
template<typename ADDRESS_T>
i32 socket<FAMILY_T, DATATYPE_T, SOCKTYPE_T>::accept( ADDRESS_T& address )
{
    CRAP_ASSERT_DEBUG(SOCKTYPE_T == tcp || SOCKTYPE_T == sctp, "Only tcp/sctp sockets can connect");
#if defined( CRAP_PLATFORM_WIN )
	i32 addr_lenght = sizeof(address.socket_address);
#else
    u32 addr_lenght = sizeof(address.socket_address);
#endif
    return ::accept(_socket, (sockaddr*)&address.socket_address, &addr_lenght);
}

//typedefs
typedef socket<ip_v4, stream, tcp> socket_tcp_ip4;
typedef socket<ip_v6, stream, tcp> socket_tcp_ip6;
typedef socket<ip_v4, datagram, udp> socket_udp_ip4;
typedef socket<ip_v6, datagram, udp> socket_udp_ip6;
typedef socket<ip_v4, datagram, udp_lite> socket_udplite_ip4;
typedef socket<ip_v6, datagram, udp_lite> socket_udplite_ip6;
typedef socket<ip_v4, stream, sctp> socket_sctp_ip4;
typedef socket<ip_v6, stream, sctp> socket_sctp_ip6;
typedef socket<ip_v4, raw, raw_data> socket_raw_ip4;
typedef socket<ip_v6, raw, raw_data> socket_raw_ip6;

}

#endif // CRAP_NETWORK_SOCKETS_H

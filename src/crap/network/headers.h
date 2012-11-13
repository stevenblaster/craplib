////////////////////////////////////////////////////////
// CRAP Library
//!		@file headers.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief headers for sockets
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_NETWORK_HEADERS_H
#define CRAP_NETWORK_HEADERS_H

//lib namespace
namespace crap
{
	//predeclare...
	struct address_ip4;
	struct address_ip6;

	/*
	 *! @brief ipv4 header
	 */

	enum ip_protocol
	{
		ICMP = 1,
		stream = 5,
		TCP,
		UDP = 17,
		RDP = 27,
		ICMP_v6 = 58,
		UDPLite = 136
	};

	struct ip_header_v4
	{
		//! @brief data
#if defined(CRAP_ENDIAN_LITTLE)
		u32 header_length:4;		/* header length (usually 5)*/
		u32 version:4;				/* version */
#else
		u32 version:4;				/* version */
		u32 header_length:4;		/* header length (usually 5)*/
#endif
		u8 type_of_service;			/* type of service */
		u16 lenght;					/* total length */
		u16 identification;			/* identification */
#if defined(CRAP_ENDIAN_LITTLE)
		u16 offset:13;				/* fragment offset field */
		u32 more_fragments_flag:1;	/* more fragments follow */
		u32 fragment_flag:1;		/* fragment / dont fragment */
		u32 reserved_flag:1;		/* reserved flag - gotta be zero */
#else
		u32 more_fragments_flag:1;	/* more fragments follow */
		u32 fragment_flag:1;		/* fragment / dont fragment */
		u32 reserved_flag:1;		/* reserved flag - gotta be zero */
		u16 offset:13;				/* fragment offset field */
#endif
		u8 time_to_live;			/* time to live */
		u8 protocol;				/* protocol */
		u16 checksum;				/* checksum */
		u32 source_address;			/* source address */
		u32 destination_address;	/* destination address */

		//! @brief default constructor
		ip_header_v4( void );

		//! @brief copy constructor
		ip_header_v4( const ip_header_v4& other );

		//! @brief destructor
		~ip_header_v4( void );

		//! @brief set header length
		void set_header_lenght( u32 h_lenght );

		//! @brief set version
		void set_version( u32 ver );

		//! @brief set TOS
		void set_type_of_service( u8 tos );

		//! @brief set total lenght
		void set_lenght( u16 t_lenght );

		//! @brief set identification
		void set_identification( u16 id );

		//! @brief set more fragments flag
		void set_more_fragments_flag( bool more_frag_flag );

		//! @brief set do fragment flag
		void set_fragment_flag( bool frag_flag );

		//! @brief set offset
		void set_offset( u16 off );

		//! @brief set time to live
		void set_time_to_live( u8 ttl );

		//! @brief set protocol type
		void set_protocol( ip_protocol prtcl );

		//! @brief create checksum
		void create_checksum( void );

		//! @brief set source address
		void set_source_address( address_ip4 src_address );

		//! @brief set destination address
		void set_destination_address( address_ip4 dst_address );
	};

	/*
	 *! @brief ipv6 header
	 */

	//! @todo create a v6 header - no idea if that one is correct!!
	struct ip6_header
	{
		/*
		 *! @brief data //taken from linux default, changed a little (anon. struct)
		 */

		union
		{
			struct// ip6_hdrctl
			{
				u32 flow_label;			/* 4 bits version, 8 bits TC,20 bits flow-ID */
				u16 payload_lenght;		/* payload length */
				u8  next_header;		/* next header */
				u8  hop_limit;			/* hop limit */
			}; // ip6_un1;

			u8 version_traffic_class;	/* 4 bits version, top 4 bits tclass */

		}; // ip6_ctlun;

		//address structure
		struct ip_field
		{
			u64 front_part;
			u64 back_part;
		};

		ip_field source_address;		/* source address */
		ip_field destination_address;	/* destination address */

		//! @brief default constructor
		ip6_header( void );

		//! @brief copy constructor
		ip6_header( const ip6_header& other );

		//! @brief destructor
		~ip6_header( void );

		//! @brief set version
		void set_version( u32 ver );

		//! @brief set traffic class
		void set_traffic_class( u32 tcl );

		//! @brief set flow label
		void set_flow_label( u32 flow );

		//! @brief set payload lenght
		void set_payload_lenght( u16 pay_lenght );

		//! @brief set next header
		void set_next_header( u8 hdr );

		//! @brief set hop limit
		void set_hop_limit( u8 hop_lmt );

		//! @brief set source address
		void set_source_address( address_ip6 src_address );

		//! @brief set destination address
		void set_destination_address( address_ip6 dst_address );

	  };

	/*
	 *! @brief udp header
	 */

	struct udp_header
	{
		//! @brief data
		u16 source_port;
		u16 destination_port;
		u16 lenght;
		u16 checksum;

		//! @brief default constructor
		udp_header( void );

		//! @brief copy constructor
		udp_header( const udp_header& other );

		//! @brief destructor
		~udp_header( void );

		//! @brief set source port
		void set_source_port( u16 prt );

		//! @brief set destination port
		void set_destination_port( u16 prt );

		//! @brief set lenght
		void set_lenght( u16 lenght );

		//! @brief creating checksum
		void create_checksum( void );
	};

	/*
	 *! @brief udp lite header
	 */

	struct udp_lite_header
	{
		//! @brief data
		u16 source_port;
		u16 destination_port;
		u32 checksum;

		//! @brief default constructor
		udp_lite_header( void );

		//! @brief copy constructor
		udp_lite_header( const udp_header& other );

		//! @brief destructor
		~udp_lite_header( void );

		//! @brief set source port
		void set_source_port( u16 prt );

		//! @brief set destination port
		void set_destination_port( u16 prt );

		//! @brief creating checksum
		void create_checksum( void );
	};

	/*
	 *! @brief tcp header
	 */

	struct tcp_header
	{
		//! @brief data
		u16 source_port;		//source port
		u16 destination_port;	//destination port
		u32 sequence;			//sequence number
		u32 acknowledge;		//acknowledged number
#if defined(CRAP_ENDIAN_LITTLE)
		u16 reserved1:4;		//reserved field
		u16 data_offset:4;		//header size in 32bit blocks (usually 5)
		u16 fin:1;				//FIN flag
		u16 syn:1;				//SYN flag
		u16 rst:1;				//RST flag
		u16 psh:1;				//PSH flag
		u16 ack:1;				//ACK flag
		u16 urg:1;				//URG flag
		u16 reserved2:2;		//reserved field
#else
		u16 data_offset:4;		//header isze in 32bit blocks (usually 5)
		u16 reserved1:4;		//reserved field
		u16 reserved2:2;		//reserved field
		u16 urg:1;				//URG flag
		u16 ack:1;				//ACK flag
		u16 psh:1;				//PSH flag
		u16 rst:1;				//RST flag
		u16 syn:1;				//SYN flag
		u16 fin:1;				//FIN flag
#endif
		u16 window;				//number of data octretts ready to get received
		u16 checksum;			//verification number over header, pseudo and data
		u16 urgent_pointer;		//urgent offset if flag is set

		//! @brief default constructor
		tcp_header( void );

		//! @brief copy constructor
		tcp_header( const tcp_header& other );

		//! @brief destructor
		~tcp_header( void );

		//! @brief set source port
		void set_source_port( u16 src_port );

		//! @brief set destination port
		void set_destination_port( u16 dst_port );

		//! @brief set sequence number
		void set_sequence_number( u32 sequence );

		//! @brief set acknowledge number
		void set_acknowledge_number( u32 acknowledge );

		//! @brief set data offset (usually 5) - 4 bit
		void set_data_offset( u16 offset );

		//! @brief set fin flag
		void set_fin_flag( bool fin );

		//! @brief set syn flag
		void set_syn_flag( bool syn );

		//! @brief set rst flag
		void set_rst_flag( bool rst );

		//! @brief set psh flag
		void set_psh_flag( bool psh );

		//! @brief set ack flag
		void set_ack_flag( bool ack );

		//! @brief set urg flag
		void set_urg_flag( bool urg );

		//! @brief set window size
		void set_window( u16 win );

		//! @brief create checksum
		void create_checksum( void );

		//! @brief set urgent offset
		void set_urgent( u16 urgnt );
	};

}	//namespace crap

#endif	// CRAP_NETWORK_IPHEADERS_H

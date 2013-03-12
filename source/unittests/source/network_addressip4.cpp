#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "network/addressip4.h"
#include "control/endian.h"

namespace
{

crap::address_ip4* _ip4;

TEST(NetworkAddressIP4Title)
{
    std::cout << "Testing \"network/addressip4.h\"" << std::endl;
}

TEST(NetworkAddressIP4Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_ip4 = new crap::address_ip4;
}

TEST(NetworkAddressIP4CopyConstructor)
{
	std::cout << "\tdoing tests..." << std::endl;
	crap::address_ip4 addr( *_ip4 );
	CHECK_EQUAL( _ip4->get_ip(), addr.get_ip() );
	CHECK_EQUAL( _ip4->get_port(), addr.get_port() );
}

TEST(NetworkAddressIP4Assignment)
{
	crap::address_ip4 addr;
	addr = *_ip4;

	CHECK_EQUAL( _ip4->get_ip(), addr.get_ip() );
	CHECK_EQUAL( _ip4->get_port(), addr.get_port() );
}

TEST(NetworkAddressIP4AdressPortConstructor)
{
	i32 add = 123456;
	i16 prt = 1024;
	crap::address_ip4 addr( add, prt );

#if defined( CRAP_PLATFORM_WIN )
	CHECK_EQUAL( htonl( add ), addr.socket_address.sin_addr.S_un.S_addr );
	CHECK_EQUAL( add, addr.get_ip() );
	CHECK_EQUAL( htons( prt ), addr.socket_address.sin_port );
	CHECK_EQUAL( prt, addr.get_port() );
#else
    CHECK_EQUAL( htonl( add ), addr.socket_address.sin_addr.s_addr );
    CHECK_EQUAL( add, addr.get_ip() );
    CHECK_EQUAL( htons( prt ), addr.socket_address.sin_port );
    CHECK_EQUAL( prt, addr.get_port() );
#endif
}

TEST(NetworkAddressIP4AdressDetailPortConstructor)
{
	u8 parts[4] = { 127,0,0,1 };
	u32 add = ( parts[0] << 24 ) | ( parts[1] << 16 ) | ( parts[2] << 8 ) | parts[3];
	i16 prt = 1024;
	crap::address_ip4 addr( parts[0], parts[1], parts[2], parts[3], prt );

#if defined( CRAP_PLATFORM_WIN )
    CHECK_EQUAL( htonl( add ), addr.socket_address.sin_addr.S_un.S_addr );
    CHECK_EQUAL( add, addr.get_ip() );
    CHECK_EQUAL( htons( prt ), addr.socket_address.sin_port );
    CHECK_EQUAL( prt, addr.get_port() );
#else
    CHECK_EQUAL( htonl( add ), addr.socket_address.sin_addr.s_addr );
    CHECK_EQUAL( add, addr.get_ip() );
    CHECK_EQUAL( htons( prt ), addr.socket_address.sin_port );
    CHECK_EQUAL( prt, addr.get_port() );
#endif
}

TEST(NetworkAddressIP4Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _ip4;
}

}   // namespace





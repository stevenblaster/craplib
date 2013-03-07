#include "UnitTest++.h"

//lib includes
#include "network/addressip6.h"

namespace
{

crap::address_ip6* _ip6;

TEST(NetworkAddressIP6Title)
{
    std::cout << "Testing \"network/addressip6.h\"" << std::endl;
}

TEST(NetworkAddressIP6Constructor)
{
	std::cout << "\tConstruction" << std::endl;
	_ip6 = new crap::address_ip6;
}

TEST(NetworkAddressIP6CopyConstructor)
{
	std::cout << "\tdoing tests... ip6 not useable yet (128 bit type probs on Winfuck)" << std::endl;
	crap::address_ip6 addr( *_ip6 );
	CHECK( _ip6->get_ip() == addr.get_ip() );
	CHECK( _ip6->get_port() == addr.get_port() );
}

TEST(NetworkAddressIP6Assignment)
{
	crap::address_ip6 addr;
	addr = *_ip6;

	CHECK( _ip6->get_ip() == addr.get_ip() );
	CHECK( _ip6->get_port() == addr.get_port() );
}

TEST(NetworkAddressIP6AdressPortConstructor)
{
#if defined( CRAP_COMPILER_GCC )
//	u128 add = 123456;
#else
	//u128 add;
	//add.part_64[1] = 123456;
#endif
//	i16 prt = 1024;
	//crap::address_ip6 addr( add, prt );
	//CHECK( add == addr.get_ip() );
	//CHECK_EQUAL( prt, addr.get_port() );
}

TEST(NetworkAddressIP6Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _ip6;
}

}   // namespace






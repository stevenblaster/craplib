#include "UnitTest++.h"

//lib includes
#include "network/addressip4.h"

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

TEST(NetworkAddressIP4Destructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _ip4;
}

}   // namespace





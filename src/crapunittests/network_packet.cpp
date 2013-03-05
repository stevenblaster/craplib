#include "UnitTest++.h"

//lib includes
#include "network/packet.h"
#include "network/addressip4.h"

namespace
{

crap::packet_ip4< 10 >* _pack;

TEST(NetworkPacketTitle)
{
    std::cout << "Testing \"network/packet.h\"" << std::endl;
}

TEST(NetworkPacketConstructor)
{
	std::cout << "\tConstruction" << std::endl;
	_pack = new crap::packet_ip4< 10 >();
}

TEST(NetworkPacketInfo)
{
	std::cout << "\tTests done with socket tests" << std::endl;
}

TEST(NetworkPacketDestructor)
{
	std::cout << "\tDestruction" << std::endl;
	delete _pack;
}

}   // namespace





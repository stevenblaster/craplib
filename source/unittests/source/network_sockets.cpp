#include "UnitTest++.h"
#include "crap.h"

//lib includes
#include "network/sockets.h"

namespace
{

crap::socket_udp_ip4* _sock_udp;
crap::socket_tcp_ip4* _sock_tcp;
crap::socket_tcp_ip4* _sock_tcp2;

TEST(NetworkSocketsTitle)
{
    std::cout << "Testing \"network/sockets.h\"" << std::endl;
}

TEST(NetworkSocketsConstructor)
{
	std::cout << "\tConstruction" << std::endl;
	_sock_udp = new crap::socket_udp_ip4();
	_sock_tcp = new crap::socket_tcp_ip4();
	_sock_tcp2 = new crap::socket_tcp_ip4();
}

TEST(NetworkSocketSetBlocking)
{
	_sock_udp->set_blocking(true);
	_sock_tcp->set_blocking(true);
	_sock_tcp2->set_blocking(true);
	_sock_udp->set_blocking(false);
	_sock_tcp->set_blocking(false);
	_sock_tcp2->set_blocking(false);
}

TEST(NetworkSocketInit)
{
	_sock_udp->init(12345);
	_sock_tcp->init(23456);
	_sock_tcp2->init(23465);
}

TEST(NetworkSocketUDPSend)
{
	crap::packet_ip4<10> pack_ip4;
	pack_ip4.address = crap::address_ip4( 127, 0, 0, 1, 12345 );
	char txt[10] = {'H', 'a', 'l', 'l', 'o', '!', '\0', '\0', '\0', '\0'};
	memcpy( pack_ip4.data, txt, 10 );
	_sock_udp->send( pack_ip4 );
	printf("\tUDP - sent: %s\n", pack_ip4.data );
}

TEST(NetworkSocketUDPReceive)
{
	crap::packet_ip4<10> pack_ip4;
	pack_ip4.address = crap::address_ip4::any;
	_sock_udp->receive( pack_ip4 );
	printf("\tUDP - received: %s\n", pack_ip4.data );
}

TEST(NetworkSocketTCPListen)
{
	_sock_tcp->listen();
}

TEST(NetworkSocketTCPConnect)
{
	crap::packet_ip4<10> pack_ip4;
	pack_ip4.address = crap::address_ip4( 127, 0, 0, 1, 23456 );

	_sock_tcp2->connect( pack_ip4.address );
}

TEST(NetworkSocketTCPAccept)
{
	crap::packet_ip4<10> pack_ip4;
	pack_ip4.address = crap::address_ip4( 127, 0, 0, 1, 23465 );

	_sock_tcp->accept( pack_ip4.address );
}

TEST(NetworkSocketTCPwriteClientServer)
{
	crap::packet_ip4<10> pack_ip4;
	pack_ip4.address = crap::address_ip4( 127, 0, 0, 1, 23456 );
	char txt[10] = {'H', 'a', 'l', 'l', 'o', '!', '\0', '\0', '\0', '\0'};
	memcpy( pack_ip4.data, txt, 10 );

	_sock_tcp2->send( pack_ip4 );
	printf("\tTCP - sent: %s\n", pack_ip4.data );
}

TEST(NetworkSocketTCPreadServer)
{
	crap::packet_ip4<10> pack_ip4;
	pack_ip4.address = crap::address_ip4( 127, 0, 0, 1, 23465 );

	_sock_tcp->receive( pack_ip4 );
	printf("\tTCP - received: %s\n", pack_ip4.data );
}

TEST(NetworkSocketDeinit)
{
	_sock_udp->deinit();
	_sock_tcp->deinit();
}

TEST(NetworkSocketsDestruction)
{
	std::cout << "\tDestruction" << std::endl;
	delete _sock_udp;
	delete _sock_tcp;
}

}   // namespace







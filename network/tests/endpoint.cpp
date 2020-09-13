#include <catch2/catch.hpp>
#include <network/ip/tcp.hpp>

using network::ip::address;
using network::ip::tcp;

TEST_CASE("Default constructor", "[endpoint]")
{
	tcp::endpoint ep;

	sockaddr* data = ep.data();

	//REQUIRE(data->sa_family == AF_INET);

	REQUIRE(ep.address().to_v4() == address::v4::any());
	REQUIRE(ep.port() == 0);
	REQUIRE(ep.size() == 16);
	REQUIRE(ep.is_v4());
	REQUIRE_FALSE(ep.is_v6());
}

TEST_CASE("Protocol constructor", "[endpoint]")
{
	tcp::endpoint ep(tcp::v6());

	sockaddr* data = ep.data();

	//REQUIRE(data->sa_family == AF_INET6);

	REQUIRE(ep.address().to_v6() == address::v6::any());
	REQUIRE(ep.port() == 0);
	REQUIRE(ep.size() == 28);
	REQUIRE_FALSE(ep.is_v4());
	REQUIRE(ep.is_v6());
}

TEST_CASE("Protocol/port constructor", "[endpoint]")
{
	tcp::endpoint ep(tcp::v4(), 400);

	sockaddr* data = ep.data();

	//REQUIRE(data->sa_family == AF_INET);

	REQUIRE(ep.address().to_v4() == address::v4::any());
	REQUIRE(ep.port() == 400);
	REQUIRE(ep.size() == 16);
	REQUIRE(ep.is_v4());
	REQUIRE_FALSE(ep.is_v6());
}

TEST_CASE("Address constructors", "[endpoint]")
{
	tcp::endpoint ep(address::v4::any(), 1000);

	sockaddr* data = ep.data();

	//REQUIRE(data->sa_family == AF_INET);

	REQUIRE(ep.port() == 1000);
	REQUIRE(ep.size() == 16);
	REQUIRE(ep.is_v4());
	REQUIRE_FALSE(ep.is_v6());

	tcp::endpoint ep2(address::v6::loopback(), 555);

	data = ep2.data();

	//REQUIRE(data->sa_family == AF_INET6);

	REQUIRE(ep2.port() == 555);
	REQUIRE(ep2.size() == 28);
	REQUIRE_FALSE(ep2.is_v4());
	REQUIRE(ep2.is_v6());
}

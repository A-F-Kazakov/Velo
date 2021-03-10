#include <catch2/catch.hpp>
#include <network/ip/tcp.hpp>

using network::ip::address;
using network::ip::tcp;

TEST_CASE("Endpoint can be defaul constructed", "[endpoint]")
{
	tcp::endpoint ep;

	CHECK(ep.address().to_v4() == address::v4::any());
	CHECK_THROWS_AS(ep.address().to_v6(), std::bad_cast);
	CHECK(ep.port() == 0);
	CHECK(ep.size() == 16);
	CHECK(ep.is_v4());
	CHECK_FALSE(ep.is_v6());
}

TEST_CASE("Endpoint can be constructed via ipv6 protocol", "[endpoint]")
{
	tcp::endpoint ep{tcp::v6()};

	CHECK_THROWS_AS(ep.address().to_v4(), std::bad_cast);
	CHECK(ep.address().to_v6() == address::v6::any());
	CHECK(ep.port() == 0);
	CHECK(ep.size() == 28);
	CHECK_FALSE(ep.is_v4());
	CHECK(ep.is_v6());
}

TEST_CASE("Endpoint can be constructed via ipv4 protocol", "[endpoint]")
{
	tcp::endpoint ep{tcp::v4()};

	CHECK(ep.address().to_v4() == address::v4::any());
	CHECK_THROWS_AS(ep.address().to_v6(), std::bad_cast);
	CHECK(ep.port() == 0);
	CHECK(ep.size() == 16);
	CHECK(ep.is_v4());
	CHECK_FALSE(ep.is_v6());
}

TEST_CASE("Endpoint can be constructed via protocol and port number", "[endpoint]")
{
	tcp::endpoint ep{tcp::v4(), 400};

	CHECK(ep.address().to_v4() == address::v4::any());
	CHECK_THROWS_AS(ep.address().to_v6(), std::bad_cast);
	CHECK(ep.port() == 400);
	CHECK(ep.size() == 16);
	CHECK(ep.is_v4());
	CHECK_FALSE(ep.is_v6());
}

TEST_CASE("Encpoint can be constructed via specific address", "[endpoint]")
{
	tcp::endpoint ep{address::v4::any(), 1000};

	sockaddr* data = ep.data();

	CHECK(ep.port() == 1000);
	CHECK(ep.size() == 16);
	CHECK(ep.is_v4());
	CHECK_FALSE(ep.is_v6());

	tcp::endpoint ep2{address::v6::loopback(), 555};

	CHECK(ep2.port() == 555);
	CHECK(ep2.size() == 28);
	CHECK_FALSE(ep2.is_v4());
	CHECK(ep2.is_v6());
}

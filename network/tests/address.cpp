#include <catch2/catch.hpp>
#include <network/ip/address.hpp>

using network::ip::address;

TEST_CASE("Address can be consructed from address v4", "[address]")
{
	address addr{address::v4::any()};

	REQUIRE(addr.to_string() == "0.0.0.0");
	REQUIRE(addr.is_v4());
	REQUIRE_FALSE(addr.is_v6());
	REQUIRE_FALSE(addr.is_loopback());
	REQUIRE(addr.is_unspecified());
	REQUIRE_FALSE(addr.is_multicast());
	REQUIRE(addr.to_v4() == address::v4::any());
	REQUIRE_THROWS_AS(addr.to_v6(), std::bad_cast);
}

TEST_CASE("Adress can be constructed from address v6", "[address]")
{
	address addr{address::v6::any()};

	REQUIRE(addr.to_string() == "::");
	REQUIRE_FALSE(addr.is_v4());
	REQUIRE(addr.is_v6());
	REQUIRE_FALSE(addr.is_loopback());
	REQUIRE(addr.is_unspecified());
	REQUIRE_FALSE(addr.is_multicast());
	REQUIRE(addr.to_v6() == address::v6::any());
	REQUIRE_THROWS_AS(addr.to_v4(), std::bad_cast);
}

TEST_CASE("Address is copyable", "[address]")
{
	address addr_old{address::v6::any()};
	address addr{addr_old};

	REQUIRE(addr.to_string() == "::");
	REQUIRE_FALSE(addr.is_v4());
	REQUIRE(addr.is_v6());
	REQUIRE_FALSE(addr.is_loopback());
	REQUIRE(addr.is_unspecified());
	REQUIRE_FALSE(addr.is_multicast());
	REQUIRE(addr.to_v6() == address::v6::any());
	REQUIRE_THROWS_AS(addr.to_v4(), std::bad_cast);
}

TEST_CASE("Address is movable", "[address]")
{
	address addr_old{address::v6::any()};
	address addr{std::move(addr_old)};

	REQUIRE(addr.to_string() == "::");
	REQUIRE_FALSE(addr.is_v4());
	REQUIRE(addr.is_v6());
	REQUIRE_FALSE(addr.is_loopback());
	REQUIRE(addr.is_unspecified());
	REQUIRE_FALSE(addr.is_multicast());
	REQUIRE(addr.to_v6() == address::v6::any());
	REQUIRE_THROWS_AS(addr.to_v4(), std::bad_cast);
}

TEST_CASE("Address can compare", "[address]")
{
	address addr1{address::v4::any()};
	address addr2{address::v6::any()};
	address addr3{address::v4::from_str("0.0.0.0")};

	REQUIRE(addr1 != addr2);
	REQUIRE(addr1 == addr3);
}

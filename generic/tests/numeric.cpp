#include <catch2/catch.hpp>
#include <generic/numeric.hpp>

TEST_CASE("integer can act like uint8_t", "[integer]")
{
	using u8 = generic::integer<8, uint8_t>;

	CHECK(sizeof(u8) == 1);
	CHECK(u8::size == 1);
	CHECK(u8::min == 0);
	CHECK(u8::max == UINT8_MAX);

	u8 num;

	CHECK(num == 0);

	num = 55;

	CHECK(num == 55);

	int cast = num;

	CHECK(cast == 55);

	char c = 50;

	u8 num1{&c};

	CHECK(num1 == 50);

	u8 num2{2000};

	CHECK(num2 == 255);

	u8 num3{-2000};

	CHECK(num3 == 0);
}

/**
 * @author	Казаков Андрей
 * @date	05.08.17.
 */

#include "numeric.h"

#define BOOST_TEST_MODULE generic_numbers

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(integer_class)

	BOOST_AUTO_TEST_CASE(unsigned8)
	{
		using u8 = generic::integer<8, uint8_t>;

		BOOST_CHECK(sizeof(u8) == 1);
		BOOST_CHECK(u8::size == 1);
		BOOST_CHECK(u8::min == 0);
		BOOST_CHECK(u8::max == UINT8_MAX);

		u8 num;

		BOOST_CHECK_EQUAL(num, 0);

		num = 55;

		BOOST_CHECK_EQUAL(num, 55);

		int cast = num;

		BOOST_CHECK_EQUAL(cast, 55);

		char c = 50;

		u8 num1(&c);

		BOOST_CHECK_EQUAL(num1, 50);

		u8 num2(2000);

		BOOST_CHECK_EQUAL(num2, 255);

		u8 num3(-2000);

		BOOST_CHECK_EQUAL(num3, 0);
	}

BOOST_AUTO_TEST_SUITE_END()
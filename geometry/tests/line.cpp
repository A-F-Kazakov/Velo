#include <catch2/catch.hpp>
#include <geometry/flat/line.hpp>

using line2d = geometry::flat::line<double>;

TEST_CASE("Line can be default constructable", "[line]")
{
	line2d l;

	CHECK(l.a() == 0);
	CHECK(l.b() == 0);
	CHECK(l.c() == 0);
}	

TEST_CASE("Line can be constructed via coefficients", "[line]")
{
	line2d l1{1, 3, 6};

	CHECK(l1.a() == 1);
	CHECK(l1.b() == 3);
	CHECK(l1.c() == 6);
}

TEST_CASE("Line can be constructed via two points", "[line]")
{
	line2d l2{{2, 5}, {10, 9}};

	CHECK(l2.a() == -4);
	CHECK(l2.b() == 8);
	CHECK(l2.c() == -32);
}

TEST_CASE("Line can be normalized", "[line]")
{
	line2d l{{2, 5}, {10, 9}};
	l.normalize();

	REQUIRE_THAT(l.a(), Catch::Matchers::WithinRel(-0.5, 0.001));
	REQUIRE_THAT(l.b(), Catch::Matchers::WithinRel(1, 0.0001));
	REQUIRE_THAT(l.c(), Catch::Matchers::WithinRel(-4, 0.0001));
}

		//l1 = {4, -2, -2};

//		point p = l1.get_point_on_line(0, axes::OX);

//		BOOST_CHECK_EQUAL(p.x, 0);
//		BOOST_CHECK_EQUAL(p.y, -1);
//
//		p = l1.get_point_on_line(0, axes::OY);
//
//		BOOST_CHECK_EQUAL(p.x, 0.5);
//		BOOST_CHECK_EQUAL(p.y, 0);
//
//		line2d l2(4, 3, -1);
//
//		BOOST_CHECK(l2.contains({3,5}));
//
//		l1 = {1, 0, -2};
//		l2 = {0, 1, -2};

//		point intersection;
//
//		BOOST_CHECK(geometry::two_dimensional::intersection_point(l1, l2, intersection));
//
//		BOOST_CHECK_EQUAL(intersection.x, 2);
//		BOOST_CHECK_EQUAL(intersection.y, 2);
	//}

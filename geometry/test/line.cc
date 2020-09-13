/**
 * @author   Казаков Андрей 
 * @date     25.02.19.
 */

#include <boost/test/unit_test.hpp>

#include <geometry/flat/line.hh>

using line2d = geometry::flat::line<double>;

BOOST_AUTO_TEST_SUITE(line2d_class)

	BOOST_AUTO_TEST_CASE(constructors)
	{
		line2d l;

		BOOST_CHECK_EQUAL(l.a(), 0);
		BOOST_CHECK_EQUAL(l.b(), 0);
		BOOST_CHECK_EQUAL(l.c(), 0);

		line2d l1(1, 3, 6);

		BOOST_CHECK_EQUAL(l1.a(), 1);
		BOOST_CHECK_EQUAL(l1.b(), 3);
		BOOST_CHECK_EQUAL(l1.c(), 6);

		line2d l2({2, 5}, {10, 9});

		BOOST_CHECK_EQUAL(l2.a(), -4);
		BOOST_CHECK_EQUAL(l2.b(), 8);
		BOOST_CHECK_EQUAL(l2.c(), -32);

		l2.normalize();

		BOOST_CHECK_CLOSE(l1.a(), -0.5, 0.001);
		BOOST_CHECK_CLOSE(l1.b(), 1, 0.0001);
		BOOST_CHECK_CLOSE(l1.c(), -4, 0.0001);

		l1 = {4, -2, -2};

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
	}

BOOST_AUTO_TEST_SUITE_END()
/**
 * @author   Казаков Андрей 
 * @date     25.02.19.
 */

#include <boost/test/unit_test.hpp>

#include <geometry/flat/point.hh>
#include <geometry/spatial/point.hh>

using point2d = geometry::flat::point<double>;
using point3d = geometry::spatial::point<double>;

BOOST_AUTO_TEST_SUITE(point2d_class)

	BOOST_AUTO_TEST_CASE(constructors)
	{
		point2d p;

		BOOST_CHECK_EQUAL(p.x(), 0);
		BOOST_CHECK_EQUAL(p.y(), 0);

		point2d p1(12, 9.7);

		BOOST_CHECK_EQUAL(p1.x(), 12);
		BOOST_CHECK_EQUAL(p1.y(), 9.7);

		point2d p2(p1);

		BOOST_CHECK_EQUAL(p2.x(), 12);
		BOOST_CHECK_EQUAL(p2.y(), 9.7);

		point2d p3{34, 98};

		BOOST_CHECK_EQUAL(p3.x(), 34);
		BOOST_CHECK_EQUAL(p3.y(), 98);

		point2d p4({45, 9.4});

		BOOST_CHECK_EQUAL(p4.x(), 45);
		BOOST_CHECK_EQUAL(p4.y(), 9.4);
	}

	BOOST_AUTO_TEST_CASE(assignments)
	{
		point2d p0(3.6, 88);

		point2d p1 = p0;

		BOOST_CHECK_EQUAL(p1.x(), 3.6);
		BOOST_CHECK_EQUAL(p1.y(), 88);

		point2d p2 = {12, 98};

		BOOST_CHECK_EQUAL(p2.x(), 12);
		BOOST_CHECK_EQUAL(p2.y(), 98);
	}

	BOOST_AUTO_TEST_CASE(comparisson)
	{
		point2d p0;
		point2d p1;

		BOOST_CHECK(p0 == p1);
		BOOST_CHECK(!(p0 != p1));

		point2d p2(23, 78);

		BOOST_CHECK(!(p2 == p1));
		BOOST_CHECK(p2 != p1);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(point3d_class)

	BOOST_AUTO_TEST_CASE(constructors)
	{
		point3d p;

		BOOST_CHECK_EQUAL(p.x(), 0);
		BOOST_CHECK_EQUAL(p.y(), 0);
		BOOST_CHECK_EQUAL(p.z(), 0);

		point3d p1(12, 9.7, 5.88);

		BOOST_CHECK_EQUAL(p1.x(), 12);
		BOOST_CHECK_EQUAL(p1.y(), 9.7);
		BOOST_CHECK_EQUAL(p1.z(), 5.88);

		point3d p2(p1);

		BOOST_CHECK_EQUAL(p2.x(), 12);
		BOOST_CHECK_EQUAL(p2.y(), 9.7);
		BOOST_CHECK_EQUAL(p1.z(), 5.88);

		point3d p3{34, 98, -55};

		BOOST_CHECK_EQUAL(p3.x(), 34);
		BOOST_CHECK_EQUAL(p3.y(), 98);
		BOOST_CHECK_EQUAL(p3.z(), -55);

		point3d p4({45, 9.4, 8839});

		BOOST_CHECK_EQUAL(p4.x(), 45);
		BOOST_CHECK_EQUAL(p4.y(), 9.4);
		BOOST_CHECK_EQUAL(p4.z(), 8839);
	}

	BOOST_AUTO_TEST_CASE(assignments)
	{
		point3d p0(3.6, 88, 15);

		point3d p1 = p0;

		BOOST_CHECK_EQUAL(p1.x(), 3.6);
		BOOST_CHECK_EQUAL(p1.y(), 88);
		BOOST_CHECK_EQUAL(p1.z(), 15);

		point3d p2 = {12, 98, 96};

		BOOST_CHECK_EQUAL(p2.x(), 12);
		BOOST_CHECK_EQUAL(p2.y(), 98);
		BOOST_CHECK_EQUAL(p2.z(), 96);
	}

	BOOST_AUTO_TEST_CASE(comparisson)
	{
		point3d p0;
		point3d p1;

		BOOST_CHECK(p0 == p1);
		BOOST_CHECK(!(p0 != p1));

		point3d p2(23, 78, 876);

		BOOST_CHECK(!(p2 == p1));
		BOOST_CHECK(p2 != p1);
	}

BOOST_AUTO_TEST_SUITE_END()

#include <geometry/algorythms/distance.hpp>
#include <geometry/flat/point.hpp>
#include <geometry/flat/line.hpp>
#include <geometry/spatial/point.hpp>

using point2d = geometry::flat::point<double>;
using line2d = geometry::flat::line<double>;
using point3d = geometry::spatial::point<double>;

/*
BOOST_AUTO_TEST_SUITE(distance)

	BOOST_AUTO_TEST_CASE(point2d_to_point2d)
	{
		point2d p1;
		point2d p2(100, 100);

		auto value = geometry::distance(p1, p2);

		BOOST_CHECK_CLOSE(value, 141.421, 0.001);
	}

	BOOST_AUTO_TEST_CASE(point3d_to_point3d)
	{
		point3d p1;
		point3d p2(100, 100, 100);

		auto value = geometry::distance(p1, p2);

		BOOST_CHECK_CLOSE(value, 173.205, 0.001);
	}

	BOOST_AUTO_TEST_CASE(point2d_to_line2d)
	{
		point2d p1;
		line2d l1(-1, 1, -7);

		auto value = geometry::distance(p1, l1);

		BOOST_CHECK_CLOSE(value, 4.9497, 0.001);
	}

BOOST_AUTO_TEST_SUITE_END()
*/
int main(){}

#include <geometry/algorythms/intersect.hpp>
#include <geometry/flat/line.hpp>

using line2d = geometry::flat::line<double>;
using point2d = geometry::flat::point<double>;

/*
BOOST_AUTO_TEST_SUITE(intersect2d)

	BOOST_AUTO_TEST_CASE(line_to_line)
	{
		line2d l1({1, 1}, {6, 6});
		line2d l2({5, 2}, {3, 6});

		point2d value = geometry::intersect(l1, l2);

		BOOST_CHECK_CLOSE(value.x(), 4, 0.001);
		BOOST_CHECK_CLOSE(value.y(), 4, 0.001);
	}

BOOST_AUTO_TEST_SUITE_END()
*/
int main() {}

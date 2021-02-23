#include <catch2/catch.hpp>
#include <geometry/algorythms/intersect.hpp>
#include <geometry/flat/line.hpp>

using line2d = geometry::flat::line<double>;
using point2d = geometry::flat::point<double>;

TEST_CASE("Function can calculate intersection of 2 2d points", "[intersect]")
{
	line2d l1({1, 1}, {6, 6});
	line2d l2({5, 2}, {3, 6});

	point2d value = geometry::intersect(l1, l2);

	REQUIRE_THAT(value.x(), Catch::Matchers::WithinRel(4, 0.0001));
	REQUIRE_THAT(value.y(), Catch::Matchers::WithinRel(4, 0.0001));
}

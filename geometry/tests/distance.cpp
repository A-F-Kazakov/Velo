#include <catch2/catch.hpp>
#include <geometry/algorythms/distance.hpp>
#include <geometry/flat/point.hpp>
#include <geometry/flat/line.hpp>
#include <geometry/spatial/point.hpp>

using point2d = geometry::flat::point<double>;
using line2d = geometry::flat::line<double>;
using point3d = geometry::spatial::point<double>;

TEST_CASE("Can measure distance between two 2d points", "[distance]")
{
	point2d p1;
	point2d p2{100, 100};

	auto value = geometry::distance(p1, p2);

	REQUIRE_THAT(value, Catch::Matchers::WithinRel(141.421, 0.001));
}

TEST_CASE("Can measure distance between two 3d points", "[distance]")
{
	point3d p1;
	point3d p2{100, 100, 100};

	auto value = geometry::distance(p1, p2);

	REQUIRE_THAT(value, Catch::Matchers::WithinRel(173.205, 0.001));
}

TEST_CASE(" Can measure distance between 2d point and ine", "[distance]")
{
	point2d p1;
	line2d l1{-1, 1, -7};

	auto value = geometry::distance(p1, l1);

	REQUIRE_THAT(value, Catch::Matchers::WithinRel(4.9497, 0.001));
}

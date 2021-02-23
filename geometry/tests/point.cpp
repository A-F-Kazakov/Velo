#include <catch2/catch.hpp>
#include <geometry/flat/point.hpp>
#include <geometry/spatial/point.hpp>

using point2d = geometry::flat::point<double>;
using point3d = geometry::spatial::point<double>;

TEST_CASE("Point can be default constructable", "[point]")
{
	point2d p;

	CHECK(p.x() == 0);
	CHECK(p.y() == 0);
}

TEST_CASE("Point can be constructed via pair of numbers", "[point]")
{
	point2d p1{12, 9.7};

	CHECK(p1.x() == 12);
	CHECK(p1.y() == 9.7);
}

TEST_CASE("Point can be copy constructable", "[point]")
{
	point2d p1{12, 9.7};
	point2d p2{p1};

	CHECK(p2.x() == 12);
	CHECK(p2.y() == 9.7);

	CHECK(p2.x() == p1.x());
	CHECK(p2.y() == p1.y());
}

TEST_CASE("Point can be move constructable", "[point]")
{
	point2d p4{point2d{45, 9.4}};

	CHECK(p4.x() == 45);
	CHECK(p4.y() == 9.4);
}

TEST_CASE("Point can be copy assignable", "[point]")
{
	point2d p0{3.6, 88};

	point2d p1 = p0;

	CHECK(p1.x() == 3.6);
	CHECK(p1.y() == 88);

	CHECK(p1.x() == p0.x());
	CHECK(p1.y() == p0.y());
}

TEST_CASE("Point can be move assignable", "[point]")
{
	point2d p2 = {12, 98};

	CHECK(p2.x() == 12);
	CHECK(p2.y() == 98);
}

TEST_CASE("Points can compare", "[point]")
{
	point2d p0;
	point2d p1;

	CHECK(p0 == p1);
	CHECK_FALSE(p0 != p1);

	point2d p2{23, 78};

	CHECK_FALSE(p2 == p1);
	CHECK(p2 != p1);
}

/**
 * @author   Казаков Андрей 
 * @date     03.09.19.
 */

#ifndef GEOMETRY_INTERSECT_HH
#define GEOMETRY_INTERSECT_HH

#include <cmath>
#include "geometry/traits.hh"

namespace geometry
{
	namespace dispatch
	{
		const double EPS = 1e-9;

		double determinant(double a, double b, double c, double d){ return a * d - b * c; }

		template<typename Tag1, typename Tag2, typename G1, typename G2>
		struct intersect{};

		template<typename T1, typename T2>
		struct intersect<traits::line_tag, traits::line_tag, T1, T2>
		{
			static typename T1::point_type apply(const T1& a, const T2& b)
			{
				double zn = determinant(a.a(), a.b(), b.a(), b.b());
				if(std::abs(zn) < EPS)
					return {0, 0};
				double x = -determinant(a.c(), a.b(), b.c(), b.b()) / zn;
				double y = -determinant(a.a(), a.c(), b.a(), b.c()) / zn;
				return {x, y};
			}
		};
	}

	template<typename T1, typename T2>
	auto intersect(const T1& p1, const T2& p2)
	{
		return dispatch::intersect<typename traits::tag<T1>::type, typename traits::tag<T2>::type, T1, T2>::apply(p1, p2);
	}
}

#endif //GEOMETRY_INTERSECT_HH

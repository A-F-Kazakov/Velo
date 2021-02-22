#ifndef VELO_GEOMETRY_DISTANCE_HPP
#define VELO_GEOMETRY_DISTANCE_HPP

#include <cmath>
#include <geometry/traits.hpp>

namespace geometry
{
	namespace dispatch
	{
		template<typename T1, typename T2, int Size>
		struct pythagoras
		{
			static double apply(const T1& p1, const T2& p2)
			{
				double d = traits::get<Size - 1>(p1) - traits::get<Size - 1>(p2);
				return d * d + pythagoras<T1, T2, Size - 1>::apply(p1, p2);
			}
		};

		template<typename T1, typename T2>
		struct pythagoras<T1, T2, 0>{ static double apply(const T1& p1, const T2& p2){ return 0; }};

		template<typename Tag1, typename Tag2, typename G1, typename G2>
		struct distance{};

		template<typename T1, typename T2>
		struct distance<traits::point_tag, traits::point_tag, T1, T2>
		{
			static double apply(const T1& a, const T2& b)
			{
				static_assert(traits::dimension<T1>::value == traits::dimension<T2>::value);
				return sqrt(pythagoras<T1, T2, traits::dimension<T1>::value>::apply(a, b));
			}
		};

		template<typename P1, typename P2>
		struct distance<traits::point_tag, traits::line_tag, P1, P2>
		{
			static double apply(const P1& a, const P2& b)
			{
				return std::abs(traits::get<0>(b) * traits::get<0>(a) +
				                traits::get<1>(b) * traits::get<1>(a) +
				                traits::get<2>(b))/
				                std::sqrt(std::pow(traits::get<0>(b), 2) + std::pow(traits::get<1>(b), 2));
			}
		};
	}

	template<typename T1, typename T2>
	double distance(const T1& p1, const T2& p2)
	{
		return dispatch::distance<typename traits::tag<T1>::type, typename traits::tag<T2>::type, T1, T2>::apply(p1, p2);
	}
}

#endif //GEOMETRY_DISTANCE_H

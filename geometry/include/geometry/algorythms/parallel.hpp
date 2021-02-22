#ifndef VELO_GEOMETRY_PARALLEL_HPP
#define VELO_GEOMETRY_PARALLEL_HPP

#include <cmath>
#include <geometry/traits.hpp>

namespace geometry
{
	bool parallel(line m, line n)
	{
		return std::abs(determinant(m.a(), m.b(), n.a(), n.b())) < EPS;
	}
}

#endif

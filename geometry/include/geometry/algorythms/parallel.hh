/**
 * @author   Казаков Андрей 
 * @date     03.09.19.
 */

#ifndef GEOMETRY_PARALLEL_HH
#define GEOMETRY_PARALLEL_HH

#include <cmath>
#include "geometry/traits.hh

namespace geometry
{
	bool parallel(line m, line n)
	{
		return std::abs(determinant(m.a(), m.b(), n.a(), n.b())) < EPS;
	}
}

#endif //GEOMETRY_PARALLEL_HH

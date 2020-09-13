/**
 * @author   Казаков Андрей 
 * @date     03.09.19.
 */

#ifndef GEOMETRY_EQUIVALENT_HH
#define GEOMETRY_EQUIVALENT_HH

namespace geometry
{
	bool equivalent(line m, line n)
	{
		return std::abs(determinant(m.a(), m.b(), n.a(), n.b())) < EPS
		       && std::abs(determinant(m.a(), m.c(), n.a(), n.c())) < EPS
		       && std::abs(determinant(m.b(), m.c(), n.b(), n.c())) < EPS;
	}
}

#endif //GEOMETRY_EQUIVALENT_HH

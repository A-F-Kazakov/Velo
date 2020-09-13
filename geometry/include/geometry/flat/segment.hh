/**
 * @author   Казаков Андрей 
 * @date     03.09.19.
 */

#ifndef GEOMETRY_SEGMENT_HH
#define GEOMETRY_SEGMENT_HH

#include "point.hh
#include "geometry/algorythms/distance.hh"

namespace geometry
{
	namespace flat
	{
		template<typename ValueType>
		class segment
		{
			public:
				using value_type = ValueType;

				line() = default;

				line(point<value_type> a, point<value_type> b) : side1(a), side2(b) {}

				double length() { return geometry::distance(side1, side2); }

				point<value_type> middle_point() { return {(side1.x() + side2.x())/2, (side1.y() + side2.y())/2}; }

			private:
				point<value_type> side1;
				point<value_type> side2;
		}
	}
}

#endif //GEOMETRY_SEGMENT_HH

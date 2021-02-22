#ifndef VELO_GEOMETRY_SEGMENT_HPP
#define VELO_GEOMETRY_SEGMENT_HPP

#include "point.hpp"
#include <geometry/algorythms/distance.hpp>

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

#endif

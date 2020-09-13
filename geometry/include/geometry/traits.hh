/**
 * @author   Казаков Андрей 
 * @date     25.08.19.
 */

#ifndef GEOMETRY_TRAITS_H
#define GEOMETRY_TRAITS_H

namespace geometry::traits
{
	struct point_tag{};
	struct line_tag{};

	template<typename T>
	struct tag{};

	template<typename T>
	struct dimension{};

	template<typename T>
	struct coordinate_type{};

	template<typename T>
	struct coordinate_system{};

	template<typename T, int Index>
	struct access{};

	template<int Index, typename T>
	inline double get(const T& t){ return traits::access<T, Index>::get(t); }

	template<int Index, typename T>
	inline double set(const T& t, const double value){ return traits::access<T, Index>::set(t, value); }
}

#endif //GEOMETRY_TRAITS_H

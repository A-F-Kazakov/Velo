#ifndef VELO_GEOMETRY_SPATIAL_POINT_HPP
#define VELO_GEOMETRY_SPATIAL_POINT_HPP

#include "geometry/basic_point.hpp"
#include "geometry/traits.hpp"

namespace geometry
{
	namespace spatial
	{
		template<typename ValueType>
		class point : public basic_point<ValueType, 3>
		{
			public:
				using value_type = typename basic_point<ValueType, 3>::value_type;

				point() = default;

				inline point(value_type x, value_type y, value_type z) :
					basic_point<value_type, 3>(std::move(x), std::move(y), std::move(z)){}

				inline const value_type& x() const{ return this->template get<0>(); }
				inline const value_type& y() const{ return this->template get<1>(); }
				inline const value_type& z() const{ return this->template get<2>(); }

				inline void x(const value_type& v){ this->template set<0>(v); }
				inline void y(const value_type& v){ this->template set<1>(v); }
				inline void z(const value_type& v){ this->template set<2>(v); }

				inline void x(value_type&& v){ this->template set<0>(std::move(v)); }
				inline void y(value_type&& v){ this->template set<1>(std::move(v)); }
				inline void z(value_type&& v){ this->template set<2>(std::move(v)); }
		};
	}

	namespace traits
	{
		template<typename T>
		struct tag<spatial::point<T>>{ using type = point_tag; };

		template<typename T>
		struct dimension<spatial::point<T>>{ enum{ value = 3 }; };

		template<typename T>
		struct coordinate_type<spatial::point<T>>{ using type = T; };

		template<typename T>
		struct access<spatial::point<T>, 0>
		{
			static inline double get(const spatial::point<T>& p){ return p.x(); }
			static inline double set(const spatial::point<T>& p, const T value){ return p.x(value); }
		};

		template<typename T>
		struct access<spatial::point<T>, 1>
		{
			static inline double get(const spatial::point<T>& p){ return p.y(); }
			static inline double set(const spatial::point<T>& p, const T value){ return p.y(value); }
		};

		template<typename T>
		struct access<spatial::point<T>, 2>
		{
			static inline double get(const spatial::point<T>& p){ return p.z(); }
			static inline double set(const spatial::point<T>& p, const T value){ return p.z(value); }
		};
	}
}

#endif

#ifndef VELO_GEOMETRY_FLAT_POINT_HPP
#define VELO_GEOMETRY_FLAT_POINT_HPP

#include <geometry/basic_point.hpp>
#include <geometry/traits.hpp>

namespace geometry
{
	namespace flat
	{
		template<typename ValueType>
		class point : public basic_point<ValueType, 2>
		{
			public:
				using value_type = typename basic_point<ValueType, 2>::value_type;

				point() = default;

				inline point(value_type x, value_type y) : basic_point<value_type, 2>(std::move(x), std::move(y)){}

				inline const value_type& x() const{ return this->template get<0>(); }
				inline const value_type& y() const{ return this->template get<1>(); }

				inline void x(const value_type& v){ this->template set<0>(v); }
				inline void y(const value_type& v){ this->template set<1>(v); }

				inline void x(value_type&& v){ this->template set<0>(std::move(v)); }
				inline void y(value_type&& v){ this->template set<1>(std::move(v)); }
		};
	}

	namespace traits
	{
		template<typename T>
		struct tag<flat::point<T>>{ using type = point_tag; };

		template<typename T>
		struct dimension<flat::point<T>>{ enum{ value = 2 }; };

		template<typename T>
		struct coordinate_type<flat::point<T>>{ using type = T; };

		template<typename T>
		struct access<flat::point<T>, 0>
		{
			static inline double get(const flat::point<T>& p){ return p.x(); }
			static inline double set(const flat::point<T>& p, const T value){ return p.x(value); }
		};

		template<typename T>
		struct access<flat::point<T>, 1>
		{
			static inline double get(const flat::point<T>& p){ return p.y(); }
			static inline double set(const flat::point<T>& p, const T value){ return p.y(value); }
		};
	}
}

#endif

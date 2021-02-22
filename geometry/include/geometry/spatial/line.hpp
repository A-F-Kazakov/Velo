#ifndef VELO_GEOMETRY_SPATIAL_LINE_HPP
#define VELO_GEOMETRY_SPATIAL_LINE_HPP

#include <geometry/basic_line.hpp>
#include "point.hpp"

namespace geometry::spatial
{
	template<typename ValueType>
	class line : public basic_line<point<ValueType>>
	{
		public:
			using value_type = typename basic_line<point<ValueType>>::value_type;

			line() = default;

			line(value_type a, value_type b, value_type c, value_type d) :
				basic_line<point<value_type>>(std::move(a), std::move(b), std::move(c), std::move(d)){}

			inline const value_type& a() const{ return this->template get<0>(); }
			inline const value_type& b() const{ return this->template get<1>(); }
			inline const value_type& c() const{ return this->template get<2>(); }
			inline const value_type& d() const{ return this->template get<3>(); }

			inline void a(const value_type& v){ this->template set<0>(v); }
			inline void b(const value_type& v){ this->template set<1>(v); }
			inline void c(const value_type& v){ this->template set<2>(v); }
			inline void d(const value_type& v){ this->template set<3>(v); }

			inline void a(value_type&& v){ this->template set<0>(std::move(v)); }
			inline void b(value_type&& v){ this->template set<1>(std::move(v)); }
			inline void c(value_type&& v){ this->template set<2>(std::move(v)); }
			inline void d(value_type&& v){ this->template set<3>(std::move(v)); }
	};
}

#endif

/**
 * @author   Казаков Андрей 
 * @date     25.08.19.
 */

#ifndef GEOMETRY_FLAT_LINE_HH
#define GEOMETRY_FLAT_LINE_HH

#include "geometry/basic_line.h"
#include "point.hh"

namespace geometry
{
	namespace flat
	{
		template<typename ValueType>
		class line : public basic_line<point<ValueType>>
		{
			public:
				using value_type = typename basic_line<point<ValueType>>::value_type;
				using point_type = point<value_type>;

				line() = default;

				line(value_type a, value_type b, value_type c) :
					basic_line<point<value_type>>(std::move(a), std::move(b), std::move(c)){}

				line(const point<value_type>& p1, const point<value_type>& p2) :
					basic_line<point<value_type>>(std::move(p1.y() - p2.y()),
					                              std::move(p2.x() - p1.x()),
					                              std::move(-(p1.y() - p2.y()) * p1.x() - (p2.x() - p1.x()) * p1.y())){}

				inline const value_type& a() const{ return this->template get<0>(); }
				inline const value_type& b() const{ return this->template get<1>(); }
				inline const value_type& c() const{ return this->template get<2>(); }

				inline void a(const value_type& v){ this->template set<0>(v); }
				inline void b(const value_type& v){ this->template set<1>(v); }
				inline void c(const value_type& v){ this->template set<2>(v); }

				inline void a(value_type&& v){ this->template set<0>(std::move(v)); }
				inline void b(value_type&& v){ this->template set<1>(std::move(v)); }
				inline void c(value_type&& v){ this->template set<2>(std::move(v)); }
		};
	}

	namespace traits
	{
		template<typename T>
		struct tag<flat::line<T>>{ using type = line_tag; };

		template<typename T>
		struct access<flat::line<T>, 0>
		{
			static inline double get(const flat::line<T>& p){ return p.a(); }
			static inline double set(const flat::line<T>& p, const T value){ return p.a(value); }
		};

		template<typename T>
		struct access<flat::line<T>, 1>
		{
			static inline double get(const flat::line<T>& p){ return p.b(); }
			static inline double set(const flat::line<T>& p, const T value){ return p.b(value); }
		};

		template<typename T>
		struct access<flat::line<T>, 2>
		{
			static inline double get(const flat::line<T>& p){ return p.c(); }
			static inline double set(const flat::line<T>& p, const T value){ return p.c(value); }
		};
	}
}

#endif //GEOMETRY_FLAT_LINE_HH

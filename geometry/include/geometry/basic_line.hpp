#ifndef VELO_BASIC_LINE_HPP
#define VELO_BASIC_LINE_HPP

#include <cmath>
#include <utility>
#include "traits.hpp"

namespace geometry
{
	template<typename PointType>
	class basic_line
	{
		public:
			using value_type = typename PointType::value_type;

			enum{ size = traits::dimension<PointType>::value + 1 };

			basic_line() = default;

			template<typename ...Args>
			explicit basic_line(Args... args) : data{std::move(args)...}
			{
				static_assert(sizeof...(Args) <= size, "Too much arguments in constructor");
			}

			template<std::size_t Index>
			inline const value_type& get() const
			{
				static_assert(Index < size);
				return data[Index];
			}

			template<std::size_t Index>
			inline void set(const value_type& value)
			{
				static_assert(Index < size);
				data[Index] = value;
			}

//			basic_line(undelying_type a, undelying_type b, undelying_type c) : a(a), b(b), c(c){}
//			basic_line(value_type p1, value_type p2) :
//				a(p1.y - p2.y), b(p2.x - p1.x), c(-a * p1.x - b * p1.y){}

			bool is_vertical() const noexcept{ return (data[1] == 0); }
			bool is_horizontal() const noexcept{ return (data[0] == 0); }

			bool is_increasing() const noexcept{ return (-data[0] / data[1]) > 0; }
			bool is_decreasing() const noexcept{ return (-data[0] / data[1]) < 0; }

			void normalize() noexcept
			{
//				constexpr auto delta = (1.0 / 1000);
				auto z = std::sqrt(data[0] * data[0] + data[1] * data[1]);
//				if(std::abs(z) > delta)
				data[0] /= z, data[1] /= z, data[2] /= z;
			}

//			angle angle() const{ return angle::from_degrees(std::atan(-data[0] / data[1])); }

//			bool contains(const point <value_type>& point) const noexcept{ return distance(point) < (1 / power); }

//			value_type distance(const point <value_type>& p) const noexcept
//			{
//				return std::abs(a * p.x + b * p.y + c) / std::sqrt(std::pow(a, 2) + std::pow(b, 2));
//			}
//
//			point <value_type> get_point_on_line(value_type num, axes axis) const
//			{
//				point <value_type> res;
//				if(axis == axes::OX)
//				{
//					res.x = num;
//					res.y = ((-c - a * num) / b);
//				}
//				else
//				{
//					res.y = (num);
//					res.x = ((-c - b * num) / a);
//				}
//
//				return res;
//			}

		private:
			value_type data[size]{};
	};
}

#endif

/**
 * @author	Казаков Андрей
 * @date		18.02.2019.
 */

#ifndef GEOMETRY_BASIC_POINT_H
#define GEOMETRY_BASIC_POINT_H

#include <cstddef>
#include <algorithm>

namespace geometry
{
	template<typename ValueType, std::size_t DimensionCount>
	class basic_point
	{
			static_assert(DimensionCount > 1, "DimensionSize should be greater than zero");
		public:
			using value_type = ValueType;

			basic_point() = default;

			template<typename ...Args>
			explicit basic_point(Args... args) : data{std::move(args)...}
			{
				static_assert(sizeof...(Args) <= DimensionCount, "Too much arguments in constructor");
			}

			template<std::size_t Index>
			inline const value_type& get() const
			{
				static_assert(Index < DimensionCount);
				return data[Index];
			}

			template<std::size_t Index>
			inline void set(const value_type& value)
			{
				static_assert(Index < DimensionCount);
				data[Index] = value;
			}

			template<std::size_t Index>
			inline void set(value_type&& value)
			{
				static_assert(Index < DimensionCount);
				data[Index] = std::move(value);
			}

			template<typename T, std::size_t D>
			friend inline bool operator==(const basic_point<T, D>& p1, const basic_point<T, D>& p2);

		private:
			value_type data[DimensionCount]{};
	};

	template<typename ValueType, std::size_t DimensionCount>
	inline bool
	operator==(const basic_point<ValueType, DimensionCount>& p1, const basic_point<ValueType, DimensionCount>& p2)
	{
		return (std::equal(std::begin(p1.data), std::end(p1.data), std::begin(p2.data)));
	}

	template<typename ValueType, std::size_t DimensionCount>
	inline bool
	operator!=(const basic_point<ValueType, DimensionCount>& p1, const basic_point<ValueType, DimensionCount>& p2)
	{
		return !(p1 == p2);
	}
}

#endif //GEOMETRY_BASIC_POINT_H

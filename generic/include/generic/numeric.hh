/**
 * @author	Казаков Андрей
 * @date		07.07.17.
 */

#ifndef TESTS_BYTE_H
#define TESTS_BYTE_H

#include <ostream>
#include <type_traits>

#include "type_traits.hh"

namespace generic
{
	template<int SIZE, typename T, typename  = typename std::enable_if<is_power_of_two<SIZE>::value, bool>::type>
	class integer
	{
		public:
			enum { size = (SIZE / (sizeof(T) * 8)) };
			static const T min = std::numeric_limits<T>::min();
			static const T max = std::numeric_limits<T>::max();

			integer() noexcept : data() {}

			template<typename Tp, typename = typename std::enable_if<std::is_integral<T>::value>::type>
			integer(Tp value) noexcept : data()
			{
				if(max < value)
					value = max;

				if(min > value)
					value = min;

				data[size - 1] = static_cast<T>(value);
			}

			template<typename Tp, typename = typename std::enable_if<std::is_integral<T>::value>::type>
			integer(Tp* value) noexcept : data()
			{
				if(max < *value)
					*value = max;

				if(min > *value)
					*value = min;

				data[size - 1] = *value;
			}

			template<typename T1, typename = typename std::enable_if<std::is_integral<T>::value>::type>
			operator T1() const { return static_cast<T1>(data[0]); }

			template<typename T1, typename = typename std::enable_if<std::is_integral<T>::value>::type>
			bool operator==(T1 other) const { return (data[0] == other); }

			template<typename T1, typename = typename std::enable_if<std::is_integral<T>::value>::type>
			integer<SIZE, T>& operator=(T1 right)
			{
//				if(this == &right)
//					return *this;

				data[0] = right;
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& os, const integer& integer)
			{
				for(int i = 0; i < size; ++i)
					os << static_cast<int>(integer.data[i]);
				return os;
			}

		private:
			T data[size];
	};
}
#endif //TESTS_BYTE_H
/**
 * @author   Казаков Андрей 
 * @date     01.08.18.
 */

#ifndef VELO_TYPE_TRAITS_H
#define VELO_TYPE_TRAITS_H

#include <type_traits>

namespace generic
{
	template<int N>
	struct is_power_of_two { static const bool value = (N != 0 && !(N & (N - 1))); };

	template<typename T, T N, T M, typename = typename std::enable_if<std::is_integral<T>::value>::type>
	struct is_greater_than : public std::integral_constant<bool, (N > M)>::type {};
}
#endif //VELO_TYPE_TRAITS_H

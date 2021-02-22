#ifndef VELO_GENERIC_ALGORITHM_HPP
#define VELO_GENERIC_ALGORITHM_HPP

#include <iterator>
#include <tuple>

namespace generic
{
	template<typename Iterator, typename T = typename std::iterator_traits<Iterator>::value_type>
	std::tuple<T, T, T, T> two_min_two_max(Iterator begin, Iterator end)
	{
		T	max = std::numeric_limits<T>::min(),
			secondMax = std::numeric_limits<T>::min(),
			min = std::numeric_limits<T>::max(),
			secondMin = std::numeric_limits<T>::max();

		for(auto it = begin; it < end; ++it)
		{
			if(*it > max)
			{
				secondMax = max;
				max       = *it;
			}

			if(*it > secondMax && *it < max)
				secondMax = *it;

			if(*it < min)
			{
				secondMin = min;
				min       = *it;
			}

			if(*it < secondMin && *it > min)
				secondMin = *it;
		}

		return std::move(std::tuple(min, secondMin, max, secondMax));
	}

	constexpr bool is_prime(uint32_t num)
{
  if(num <= 1)
    return false;

  for(int i = num - 1; i > 1; --i)
    if(num % i == 0)
      return false;
  return true;
}

uint64_t sum_of_prime(uint32_t max)
{
  uint64_t res = 0;
  for(auto i = 0; i < max; ++i)
    if(is_prime(i))
      res += i;
  return res;
}

constexpr bool is_odd(size_t num) { return ((num & 1) != 0); }
}

#endif

/**
 * @author   Казаков Андрей 
 * @date     14.01.19.
 */

#include <array>
#include <algorithm>
#include <iostream>

#include "performance.h"
#include "arch.h"

void iterate(std::array<int, 10'000>& arr)
{
	for(int& i : arr)
		++i;
}

constexpr char name[] = "hello world";

int main()
{
	std::array<int, 10'000> arr;

	std::generate_n(arr.begin(), arr.size(), std::rand);

	auto dur = utility::performance::measure<>::averageDuration<>(iterate, arr);

	for(int i : arr)
		std::cout << i << '\n';
	std::cout << dur << '\n';
}
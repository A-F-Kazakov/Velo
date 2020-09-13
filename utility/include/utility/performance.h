/**
 * @author   Казаков Андрей
 * @date     25.02.2016.
 */

#ifndef UTILITY_PERFORMANCE_H
#define UTILITY_PERFORMANCE_H

#include <chrono>
#include <utility>

#define COUNT_START()			auto beginCount = std::chrono::high_resolution_clock::now()
#define COUNT_STOP()				auto endCount = std::chrono::high_resolution_clock::now()
#define COUNT_NANOSECONDS()	std::chrono::duration_cast<std::chrono::nanoseconds>(endCount - beginCount).count()
#define COUNT_MILLISECONDS()	std::chrono::duration_cast<std::chrono::milliseconds>(endCount - beginCount).count()

namespace utility::performance
{
	template<typename time = std::chrono::milliseconds>
	struct measure
	{
		template<typename F, typename ...Args>
		static auto duration(F&& func, Args&& ... args)
		{
			auto start = std::chrono::steady_clock::now();
			std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
			return std::chrono::duration_cast<time>(std::chrono::steady_clock::now() - start).count();
		}

		template<typename F, typename ...Args, int COUNT = 1'000'000>
		static auto averageDuration(F&& func, Args&& ... args)
		{
			uint64_t average = 0;
			for(int i = 0; i < COUNT; ++i)
				average += duration(func, args...);
			return average / COUNT;
		}
	};
}
#endif //UTILITY_PERFORMANCE_H
#ifndef UTILITY_DEBUG_H
#define UTILITY_DEBUG_H

#ifndef NDEBUG
	#include<iostream>
	#define DEBUG(X) std::clog << "DEBUG: " << (X) << std::endl
	#define WATCH(X) std::clog << (#X) << " = " << (X) << std::endl
#else //NDEBUG
	#define DEBUG(X)
	#define WATCH(X)
#endif //NDEBUG

namespace utility
{
	void debug()
	{
#ifndef NDEBUG
		std::clog << std::endl;
#endif
	}

	template <typename Head, typename... Tail>
	void debug(Head H, Tail... T)
	{
#ifndef NDEBUG
		std::clog << H << ' ';
		debug(T...);
#endif
	}
}

#endif //UTILITY_DEBUG_H

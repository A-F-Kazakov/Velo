#ifndef VELO_UTILITY_LOGGER_HPP
#define VELO_UTILITY_LOGGER_HPP

#include <iostream>
#include <mutex>

namespace utility
{
	class logger
	{
	  public:
		enum class level { off, debug, info, warn, error };

		static void initiate(level lvl) { logger::lvl_ = lvl; }

		template<typename Arg, typename... Args>
		static void debug(Arg&& arg, Args&&... args)
		{
			if(logger::lvl_ > level::debug || logger::lvl_ == level::off)
				return;

			std::lock_guard lock(mut);

			log(std::clog, level::debug) << std::forward<Arg>(arg);
			((std::clog << std::forward<Args>(args)), ...);
			std::clog << '\n';
		}

		template<typename Arg, typename... Args>
		static void info(Arg&& arg, Args&&... args)
		{
			if(logger::lvl_ > level::info || logger::lvl_ == level::off)
				return;

			std::lock_guard lock(mut);

			log(std::clog, level::info) << std::forward<Arg>(arg);
			((std::clog << std::forward<Args>(args)), ...);
			std::clog << '\n';
		}

		template<typename Arg, typename... Args>
		static void warn(Arg&& arg, Args&&... args)
		{
			if(logger::lvl_ > level::warn || logger::lvl_ == level::off)
				return;

			std::lock_guard lock(mut);

			log(std::clog, level::warn) << std::forward<Arg>(arg);
			((std::clog << std::forward<Args>(args)), ...);
			std::clog << '\n';
		}

		template<typename Arg, typename... Args>
		static void error(Arg&& arg, Args&&... args)
		{
			if(logger::lvl_ == level::off)
				return;

			std::lock_guard lock(mut);

			log(std::cerr, level::error) << std::forward<Arg>(arg);
			((std::cerr << std::forward<Args>(args)), ...);
			std::cerr << '\n';
		}

	  private:
		static std::ostream& log(std::ostream& os, level lvl);

		static level lvl_;
		static std::mutex mut;
	};
} // namespace utility

#endif

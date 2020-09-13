#ifndef UTILITY_LOGGER_H
#define UTILITY_LOGGER_H

#include <iostream>
#include <mutex>

namespace utility
{
	class logger
	{
		public:
			enum class level
			{
					off,
					debug,
					info,
					warn,
					error
			};

			static void initiate(level lvl) { logger::lvl_ = lvl; }

			template<typename Arg, typename ...Args>
			static void debug(Arg &&arg, Args &&... args)
			{
				if(logger::lvl_ > level::DEBUG || logger::lvl_ == level::OFF)
					return;

				std::lock_guard lock(mut);

				log(std::clog, level::DEBUG) << std::forward<Arg>(arg);
				((std::clog << std::forward<Args>(args)), ...);
				std::clog << '\n';
			}

			template<typename Arg, typename ...Args>
			static void info(Arg &&arg, Args &&... args)
			{
				if(logger::lvl_ > level::INFO || logger::lvl_ == level::OFF)
					return;

				std::lock_guard lock(mut);

				log(std::clog, level::INFO) << std::forward<Arg>(arg);
				((std::clog << std::forward<Args>(args)), ...);
				std::clog << '\n';
			}

			template<typename Arg, typename ...Args>
			static void warn(Arg &&arg, Args &&... args)
			{
				if(logger::lvl_ > level::WARN || logger::lvl_ == level::OFF)
					return;

				std::lock_guard lock(mut);

				log(std::clog, level::WARN) << std::forward<Arg>(arg);
				((std::clog << std::forward<Args>(args)), ...);
				std::clog << '\n';
			}

			template<typename Arg, typename ...Args>
			static void error(Arg &&arg, Args &&... args)
			{
				if(logger::lvl_ == level::OFF)
					return;

				std::lock_guard lock(mut);

				log(std::cerr, level::ERROR) << std::forward<Arg>(arg);
				((std::cerr << std::forward<Args>(args)), ...);
				std::cerr << '\n';
			}

		private:
			static std::ostream &log(std::ostream &os, level lvl);

			static level lvl_;
			static std::mutex mut;
	};
}

#endif //UTILITY_LOGGER_H

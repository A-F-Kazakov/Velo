#ifndef VELO_UTILITY_FILE_WATCHER_HPP
#define VELO_UTILITY_FILE_WATCHER_HPP

#include <chrono>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <functional>

namespace utility
{
	enum class file_status { created, modified, erased };

	class file_watcher
	{
		public:
			file_watcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay);

			void start(const std::function<void(std::string, file_status)> &action);

		private:
			std::string path_to_watch;
			std::chrono::duration<int, std::milli> delay;

			std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
			bool running;

			bool contains(const std::string &key);
	};
}

#endif

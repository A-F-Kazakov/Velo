/**
 * @author   Казаков Андрей 
 * @date     20.02.19.
 */

#ifndef UTILITY_FILE_WATCHER_H
#define UTILITY_FILE_WATCHER_H

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

#endif //UTILITY_FILE_WATCHER_H

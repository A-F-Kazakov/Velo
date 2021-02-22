#include <thread>

#include <utility/file_watcher.hpp>

utility::file_watcher::file_watcher(std::string path_to_watch, std::chrono::duration<int, std::milli> delay) :
path_to_watch{path_to_watch}, delay{delay}, running(true)
{
	for(auto &file : std::filesystem::recursive_directory_iterator(path_to_watch))
		paths_[file.path()] = std::filesystem::last_write_time(file);
}

void utility::file_watcher::start(const std::function<void(std::string, utility::file_status)> &action)
{
	while(running)
	{
		std::this_thread::sleep_for(delay);

		for(auto &el : paths_)
			if(!std::filesystem::exists(el.first))
			{
				action(el.first, file_status::erased);
				paths_.erase(el.first);
			}

		for(auto &file : std::filesystem::recursive_directory_iterator(path_to_watch))
		{
			auto current_file_last_write_time = std::filesystem::last_write_time(file);

			if(!contains(file.path()))
			{
				paths_[file.path()] = current_file_last_write_time;
				action(file.path(), file_status::created);
			}
			else
				if(paths_[file.path()] != current_file_last_write_time)
				{
					paths_[file.path()] = current_file_last_write_time;
					action(file.path(), file_status::modified);
				}
		}
	}
}

bool utility::file_watcher::contains(const std::string &key)
{
	auto el = paths_.find(key);
	return el != paths_.end();
}

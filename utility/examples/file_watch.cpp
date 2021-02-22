#include <iostream>

#include <utility/file_watcher.hpp>

using namespace utility;

int main()
{
	file_watcher fw{"./", std::chrono::milliseconds(5000)};

	fw.start([](std::string path_to_watch, file_status status)
   {
      if(!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != file_status::erased)
         return;

      switch(status)
      {
         case file_status::created:
         	std::cout << "File created: " << path_to_watch << '\n';
	         break;
         case file_status::modified:
         	std::cout << "File modified: " << path_to_watch << '\n';
	         break;
         case file_status::erased:
         	std::cout << "File erased: " << path_to_watch << '\n';
	         break;
         default:
         	std::cout << "Error! Unknown file status.\n";
      }
   });
}

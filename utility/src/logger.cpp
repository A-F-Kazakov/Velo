#include <utility/logger.hpp>

utility::logger::level utility::logger::lvl_ = utility::logger::level::debug;

std::mutex utility::logger::mut;

std::ostream& utility::logger::log(std::ostream& os, utility::logger::level lvl)
{
	time_t now = time(nullptr);
	tm tstruct{};
	char buf[20];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y.%X", &tstruct);

	os << buf << " [";

	switch(lvl)
	{
		case level::off:
			break;
		case level::debug:
			os << "DEBUG";
			break;
		case level::info:
			os << "INFO";
			break;
		case level::warn:
			os << "WARN";
			break;
		case level::error:
			os << "ERROR";
			break;
	}

	os << "]: ";

	return os;
}

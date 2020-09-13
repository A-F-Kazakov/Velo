#include "utility/logger.h"

utility::logger::level utility::logger::lvl_ = utility::logger::level::DEBUG;

std::mutex utility::logger::mut;

std::ostream &utility::logger::log(std::ostream &os, utility::logger::level lvl)
{
	time_t   now = time(nullptr);
	tm       tstruct{};
	char     buf[20];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y.%X", &tstruct);

	os << buf << " [";

	switch(lvl)
	{
		case level::OFF:break;
		case level::DEBUG:
			os << "DEBUG";
			break;
		case level::INFO:
			os << "INFO";
			break;
		case level::WARN:
			os << "WARN";
			break;
		case level::ERROR:
			os << "ERROR";
			break;
	}

	os << "]: ";

	return os;
}

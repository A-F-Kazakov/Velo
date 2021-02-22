#include <utility/logger.hpp>

using utility::logger;

int main()
{
	std::cout << "Initiate logger to DEBUG mode\n";
	logger::initiate(logger::level::DEBUG);

	logger::debug("it's", "debug message");
	logger::info("it's", "info message");
	logger::warn("this is ", "warn", "message");
	logger::error("this is ", "error", "message");

	logger::initiate(logger::level::INFO);
	std::clog << "\n";

	logger::debug("it's", "debug message");
	logger::info("it's", "info message");
	logger::warn("this is ", "warn", "message");
	logger::error("this is ", "error", "message");

	logger::initiate(logger::level::WARN);
	std::clog << "\n";

	logger::debug("it's", "debug message");
	logger::info("it's", "info message");
	logger::warn("this is ", "warn", "message");
	logger::error("this is ", "error", "message");

	logger::initiate(logger::level::ERROR);
	std::clog << "\n";

	logger::debug("it's", "debug message");
	logger::info("it's", "info message");
	logger::warn("this is ", "warn", "message");
	logger::error("this is ", "error", "message");

	logger::initiate(logger::level::OFF);
	std::clog << "\n";

	logger::debug("it's", "debug message");
	logger::info("it's", "info message");
	logger::warn("this is ", "warn", "message");
	logger::error("this is ", "error", "message");

	std::cout << "End of example\n";
}

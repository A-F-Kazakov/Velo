/**
 * @author   Казаков Андрей 
 * @date     07.08.18.
 */

#include <iostream>
#include <string_view>
#include <algorithm>

#include "argument_parser.h"
#include "settings.h"

using utility::argument_parser;

int main(int argc, char** argv)
{
	argument_parser args;

	args.required("host", 'h', "\tlistening host somehow long string describes\n\t\t\t\t\t the behaviour of this flag", true)
		  .required("port", 'p', "\tlistening port", true)
		  .optional("fork", 'f', "\tfork processes", false)
		  .optional("create", 'c', "create files", false);

	args.parse(argc, argv);

	std::cout << args.get<std::string_view>("host") << "\n";
	std::cout << args.get<uint16_t>("port") << "\n";
	std::cout << std::boolalpha << !args.get<bool>("fork") << "\n";
	std::cout << std::boolalpha << !args.get<bool>("create") << "\n";
}

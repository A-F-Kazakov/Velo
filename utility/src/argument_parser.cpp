#include <iostream>

#include "utility/argument_parser.h"

utility::argument::argument(char short_name,
								 std::string long_name,
								 std::string description,
								 bool required,
								 bool need_value,
								 std::string_view value) :
		short_name(short_name),
		long_name(std::move(long_name)),
		required(required),
		description(std::move(description)),
		need_value(need_value),
		value(value){}

utility::argument_parser&
utility::argument_parser::required(const std::string& lName, char sName, const std::string& description, bool needValue)
{
	flags.emplace_back(sName, lName, description, true, needValue, "");
	return *this;
}

utility::argument_parser&
utility::argument_parser::optional(const std::string& longName, char shortName, const std::string& description)
{
	flags.emplace_back(shortName, longName, description, false, false, "");
	return *this;
}

utility::argument_parser&
utility::argument_parser::optional(const std::string& longName, char shortName, const std::string& description, bool need)
{
	flags.emplace_back(shortName, longName, description, false, need, "");
	return *this;
}

utility::argument_parser&
utility::argument_parser::optional(const std::string& lName, char sName, const std::string& desc, std::string& defaultVal)
{
	flags.emplace_back(sName, lName, desc, false, false, defaultVal);
	return *this;
}

utility::argument_parser&
utility::argument_parser::optional(const std::string& lName, char sName, const std::string& desc, bool need, std::string& defVal)
{
	flags.emplace_back(sName, lName, desc, false, need, defVal);
	return *this;
}

void utility::argument_parser::parse(int argc, char** argv)
{
	std::string_view flag, value;

	for(int i = 1; i < argc; ++i)
	{
		if(argv[i][0] == '-' && argv[i][1] != '-')
		{
			flag = std::string_view(&argv[i][1], 1);

			if(is_need_vale(flag))
			{
				if(argv[i][2] == '\0' && argc != i + 1 && argv[i + 1][0] != '-')
					value = argv[++i];
				else
					value = &argv[i][2];
			}
		}
		else
			if(argv[i][0] == argv[i][1] && argv[i][0] == '-')
			{
				std::string_view tmp(&argv[i][2]);

				auto pos = tmp.find('=');

				if(pos == std::string::npos)
					flag = tmp.substr(0, pos);
				else
				{
					flag  = tmp.substr(0, pos);
					value = tmp.substr(pos + 1);
				}
			}

		if(flag == "?" || flag == "help")
		{
			print_help(argv[0]);
			exit(1);
		}

		for(auto&& item : flags)
			if(flag == item.long_name || flag == std::string(1, item.short_name))
			{
				if(item.need_value)
					item.value = value;
				break;
			}
	}
}

void utility::argument_parser::print_help(std::string_view path)
{
	path = path.substr(path.find_last_of('/') + 1);

	std::cout << "Usage:\n\t" << path;

	std::stringstream nrequired;

	nrequired << "\t-?, --help\tprint this message";

	for(auto&& flag : flags)
	{
		if(flag.required)
			std::cout << " --" << flag.long_name << "=<value>";

		nrequired << "\n\t";

		if(flag.short_name == '\0')
			nrequired << "    ";
		else
			nrequired << "-" << flag.short_name << ", ";

		nrequired << "--" << flag.long_name << "\t" << flag.description;

		if(!flag.value.empty())
			nrequired << " [=" << flag.value << "]";
	}

	std::cout << " [options]\noptions:\n" << nrequired.rdbuf() << "\n";
}

bool utility::argument_parser::is_need_vale(std::string_view flag)
{
	for(auto&& item : flags)
		if(flag == item.long_name || flag == std::string(1, item.short_name))
			return item.need_value;

	return false;
}

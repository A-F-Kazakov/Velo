/**
 * @author   Казаков Андрей 
 * @date     07.08.18.
 * https://github.com/muellan/clipp
 */

#ifndef UTILITY_ARGUMENTPARSER_H
#define UTILITY_ARGUMENTPARSER_H

#include <string>
#include <string_view>
#include <vector>
#include <sstream>

namespace utility
{
	struct argument
	{
		bool             required;
		bool             need_value;
		char             short_name;
		std::string      long_name;
		std::string      description;
		std::string_view value;

		argument(char short_name,
					std::string long_name,
					std::string description,
					bool required,
					bool need_value,
					std::string_view value);
	};

	class argument_parser
	{
		public:
			argument_parser& required(const std::string&, char, const std::string&, bool = false);

			argument_parser& optional(const std::string&, char, const std::string&);

			argument_parser& optional(const std::string&, char, const std::string&, bool);

			argument_parser& optional(const std::string&, char, const std::string&, std::string&);

			argument_parser& optional(const std::string&, char, const std::string&, bool, std::string&);

			template<typename T>
			T get(std::string&& longName)
			{
				std::stringstream ss;
				for(auto&& item : flags)
					if(longName == item.long_name)
					{
						ss << item.value;
						T ret;
						ss >> ret;

						return std::move(ret);
					}

				return T();
			}

			void parse(int argc, char** argv);

		private:
			void print_help(std::string_view path);

			bool is_need_vale(std::string_view flag);

			std::vector<argument> flags;
	};

	template<>
	inline std::string_view argument_parser::get<std::string_view>(std::string&& longName)
	{
		for(auto&& item : flags)
			if(longName == item.long_name)
				return item.value;
		return nullptr;
	}

	template<>
	inline bool argument_parser::get<bool>(std::string&& longName)
	{
		for(auto&& item : flags)
			if(longName == item.long_name)
				return !item.value.empty();
		return false;
	}
}
#endif //UTILITY_ARGUMENTPARSER_H

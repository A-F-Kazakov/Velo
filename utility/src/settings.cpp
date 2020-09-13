#include <utility/settings.h>

#include <fstream>

utility::settings::settings() : settings(std::string(std::getenv("HOME")).append("/.settings")){}

utility::settings::settings(const std::string& filePath) : path(filePath){}

utility::settings::settings(std::string&& filePath) noexcept : path(std::move(filePath)){}

utility::settings::settings(const std::filesystem::path& filepath) : path(filepath.string()){}

utility::settings::settings(std::filesystem::path&& filepath) noexcept: path(std::move(filepath.string())){}

utility::settings::settings(utility::settings&& other) noexcept : path(std::move(other.path)), data(std::move(other.data)){}

void utility::settings::clear(){ data.clear(); }

template<>
std::error_code utility::settings::load<utility::settings::type::INI>()
{
	std::ifstream is(path);

	std::string line;
	if(is)
	{
		while(std::getline(is, line))
		{
			auto pos = line.find('=');

			if(pos != std::string::npos)
				data[line.substr(0, pos)] = line.substr(pos + 1);
		}
		is.close();
	}

	return {};
}

template<>
std::error_code utility::settings::save<utility::settings::type::INI>()
{
	std::ofstream os(path);

	if(os)
	{
		for(const auto&[key, val] : data)
			os << key << '=' << val << '\n';

		os.close();
		return {};
	}
	return std::make_error_code(std::errc::no_such_file_or_directory);
}

template<>
void utility::settings::set<std::string_view>(std::string_view key, std::string_view value){ data.emplace(key, value); }

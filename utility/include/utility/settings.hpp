#ifndef VWLO_UTILITY_SETTINGS_HPP
#define VWLO_UTILITY_SETTINGS_HPP

#include <unordered_map>
#include <string>
#include <string_view>
#include <sstream>
#include <filesystem>

namespace utility
{
	class settings
	{
		public:
			enum type { INI };

			settings();
			explicit settings(const std::string&);
			explicit settings(std::string&&) noexcept;

			explicit settings(const std::filesystem::path&);
			explicit settings(std::filesystem::path&&) noexcept;

			settings(const settings&) = default;
			settings(settings&&) noexcept;

			void clear();

			void set_path(std::string_view v) { path = v; }
			void set_path(std::string &&v) { path = std::move(v); }

			template <type T>
			std::error_code load();
			template <type T>
			std::error_code save();

			std::string_view get_path() const { return path; }

			template <typename T, typename  = typename std::enable_if<std::is_integral<T>::value>>
			void set(std::string_view key, T value)
			{
				std::stringstream ss;

				ss << value;

				data.emplace(key, ss.str());
			}

			template <typename T, typename = std::enable_if<std::is_integral<T>::value>>
			T get(const std::string& key) const
			{
				std::stringstream ss;

				ss << data.at(key);

				T value;
				ss >> value;
				return std::move(value);
			}

			std::string_view get(const std::string& key) const{ return data.at(key); }

			template <typename T, typename = std::enable_if<std::is_integral<T>::value>>
			T get_or_assign(const std::string &key, T defaultValue) const
			{
				std::stringstream ss;

				try
				{
					ss << data.at(key);

					T value;
					ss >> value;
					return std::move(value);
				}
				catch(std::out_of_range& e)
				{
					return std::move(defaultValue);
				}
			}

		private:
			std::string path;
			std::unordered_map<std::string, std::string> data;
	};
}

#endif

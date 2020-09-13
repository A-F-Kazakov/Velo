/**
 * @author   Казаков Андрей 
 * @date     18.09.19.
 */

#include <generic/serializer.hh>

using generic::serialize;
using generic::json;
using generic::xml;

struct person
{
	std::string name;
	std::string surname;
	uint8_t age;
	uint8_t grades[3]{};
};

template<>
struct generic::type_traits::field_count<person> { enum { value = 4 }; };

template<>
struct generic::type_traits::access<person, 0> : std::false_type
{
	using type = std::string;

	static inline std::string get_name() { return "name"; }
	static inline std::string get(person v) { return v.name; }
};

template<>
struct generic::type_traits::access<person, 1> : std::false_type
{
	using type = std::string;

	static inline std::string get_name() { return "surname"; }
	static inline std::string get(person v) { return v.surname; };
};

template<>
struct generic::type_traits::access<person, 2> : std::false_type
{
	using type = int;

	static inline std::string get_name() { return "age"; }
	static inline int get(person v) { return v.age; };
};

template<>
struct generic::type_traits::access<person, 3> : std::true_type
{
	static inline std::string get_name() { return "grades"; }
	static inline auto &get(person v) { return v.grades; };
};

int main()
{
	person p1{"Jane", "Doe", 12};

	std::string json_string = serialize<json>(p1);
	std::string xml_string  = serialize<xml>(p1);

	std::cout << json_string << "\n" << xml_string << std::endl;
}

#include <iostream>

#include <generic/typelist.hpp>

using namespace generic;

int main(int argc, char** argv)
{
	std::cout << "Velo generic structures:\n\n";

	typedef TypeList<char, short, int, long> IntegerTypes;

	IntegerTypes types;

	std::cout << "Types list: " << types << std::endl;

	std::cout << "Is empty EmptyTypeList: " << std::boolalpha << IsEmpty<EmptyTypeList>::value << std::endl;
	std::cout << "Is empty IntegerList: " << std::boolalpha << IsEmpty<IntegerTypes>::value << std::endl;

	std::cout << "Length of the IntegerTypes: " << Length<IntegerTypes>::value << std::endl;

	int status = 0;
	std::cout << "Type at 3 of the IntegerTypes: " << typeid(TypeAt<IntegerTypes, 3>::type).name() << std::endl;

	typedef TypeList<float, double> FloatingTypes;

	typedef Append<IntegerTypes, FloatingTypes>::type NumbersList;

	NumbersList list;

	std::cout << "\nAppended types: " << list << std::endl;

	std::cout << "Is float in list: " << IsIn<float, NumbersList>::value << std::endl;
	std::cout << "Is uint8_t in list: " << IsIn<uint8_t, NumbersList>::value << std::endl;

	typedef AppendUnique<uint8_t, NumbersList>::type Appended;
	typedef AppendUnique<float , NumbersList>::type NotAppended;

	Appended a;
	NotAppended na;

	std::cout << a << " - " << na << std::endl;

	typedef RemoveAll<float, NotAppended>::type WithoutFloat;

	WithoutFloat wf;

	std::cout << wf << std::endl;

	typedef TypeList<int, long, int, char, float, float, int> duplicates;

	duplicates dp;

	std::cout << "Typelist with duplicates: " << dp << std::endl;

	typedef RemoveDuplicates<duplicates>::type WitoutDuplictes;

	WitoutDuplictes wdp;

	std::cout << "Type list without duplicates: " << wdp << std::endl;

	std::cout << "Tke last element: " << typeid(TakeLast<WithoutFloat>::type).name() << std::endl;

	typedef TakeFirstN<NumbersList, 2>::type firstTwoNumbers;

	firstTwoNumbers fton;

	std::cout << "First two types from the numbers: " << fton << std::endl;

	typedef SkipFirst<NumbersList, 2>::type withoutFirsttwo;

	withoutFirsttwo wft;

	std::cout << "Without first two numbers: " << wft << std::endl;
}

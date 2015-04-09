#include <iostream>
#include <string>

#define USE_ENUM_MACRO
#ifdef USE_ENUM_MACRO
	#include "enum_conversions_macro.h"
	ENUM_CLASS(Day, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday);
#else
	#include "enum_conversions.h"
	enum class Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

	template <> const typename EnumConversions<Day>::Vector EnumConversions<Day>::enumToStringVector = { 
		{Monday, "Monday"}, {Tuesday, "Tuesday"}, {Wednesday, "Wednesday"}, {Thursday, "Thursday"}, {Friday, "Friday"}, {Saturday, "Saturday"}, {Sunday, "Sunday"}
	};

	template <> struct enum_serializable<Day> : std::true_type {};
#endif

int main ()
{
	std::cout << "size:" << EnumManager<Day>::size() << std::endl;

	for (int DAY = 0; DAY < EnumManager<Day>::size(); DAY++)
		std::cout << static_cast<Day> (DAY) << std::endl;

	Day e = Day::Friday;
	std::string s = EnumConversions<Day>::toString(e);
	std::cout << "to string: '" << s << "'" << std::endl;
	e = EnumConversions<Day>::toEnum(s);
	std::cout << "from string: " << e << " = " << (int)e << std::endl;

	std::cout << "Name a day: ";
	while (true)
	{
		std::cin >> e;
		std::cout << "day = " << e << std::endl;
	}
}


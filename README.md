# enum_strings
C++ enum convertible to and from string.

The source code was gathered from several sources and slightly modified. The original sources are referenced in the code.

## Example
``` cpp
#include "enum_conversions_macro.h"
ENUM_CLASS(Day, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday);

int main ()
{
	// get enum size
	std::cout << "enum size:" << EnumManager<Day>::size() << std::endl;
	
	Day e = Day::Friday;
	
	// convert enum to string
	std::string s = EnumConversions<Day>::toString(e);
	std::cout << "to string: '" << s << "'" << std::endl;
	
	// convert string to enum
	e = EnumConversions<Day>::toEnum(s);
	std::cout << "from string: " << e << " = " << (int)e << std::endl;
	
	return 0;
}
```

The code is usable also without macros (for those who hate them ;o), just check the main.cpp

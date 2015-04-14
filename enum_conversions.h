#ifndef ENUM_CONVERSIONS_H
#define ENUM_CONVERSIONS_H

#include <string>
#include <sstream>
#include <vector>
#include <map>

// http://www.cplusplus.com/forum/general/124592/
template <typename Enum>
class EnumConversions;

template <typename Enum>
struct EnumManager {
	typedef std::vector<std::pair<Enum, std::string>> EnumToStringVector;
	static const int ENUM_NOT_FOUND = -1;
    static std::string toString (const Enum en);
    static Enum toEnum (const std::string& str);
	static int size();
    static const std::map<Enum, std::string> enumToStringMap;
    static const std::map<std::string, Enum> stringToEnumMap;
private:
    static std::map<Enum, std::string> initializeEnumToStringMap();
    static std::map<std::string, Enum> initializeStringToEnumMap();
protected:
	static std::string trim(std::string const& str)
	{
		if(str.empty())
			return str;

		std::size_t first = str.find_first_not_of(' ');
		std::size_t last  = str.find_last_not_of(' ');
		return str.substr(first, last-first+1);
	}
	static EnumToStringVector splitStringToVector(const std::string& str) {
		const char delim = ',';
		EnumToStringVector tokens;
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delim)) {
			tokens.push_back(std::make_pair(static_cast<Enum>(tokens.size()), trim(item)));
		}
		return tokens;
	}
};

template <typename Enum>
const std::map<Enum, std::string> EnumManager<Enum>::enumToStringMap =  EnumManager<Enum>::initializeEnumToStringMap();

template<typename Enum>
std::map<Enum, std::string> EnumManager<Enum>::initializeEnumToStringMap() {
    std::map<Enum, std::string> m;
    //for (const auto& x: EnumConversions<Enum>::enumToStringVector)
	for (const auto& x: splitStringToVector(EnumConversions<Enum>::enumToStringStr))
		m[x.first] = x.second;
    return m;
}

template <typename Enum>
const std::map<std::string, Enum> EnumManager<Enum>::stringToEnumMap =  EnumManager<Enum>::initializeStringToEnumMap();

template<typename Enum>
std::map<std::string, Enum> EnumManager<Enum>::initializeStringToEnumMap() {
    std::map<std::string, Enum> m;
    //for (const auto& x: EnumConversions<Enum>::enumToStringVector)
	for (const auto& x: splitStringToVector(EnumConversions<Enum>::enumToStringStr))
		m[x.second] = x.first;
    return m;
}

template <typename Enum>
std::string EnumManager<Enum>::toString (const Enum en) {
    auto it = EnumManager<Enum>::enumToStringMap.find (en);  // std::map::find is the fastest lookup method
    if (it != EnumManager<Enum>::enumToStringMap.end())
        return it->second;
    return "[[[Enum to string not found. Programmer made an error]]]";
}

template<typename Enum>
Enum EnumManager<Enum>::toEnum (const std::string& str) {
    auto it = EnumManager<Enum>::stringToEnumMap.find (str);
    if (it != EnumManager<Enum>::stringToEnumMap.end())
        return it->second;
    return static_cast<Enum> (ENUM_NOT_FOUND);
}

template<typename Enum>
int EnumManager<Enum>::size() {
	return EnumManager<Enum>::enumToStringMap.size();
}

template <typename Enum>
struct EnumConversions //: public EnumManager<Enum>
{
	//static constexpr typename EnumManager<Enum>::EnumToStringVector enumToStringVector = {};
	static constexpr char enumToStringStr[] = "";
};


// http://codereview.stackexchange.com/a/43862
template <typename Enum>
struct enum_serializable : std::false_type
{};

template <typename Enum>
typename std::enable_if<enum_serializable<Enum>::value, std::ostream&>::type operator<<(std::ostream& os, Enum e)
{
    return os << EnumManager<Enum>::toString(e);
}

template <typename Enum>
typename std::enable_if<enum_serializable<Enum>::value, std::istream&>::type operator>>(std::istream& is, Enum& e)
{
    std::string buf;
    is >> buf;
	e = EnumManager<Enum>::toEnum(buf);
    return is;
}

#endif

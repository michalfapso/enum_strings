#ifndef ENUM_CONVERSIONS_MACRO_H
#define ENUM_CONVERSIONS_MACRO_H

#include "enum_conversions.h"

// http://stackoverflow.com/a/25516380
#define ENUM_IMPL_(type, name, ...)\
    type name\
    {\
        __VA_ARGS__\
    };\
	template <> struct EnumConversions<name> { \
		static constexpr char enumToStringStr[] = #__VA_ARGS__; \
	}; \
	constexpr char EnumConversions<name>::enumToStringStr[]; \
	template <> struct enum_serializable<name> : std::true_type {};\

//	template <> constexpr char EnumConversions<name>::enumToStringStr[]; \
//		public: static constexpr EnumToStringVector enumToStringVector = splitStringToVector(#__VA_ARGS__); \
//	template <> const typename EnumConversions<name>::Vector EnumConversions<name>::enumToStringVector = EnumConversions<name>::splitStringToVector(#__VA_ARGS__);\
//	static const int name##Size = (sizeof((int[]){__VA_ARGS__})/sizeof(int));\

#define ENUM(name, ...) ENUM_IMPL_(enum, name, __VA_ARGS__)

#define ENUM_CLASS(name, ...) ENUM_IMPL_(enum class, name, __VA_ARGS__)

#define ENUM_DEFINITION(name) \
	constexpr char EnumConversions<name>::enumToStringStr[];

#endif


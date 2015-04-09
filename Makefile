CXXFLAGS += -std=c++11

main: main.cpp enum_conversions.h enum_conversions_macro.h
	$(CXX) $(CXXFLAGS) -o $@ $<


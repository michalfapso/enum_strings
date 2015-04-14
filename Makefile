CXXFLAGS += -std=c++11

main: main.o a.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

a.o: a.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


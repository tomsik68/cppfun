CXXFLAGS= -std=c++1z -Wall -Wextra -pedantic
CXX=g++

all: test

test: const_list.hpp test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test

clean:
	rm test

CXXFLAGS=-std=c++1z -Wall -Wextra -Weffc++ -O2

all: main main.s

main: main.o
	$(CXX) $(CXXFLAGS) -o main $<

main.s: main.cpp
	$(CXX) $(CXXFLAGS) -S main.cpp
main.o: main.cpp

clean:
	rm -rf main main.o main.s

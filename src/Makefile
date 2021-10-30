CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -O3

all: PeykNowruzi

PeykNowruzi: PeykNowruzi.o Util.o CharMatrix.o
	$(CXX) PeykNowruzi.o Util.o CharMatrix.o -o runPeykNowruzi

PeykNowruzi.o: PeykNowruzi.cpp
	$(CXX) -c $(CXXFLAGS) PeykNowruzi.cpp

Util.o: Util.cpp Util.h
	$(CXX) -c $(CXXFLAGS) Util.cpp

CharMatrix.o: CharMatrix.cpp CharMatrix.h
	$(CXX) -c $(CXXFLAGS) CharMatrix.cpp

clean:
	rm -f *.o runPeykNowruzi
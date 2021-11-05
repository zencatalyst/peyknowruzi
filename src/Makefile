CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -O3 -flto

all: PeykNowruzi

PeykNowruzi: PeykNowruzi.o Util.o CharMatrix.o CharMatrix_Exceptions.o
	$(CXX) PeykNowruzi.o Util.o CharMatrix.o CharMatrix_Exceptions.o -o runPeykNowruzi

PeykNowruzi.o: PeykNowruzi.cpp CharMatrix.h
	$(CXX) -c $(CXXFLAGS) PeykNowruzi.cpp

Util.o: Util.cpp Util.h
	$(CXX) -c $(CXXFLAGS) Util.cpp

CharMatrix.o: CharMatrix.cpp CharMatrix.h Util.h CharMatrix_Exceptions.h
	$(CXX) -c $(CXXFLAGS) CharMatrix.cpp

CharMatrix_Exceptions.o: CharMatrix_Exceptions.cpp CharMatrix_Exceptions.h CharMatrix.h
	$(CXX) -c $(CXXFLAGS) CharMatrix_Exceptions.cpp

clean:
	rm *.o runPeykNowruzi
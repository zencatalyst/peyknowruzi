CC=g++
CFLAGS=-std=c++17 -O3 -Wextra -Wall -Wpedantic -flto

all: PeykNowruzi

PeykNowruzi: PeykNowruzi.o Util.o CharMatrix.o
	$(CC) PeykNowruzi.o Util.o CharMatrix.o -o runPeykNowruzi

PeykNowruzi.o: PeykNowruzi.cpp
	$(CC) $(CFLAGS) PeykNowruzi.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) Util.cpp

CharMatrix.o: CharMatrix.cpp
	$(CC) $(CFLAGS) CharMatrix.cpp

clean:
	rm -rf *o PeykNowruzi
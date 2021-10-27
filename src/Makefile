CC=g++
CFLAGS=-std=c++20 -Wall -Wextra -Wpedantic -Wshadow -O3 -flto

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
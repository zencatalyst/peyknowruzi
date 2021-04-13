CC=g++
CFLAGS=-std=c++17 -O3 -Wextra

all: PeykNowruzi

PeykNowruzi: PeykNowruzi_Easy.o Util.o CharMatrix.o
	$(CC) PeykNowruzi_Easy.o Util.o CharMatrix.o -o PeykNowruzi

PeykNowruzi_Easy.o: PeykNowruzi_Easy.cpp
	$(CC) $(CFLAGS) PeykNowruzi_Easy.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) Util.cpp

CharMatrix.o: CharMatrix.cpp
	$(CC) $(CFLAGS) CharMatrix.cpp

clean:
	rm -rf *o PeykNowruzi
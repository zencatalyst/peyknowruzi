CXX = g++
CXXFLAGS = -c -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -O3 -flto
DEPS = CharMatrix.h Util.h
OBJ = PeykNowruzi.o Util.o CharMatrix.o

PCH_SRC = pch.h
PCH_OUT = pch.h.gch

all: PeykNowruzi

PeykNowruzi: $(OBJ)
	$(CXX) $^ -o runPeykNowruzi

PeykNowruzi.o: PeykNowruzi.cpp CharMatrix.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

Util.o: Util.cpp Util.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

CharMatrix.o: CharMatrix.cpp CharMatrix.h Util.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

$(PCH_OUT): $(PCH_SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o runPeykNowruzi

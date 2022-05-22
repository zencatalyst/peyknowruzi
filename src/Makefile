CXX = g++
CXXFLAGS = -c -std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -O3 -march=native -flto
LDFLAGS = -O3 -march=native -flto -s -static
DEPS = Scripts.h CharMatrix.h Util.h
OBJS = Launch.o Scripts.o Util.o CharMatrix.o
TARGET = PeykNowruzi

PCH_SRC = pch.h
PCH_OUT = pch.h.gch

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o runPeykNowruzi

$(PCH_OUT): $(PCH_SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

Launch.o: Launch.cpp Scripts.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

Scripts.o: Scripts.cpp Scripts.h CharMatrix.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

Util.o: Util.cpp Util.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

CharMatrix.o: CharMatrix.cpp CharMatrix.h Util.h $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $< -o $@

.PHONY: clean

clean:
	rm *.o runPeykNowruzi

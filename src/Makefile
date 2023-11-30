
#
# Compiler flags
#
CXX = g++
CXXFLAGS = -c -fpie -DFULL_INPUT_MODE_ALLOWED=1 -DGUI_MODE=0 -std=c++23 -Wall -Wextra \
		   -Wpedantic -Wconversion -Wsign-conversion -Wshadow

#
# Linker flags
#
LDFLAGS = -static-pie

#
# Project files
#
DEPS = Scripts.hpp Log.hpp Util.hpp CharMatrix.hpp
SRCS = Launch.cpp Scripts.cpp Util.cpp CharMatrix.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = PeykNowruzi

#
# Precompiled header files
#
PCH_SRC = pch.hpp
PCH_OUT = pch.hpp.gch

#
# Debug build settings
#
DBGDIR = ../build/debug
DBGTARGET = $(DBGDIR)/$(TARGET)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGPCH_OUT = $(DBGDIR)/$(PCH_OUT)
DBGCXXFLAGS = -DPN_DEBUG=1 -Og -g
DBGLDFLAGS = -Og

#
# Release build settings
#
RELDIR = ../build/release
RELTARGET = $(RELDIR)/$(TARGET)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELPCH_OUT = $(RELDIR)/$(PCH_OUT)
RELCXXFLAGS = -DPN_DEBUG=0 -O3 -march=native -mtune=native -flto
RELLDFLAGS = -O3 -march=native -mtune=native -flto -s

.PHONY: all clean debug prep release remake

# Default build
all: prep release

#
# Debug rules
#
debug: $(DBGTARGET)

$(DBGTARGET): $(DBGOBJS)
	$(CXX) $(LDFLAGS) $(DBGLDFLAGS) $^ -o $@

$(DBGPCH_OUT): $(PCH_SRC)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) $< -o $@

$(DBGDIR)/Launch.o: Launch.cpp Scripts.hpp $(DBGPCH_OUT)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -include $(PCH_SRC) $< -o $@

$(DBGDIR)/Scripts.o: Scripts.cpp Scripts.hpp CharMatrix.hpp Log.hpp Util.hpp $(DBGPCH_OUT)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -include $(PCH_SRC) $< -o $@

$(DBGDIR)/Util.o: Util.cpp Util.hpp $(DBGPCH_OUT)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -include $(PCH_SRC) $< -o $@

$(DBGDIR)/CharMatrix.o: CharMatrix.cpp CharMatrix.hpp Log.hpp Util.hpp $(DBGPCH_OUT)
	$(CXX) $(CXXFLAGS) $(DBGCXXFLAGS) -include $(PCH_SRC) $< -o $@

#
# Release rules
#
release: $(RELTARGET)

$(RELTARGET): $(RELOBJS)
	$(CXX) $(LDFLAGS) $(RELLDFLAGS) $^ -o $@

$(RELPCH_OUT): $(PCH_SRC)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) $< -o $@

$(RELDIR)/Launch.o: Launch.cpp Scripts.hpp $(RELPCH_OUT)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) -include $(PCH_SRC) $< -o $@

$(RELDIR)/Scripts.o: Scripts.cpp Scripts.hpp CharMatrix.hpp Log.hpp Util.hpp $(RELPCH_OUT)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) -include $(PCH_SRC) $< -o $@

$(RELDIR)/Util.o: Util.cpp Util.hpp $(RELPCH_OUT)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) -include $(PCH_SRC) $< -o $@

$(RELDIR)/CharMatrix.o: CharMatrix.cpp CharMatrix.hpp Log.hpp Util.hpp $(RELPCH_OUT)
	$(CXX) $(CXXFLAGS) $(RELCXXFLAGS) -include $(PCH_SRC) $< -o $@

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

clean:
	rm -f $(RELTARGET) $(RELOBJS) $(DBGTARGET) $(DBGOBJS)

CXX = g++
INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/matrix_kernal.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: release

debug: CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCDIR) -g -O0
debug: $(BINDIR)/program_debug

release: CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCDIR) -O3
release: $(BINDIR)/program

# Profile target for gprof
profile: CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCDIR) -pg -O2
profile: $(BINDIR)/program_profile

# Build debug executable
$(BINDIR)/program_debug: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build profiling executable
$(BINDIR)/program_profile: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build release executable
$(BINDIR)/program: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup all generated files
clean:
	rm -rf $(OBJDIR) $(BINDIR) gmon.out

.PHONY: all clean debug release profile
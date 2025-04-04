CXX = g++
INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/matrix_kernal.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# 默认目标是 release（O3）
all: release

debug: CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCDIR) -g -O0
debug: $(BINDIR)/program_debug

release: CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCDIR) -O3
release: $(BINDIR)/program

$(BINDIR)/program_debug: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BINDIR)/program: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean debug release
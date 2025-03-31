# use g++ to compile the program and other compile options
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -O3

# specify the dictionaries
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# if you want to add more source files, add them to the SOURCES variable
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/matrix_kernal.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/program

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -g

# Executable name
TARGET = Bigint

# Source files
SRCS = Bigint.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link oject files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS) a.out

.PHONY: all clean

#Compiler
CXX = g++

#compiler flags
CXXFLAGS = -Wall -std=c++11 -g

#executable name
TARGET = bigInt

#source files
SRC = bigInt.cpp

#object files
OBJS = $(SRCS:.cpp=.o)

#Default rule

all: $(TARGET)

#Link oject files to create the executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Compile .cpp files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

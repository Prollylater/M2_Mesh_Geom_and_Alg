# Compiler
CXX = g++

# Compiler flags
#CXXFLAGS = -Wall -g
CXXFLAGS = -g

# Target executable
TARGET = mesh_app

# Source files
SRCS = Mesh.cpp

# Header files (optional, for dependencies)
HEADERS = Mesh.hpp Mesh_IO.hpp Vertices.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the executable
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile the .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to force recompilation
.PHONY: all clean

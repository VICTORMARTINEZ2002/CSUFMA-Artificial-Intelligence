CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = main

# Source files
SRCS = Source/main.cpp Source/Metrics/metrics.cpp Source/Functions/auxFunc.cpp Source/Leitura/read.cpp

# Object files (create object files in the same directories as source files)
OBJS = $(SRCS:%.cpp=%.o)

# Include directories
INCLUDES = -I./Source/Metrics -I./Source/Leitura -I./Source/Functions

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
Source/%.o: Source/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Debugging: print object files
print_objs:
	@echo "Object files: $(OBJS)"

# Clean up build files
cls:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned up object files and executable."

# Phony targets
.PHONY: clean print_objs
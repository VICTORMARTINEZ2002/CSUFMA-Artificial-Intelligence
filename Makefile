# Makefile for Windows (using MinGW or MSYS2)

CC = gcc
CFLAGS = -Wall -g

# Target executable name
TARGET = main.exe

# Object files
OBJS = bestFit.o main.o

# Default target
all: $(TARGET)

# Link the object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile main.cpp to create main.o
main.o: main.cpp bestFit.h
	$(CC) $(CFLAGS) -c main.cpp

# Compile myFunctions.cpp to create myFunctions.o
bestFit.o:
	$(CC) $(CFLAGS) -c bestFit.cpp


# Clean up object files and the executable
clean:
	del /f /q *.o $(TARGET)

OBJECTS = main.o stack.o 
SRC = main.cpp stack.cpp

CC = g++
CFLAGS = -c

TARGET = stack

$(TARGET): $(OBJECTS) stack.h
	$(CC) -o $(TARGET) $(OBJECTS)

clean: 
	rm $(OBJECTS) $(TARGET)
	

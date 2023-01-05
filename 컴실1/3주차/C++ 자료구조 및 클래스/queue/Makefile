OBJECTS = main.o queue.o 
SRC = main.cpp queue.cpp

CC = g++
CFLAGS = -c

TARGET = queue

$(TARGET): $(OBJECTS) queue.h
	$(CC) -o $(TARGET) $(OBJECTS)

clean: 
	rm $(OBJECTS) $(TARGET)
	

OBJECTS = main.o person.o student.o
SRC = main.cpp person.cpp student.cpp

CC = g++
CFLAGS = -c

TARGET = test

$(TARGET): $(OBJECTS) person.h student.h
	$(CC) -o $(TARGET) $(OBJECTS)

clean: 
	rm $(OBJECTS) $(TARGET)
	

main : main.o String.o
	g++ -o main main.o String.o

main.o : main.cpp
	g++ -c -o main.o main.cpp

String.o : String.cpp
	g++ -c -o String.o String.cpp

main.o String.o : String.hpp

.PHONY : clean
clean :
	rm main main.o String.o

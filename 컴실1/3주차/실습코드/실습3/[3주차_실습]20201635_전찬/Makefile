main : main.o array.o rangearray.o
	g++ -o main main.o array.o rangearray.o

main.o : main.cpp Array.h RangeArray.h
	g++ -c -o main.o main.cpp

array.o : array.cpp Array.h RangeArray.h
	g++ -c -o array.o array.cpp

rangearray.o : rangearray.cpp Array.h RangeArray.h
	g++ -c -o rangearray.o rangearray.cpp

.PHONY : clean
clean : 
	rm main main.o array.o rangearray.o 

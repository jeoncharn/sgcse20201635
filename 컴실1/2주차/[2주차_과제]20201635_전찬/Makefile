starwars_exe : main.o count_func.o print_func.o
	gcc -o starwars_exe main.o count_func.o print_func.o

%.o : %.c
	gcc -c -o $@ $<

.PHONY : clean

clean :
	rm *.o starwars_exe

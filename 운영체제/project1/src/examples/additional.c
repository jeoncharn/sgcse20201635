#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

int main(int argc, char* argv[]){
    
    int input_data[4];

    if(argc != 5){
        printf("additional needs 4 inputs but there are %d inputs.\n", argc-1);
        return 1;
    }

    for(int i=0; i<4; i++){
        input_data[i] = atoi(argv[i + 1]);
    }

    printf("%d %d\n", fibonacci(input_data[0]), max_of_four_int(input_data[0], input_data[1], input_data[2], input_data[3]));

    return 0;
}

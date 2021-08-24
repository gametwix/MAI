#include "stdio.h"
#include "stdlib.h"
#include "bitonic.h"
#include <sys/time.h>

#define MAXINT 2147483647

#define timer

int SizeStep(int Num){
    int i = 1;
    while(i < Num)
        i *= 2;
    return i;
}


int main(int argc, char *argv[]){
    int threads = 1;

    if(argc == 2){
        threads = atoi(argv[1]);
    }

    int input_size;
    scanf("%d",&input_size);

    //находим ближашее число 2^k >= input_size 
    int size_array = SizeStep(input_size); 
    int *array = malloc(sizeof(int)*size_array);
    
    for(int i = 0; i < input_size; ++i)
        scanf("%d",array+i);
    for(int i = input_size; i < size_array; ++i)
        array[i] = MAXINT;

    #ifdef timer
    struct timeval startwtime, endwtime;
    gettimeofday(&startwtime, NULL);
    #endif

    bitonicsort(array, size_array, threads);

    #ifdef timer
    gettimeofday(&endwtime, NULL);
    double time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("%f\n", time);
    #endif


    #ifndef timer
    for(int i=0;i<input_size;++i){
        printf("%d\n",array[i]);
    }
    #endif

    free(array);
    return 0;
}
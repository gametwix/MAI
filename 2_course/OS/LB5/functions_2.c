#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"

double my_log(double num, double base){
    return log2(num)/log2(base);
}

float Square(float a, float b){
    return a*b/2;
}

char* Translation(long x){
    char *result = NULL;
    int size = floor(my_log(x,3)) + 2;
    result = malloc(sizeof(char) * size);
    result[size - 1] = '\0';
    while(x > 0){
        --size;
        result[size - 1] = (x % 3) + '0';
        x /= 3;
    }
    return result;
}


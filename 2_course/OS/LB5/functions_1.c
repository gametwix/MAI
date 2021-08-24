#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"

float Square(float a, float b){
    return a*b;
}

char* Translation(long x){
    char *result = NULL;
    int size = floor(log2(x)) + 2;
    result = malloc(sizeof(char) * size);
    result[size - 1] = '\0';
    while(x > 0){
        --size;
        result[size - 1] = (x % 2) + '0';
        x /= 2;
    }
    return result;
}


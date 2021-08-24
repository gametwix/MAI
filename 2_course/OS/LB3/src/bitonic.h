#pragma once

#include "pthread.h"

#define UP 1
#define DOWN 0

typedef struct ArgsBitonic{
    int *array;
    int size;
    int start;
    int dir;
}ArgsBitonic;

void InitArgs(ArgsBitonic *args, int *array, int size, int start, int dir);
void Comparator(int *array, int i, int j, int dir);
void BitonicMergeSinglThread(ArgsBitonic *args);
void BitonicSortSinglThread(ArgsBitonic *args);
void BitonicMergeMultiThreads(ArgsBitonic *args);
void BitonicSortMultiThreads(ArgsBitonic *args);
void bitonicsort(int *array, int size, int threads);
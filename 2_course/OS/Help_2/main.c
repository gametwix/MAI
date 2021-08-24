/*
Лабораторная работа №3 по курсу "Операционные системы"
Задание: Перемножение двух матриц с использованием потоков, потоки синхронезировать при помощи mutex.
*/


#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>


// Global variables
#define NUM_OF_THREADS 100
pthread_mutex_t mut;
// size of matrix
static int A, B, C, D;
// Determinate the element result's matrix
static int string = -1;
static int column = 0;
// counter for pthread
static int count = 0;

// Struct for complex number representation
typedef struct Complex{
    int real;
    int imaginary;
} Complex;

typedef struct Param{
    void* myData;
    int sizeColomn;
    int *Str;
    int numStr;
} Param;

// Struct with for pointers on three matriсes
typedef struct Data{
    Complex** matrix1;
    Complex** matrix2;
    Complex** result;
} Data;

// The function, which will be transmitted in the threads
void* Produce(int str,int col,void* ptr){
    Data* myData = (Data*) ptr;
    for (int k = 0; k < B; ++k){
        myData->result[str][col].real += myData->matrix1[str][k].real*myData->matrix2[k][col].real - myData->matrix1[str][k].imaginary*myData->matrix2[k][col].imaginary; 
        myData->result[str][col].imaginary += myData->matrix1[str][k].real*myData->matrix2[k][col].imaginary + myData->matrix1[str][k].imaginary*myData->matrix2[k][col].real;
    }
    return NULL;
}

void* thread_mission(Param* Param){
    for(int i = 0; i < Param->numStr;++i){
        for(int j = 0; j < Param->sizeColomn;++j){
            Produce(Param->Str[i],j,Param->myData);
        }
    }
        
    return NULL;
}

int main(int argc, char* argv[]){

    struct timespec start, finish;

    if (argc != 2) {
        printf("Syntax: ./main Number_of_threads\n");
        return 1;
    }

    // restrictions from above for threads
    int num = atoi(argv[1]);
    if(*argv[1] > NUM_OF_THREADS){
        num = NUM_OF_THREADS;
    }
    
    // Create array variables for threads
    pthread_t* threads = (pthread_t*)calloc(num, sizeof(pthread_t));
    if (threads == NULL) {
        printf("Can't allocate space for threads\n");
        return 2;
    }

    // Sizes of two matrices
    printf("Enter first matrix size:\n");
    scanf("%d %d", &A, &B);
    printf("Enter second matrix size:\n");    
    scanf("%d %d", &C, &D);
    
    if(B != C){
        printf("It is impossible to multiply matrices!\n");
        return -1;
    }
    // Stracut for transmitted data in thread
    Data* myData = (Data*) malloc(sizeof(Data));
    
    // Initialization
    myData[0].matrix1 = (Complex**) malloc(sizeof(Complex*)*A);
    for(int i = 0; i < A; ++i){
        myData[0].matrix1[i] = (Complex*) malloc(sizeof(Complex)*B);
    }

    myData[0].matrix2 = (Complex**) malloc(sizeof(Complex*)*C);
    for(int i = 0; i < C; ++i){
        myData[0].matrix2[i] = (Complex*) malloc(sizeof(Complex)*D);
    }

    myData[0].result = (Complex**) malloc(sizeof(Complex*)*A);
    for(int i = 0; i < A; ++i){
        myData[0].result[i] = (Complex*) malloc(sizeof(Complex)*D);
    }


    // filling the arrays
    printf("Enter the first matrix:\n");
    for(int i = 0; i < A; ++i){
        for(int j = 0; j < B; ++j){
            scanf("%d", &myData->matrix1[i][j].real);
            scanf("%d",&myData->matrix1[i][j].imaginary);
        }
    }

    printf("Enter the second matrix:\n");
    for(int i = 0; i < C; ++i){
        for(int j = 0; j < D; ++j){
            scanf("%d", &myData->matrix2[i][j].real);
            scanf("%d",&myData->matrix2[i][j].imaginary);
        }
    }

    for(int i = 0; i < A; ++i){
        for(int j = 0; j < D; ++j){
            myData->result[i][j].real = (int) 0;
            myData->result[i][j].imaginary = (int) 0;
        }
    }
    
    printf("First matrix:\n");
    for(int i = 0; i < A; ++i){
        for(int j = 0; j < B; ++j){
            if(myData->matrix1[i][j].imaginary >= 0)
                printf("%d+%d*i ", myData->matrix1[i][j].real, myData->matrix1[i][j].imaginary);
            if(myData->result[i][j].imaginary < 0)
                printf("%d-%d*i ", myData->matrix1[i][j].real, myData->matrix1[i][j].imaginary);
        }
        printf("\n");
    }

    printf("Second matrix:\n");
    for(int i = 0; i < C; ++i){
        for(int j = 0; j < D; ++j){
            if(myData->matrix2[i][j].imaginary >= 0)
                printf("%d+%d*i ", myData->matrix2[i][j].real, myData->matrix2[i][j].imaginary);
            else
                printf("%d-%d*i ", myData->matrix2[i][j].real, myData->matrix2[i][j].imaginary);
        }
        printf("\n");
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    pthread_mutex_init(&mut, NULL);


    // create threads
    Param P[num];
    for(int i = 0;i<num;++i){
        P[i].numStr = 0;
        P[i].Str = NULL;
        P[i].myData = myData;
        P[i].sizeColomn = D;
    }
    for(int i = 0;i<A;++i){
        P[i%num].numStr+=1;
        P[i%num].Str = realloc(P[i%num].Str,P[i%num].numStr*sizeof(int));
        P[i%num].Str[P[i%num].numStr - 1] = i;
    }
    for(int j = 0; j < num; ++j){
        pthread_create(&threads[j], NULL,(void*) &thread_mission, &P[j]);  
    }
    

    for (int i = 0; i < num; i++)
        pthread_join(threads[i], NULL);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    printf("Result matrix:\n");
    for(int i = 0; i < A; ++i){
        for(int j = 0; j < D; ++j){
            if(myData->result[i][j].imaginary >= 0)
                printf("%d+%d*i ", myData->result[i][j].real, myData->result[i][j].imaginary);
            else
                printf("%d%d*i ", myData->result[i][j].real, myData->result[i][j].imaginary);
        }
        printf("\n");
    }
    
   
    
    double elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    pthread_mutex_destroy(&mut);
    printf("Time: %.4f seconds\n", elapsed);
    
    free(myData->matrix1);
    free(myData->matrix2);
    free(myData->result);
    free(myData);
    return 0;
}
#include "stdio.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>


int main(int argc,char **argv){
    if(argc < 5){
        printf("Arguments error");
        return 1;
    }
    char *filename = argv[1];
    char *sh_data_name = argv[2];
    char *sh_data_size_name = argv[3];
    char *mutex_name = argv[4];

    int fd_shared_data = shm_open(sh_data_name, O_RDWR | O_CREAT, S_IRWXU);
    int fd_shared_data_size = shm_open(sh_data_size_name, O_RDWR | O_CREAT, S_IRWXU);
    int fd_mutex = shm_open(mutex_name,O_RDWR | O_CREAT, S_IRWXU);
    if(fd_shared_data == -1 || fd_shared_data_size == -1 || fd_mutex == -1){
        printf("Error: shared memory open\n");
        return -1;
    }
    int *Data = (int*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data, 0);
    int *Size = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data_size, 0);
    pthread_mutex_t *Lock = (pthread_mutex_t*) mmap(NULL,sizeof(pthread_mutex_t*),PROT_READ | PROT_WRITE, MAP_SHARED,fd_mutex,0);
    if (Data == MAP_FAILED || Size == MAP_FAILED || Lock  == MAP_FAILED) {
        printf("Error: map file\n");
        return -1;
    }
    FILE *file;
    file = fopen(filename,"w");
    if(file == NULL){
        printf("Error: fopen file\n");
        return -1;
    }
    while ((*Size) != -1){
        if(pthread_mutex_lock(Lock) != 0){
            printf("Error: mutex lock\n");
            return -1;
        }
        if(*Size > 0){
            long long sum = 0;
            for(int i = 0;i < *Size; ++i){
                sum += Data[i];
            }
            *Size = 0;
            fprintf(file,"%lld\n",sum);
        }
        if(pthread_mutex_unlock(Lock) != 0){
            printf("Error: mutex unlock\n");
            return -1;
        }
    }

    if(fclose(file) != 0){
        printf("Error: fclose file\n");
        return -1;
    }
    if(munmap(Data,getpagesize()) != 0){
        printf("Error: unmap file\n");
        return -1;
    }
    if(munmap(Size,sizeof(int)) != 0){
        printf("Error: unmap file\n");
        return -1;
    }
    if(munmap(Lock,sizeof(pthread_mutex_t*)) != 0){
        printf("Error: unmap file\n");
        return -1;
    }
    if(close(fd_shared_data) < 0){
        printf("Error: close file\n");
        return -1;
    }
    if(close(fd_shared_data_size) < 0){
        printf("Error: close file\n");
        return -1;
    }
    if(close(fd_mutex) < 0){
        printf("Error: close file\n");
        return -1;
    }
    if(shm_unlink(sh_data_name) != 0){
        printf("Error: shared memory unlink\n");
        return -1;
    }
    if(shm_unlink(sh_data_size_name) != 0){
        printf("Error: shared memory unlink\n");
        return -1;
    }
    if(shm_unlink(mutex_name)!= 0){
        printf("Error: shared memory unlink\n");
        return -1;
    }
    return 0;
}


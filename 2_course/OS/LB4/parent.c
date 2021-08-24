#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

#define SH_NAME "my_shared_mem"
#define SH_SIZE_NAME "my_shared_mem_size"
#define MUTEX_NAME "my_mutex"

void wait(int *elem, int num){
    while (*elem != num){
    }
}

int main()
{
    int fd_shared_data = shm_open(SH_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int fd_shared_data_size = shm_open(SH_SIZE_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int fd_mutex = shm_open(MUTEX_NAME,O_RDWR | O_CREAT, S_IRWXU);

    if(fd_shared_data == -1 || fd_shared_data_size == -1 || fd_mutex == -1){
        printf("Error: shared memory open\n");
        return -1;
    }
    if(ftruncate(fd_shared_data,getpagesize()) == -1){
        printf("Error: ftruncate\n");
        return -1;
    }
    if(ftruncate(fd_shared_data_size,sizeof(int)) == -1){
        printf("Error: ftruncate\n");
        return -1;
    }
    if(ftruncate(fd_mutex,sizeof(pthread_mutex_t*)) == -1){
        printf("Error: ftruncate\n");
        return -1;
    }

    int *Data = (int*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data, 0);
    int *Size = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data_size, 0);
    pthread_mutex_t *Lock = (pthread_mutex_t*) mmap(NULL,sizeof(pthread_mutex_t*),PROT_READ | PROT_WRITE, MAP_SHARED,fd_mutex,0);
    if (Data == MAP_FAILED || Size == MAP_FAILED || Lock  == MAP_FAILED) {
        printf("Error: map file\n");
        return -1;
    }
    pthread_mutexattr_t MutexAttribute;
    if(pthread_mutexattr_setpshared(&MutexAttribute, PTHREAD_PROCESS_SHARED) != 0){
        printf("Error: set shared attribute mutex\n");
        return -1;
    }
    *Size = 0;
    if(pthread_mutex_init(Lock, &MutexAttribute) != 0){
        printf("Error: mutex init\n");
        return -1;
    }    

    char *filename = NULL;
    size_t sizename = 0;
    getline(&filename,&sizename,stdin);
    filename[strlen(filename)-1] = '\0';

    int id = fork();

    if(id == -1){
        printf("Error: fork\n");
        return -1;
    } else if(id == 0) {

        execl("./child","child",filename,SH_NAME,SH_SIZE_NAME,MUTEX_NAME,(char*) NULL);
    } else {

        int num;
        char sym;
        if(pthread_mutex_lock(Lock) != 0){
            printf("Error: mutex lock\n");
            return -1;
        }
        while(scanf("%d%c",&num,&sym) > 0){
            Data[*Size] = num;
            *Size += 1;
            if(sym == '\n'){
                if(pthread_mutex_unlock(Lock) != 0){
                    printf("Error: mutex unlock\n");
                    return -1;
                }
                wait(Size,0);
                if(pthread_mutex_lock(Lock) != 0){
                    printf("Error: mutex lock\n");
                    return -1;
                }
            }
        }
        *Size = -1;
        if(pthread_mutex_unlock(Lock) != 0){
            printf("Error: mutex unlock\n");
            return -1;
        }
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

    return 0;
}



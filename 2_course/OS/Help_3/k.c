#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>

#define SIZEBR 2000
#define SH_NAME "my_shared_mem"
#define SH_SIZE_NAME "my_shared_mem_size"
#define MUTEX_NAME "my_mutex"

int main()
{
	// Read file name
    char* name = NULL;
    size_t len;
    printf("Enter a filename with tests: ");
    if(getline(&name, &len, stdin) == -1){
        perror("getline");
    }
	name[strlen(name) - 1] = '\0';
	
	// Create file descriptors
	int fd_shared_data = shm_open(SH_NAME, O_RDWR | O_CREAT, S_IRWXU);
	int fd_shared_data_size = shm_open(SH_SIZE_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int fd_mutex = shm_open(MUTEX_NAME,O_RDWR | O_CREAT, S_IRWXU);
	//int fd_file = shm_open(name, O_RDWR | O_CREAT,S_IRWXU);
	if((fd_shared_data == -1) || (fd_shared_data_size == -1)|| (fd_mutex == -1)){
		perror("Error of shm_open file!");
		return -1;
	}
	// Define  size files
/*	struct stat statbuf;
	if (fstat(fd_file, &statbuf) < 0 ){
	    perror("fstat");
		return -2;
	}*/
	ftruncate(fd_mutex,sizeof(pthread_mutex_t*));
	ftruncate(fd_shared_data,getpagesize());
	ftruncate(fd_shared_data_size,sizeof(int));
	
	// mapping file
	//len = statbuf.st_size;
	//char* src = (char*) mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd_file, 0);
	pthread_mutex_t *Lock = (pthread_mutex_t*) mmap(NULL,sizeof(pthread_mutex_t*),PROT_READ | PROT_WRITE, MAP_SHARED,fd_mutex,0);
    float* data = (float*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data, 0);
	int* sizes_ = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data_size, 0);
	
	pthread_mutexattr_t MutexAttribute;
    pthread_mutexattr_setpshared(&MutexAttribute, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(Lock, &MutexAttribute);

	// Creating child process
	int id = fork();
	if (id == -1)
	{
		perror("Error: Can't creating fork.");
		return -3;
	}
	if (id == 0)
	{ // Child process
	
		int err = execl("./child", "child",name,SH_NAME,SH_SIZE_NAME,MUTEX_NAME,NULL);
		if(err == -1){
			perror("Eror of executing child programm");
			return -1;
		}
	}
	else
	{ //Parent process
		wait(NULL);
		for(int i = 0; i < *sizes_; ++i){
			printf("%f ", data[i]);
		}
    }
		
		munmap(Lock,sizeof(pthread_mutex_t*));
		//munmap(src,len);
		munmap(data, getpagesize());
		munmap(sizes_, sizeof(int));
		//Close fd shared memory
		close(fd_shared_data);
		close(fd_mutex);
		//close(fd_file);
		close(fd_shared_data_size);
		//Unlick shared memory
	    shm_unlink(SH_NAME);
    	shm_unlink(MUTEX_NAME);
		shm_unlink(name);
		shm_unlink(SH_SIZE_NAME);
		return 0;
}
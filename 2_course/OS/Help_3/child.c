#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define SIZEBR 2000

int main(int argc, char* argv[]){
	
	char* filename = argv[1];
    char* sh_data_name = argv[2];
	char* sh_size_data_name = argv[3];
    char* mutex_name = argv[4];

    //Create fd shared file
    int fd_sh_data_name = shm_open(sh_data_name, O_RDWR | O_CREAT, S_IRWXU);
    int fd_mutex_name = shm_open(mutex_name,O_RDWR | O_CREAT, S_IRWXU);
	int fd_filename = shm_open(filename,O_RDWR | O_CREAT, S_IRWXU);
	int fd_sh_size_data_name = shm_open(sh_size_data_name,O_RDWR | O_CREAT, S_IRWXU);
	if((fd_sh_data_name == -1) ||(fd_filename == -1) || (fd_mutex_name == -1) ||(fd_sh_size_data_name == -1)){
		perror("Error of shm_open file!");
		return -6;
	}

	struct stat statbuf;
	if (fstat(fd_filename, &statbuf) < 0 ){
	    perror("fstat");
		return -9;
	}
	ftruncate(fd_mutex_name,sizeof(pthread_mutex_t*));
	ftruncate(fd_sh_data_name,getpagesize());
	ftruncate(fd_sh_size_data_name,sizeof(int));

	size_t len = statbuf.st_size;
	
	//Map shared files in memory
    char* str = (char*) mmap(NULL,len,PROT_READ | PROT_WRITE, MAP_SHARED, fd_filename, 0);
	float* result_mass = (float*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED, fd_sh_data_name, 0);
    pthread_mutex_t *Lock = (pthread_mutex_t*) mmap(NULL,sizeof(pthread_mutex_t*),PROT_READ | PROT_WRITE, MAP_SHARED,fd_mutex_name,0);
	int* sizes_ = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED, fd_sh_size_data_name, 0);

	// dynamic string
	size_t index = 0;
	//char c;
	float data[2];
	//bool fstvalue = 0;
	/*while(1){
		// Reading char
		pthread_mutex_lock(Lock);
		if(read(STDIN_FILENO, &c, sizeof(char)) == -1){
			perror("Error reading char");
			return -1;
		}
		// chech on
		if((c == ' ') || (c =='\n')){
			if(c == '\n'){
				if( data[1] == 0){
					perror("Segmentation 0");
					return -1;
				}
				reslut_mass[index++] = data[0]/data[1];
				*sizes_++;
				break;
			}
			if (index > getpagesize() - 1){
				
				float* tmp = (float*) malloc(getpagesize());
				memcpy(tmp,reslut_mass,getpagesize());
				munmap(reslut_mass,getpagesize());
				
				if((str = (char*)realloc(str,sizeof(char)*SIZEBR + 1)) == NULL){
					perror("Err realloc");
					return -1;
				}
			}
			if(!fstvalue){
				str[index] = '\0';
				data[0] = atof(str);
				fstvalue = 1;
				index = 0;
			}
			else{
				str[index] = '\0';
				data[1] = atof(str);
				
				// chech on segmentation 0
				if( data[1] == 0){
					perror("Segmentation 0");
					return -1;
				}
				res = data[0]/data[1];
				data[0] = data[1];
				printf("%f ",res);
				index = 0;
			}
		}
		else{
			// check on buffer overflow
			if (index > SIZEBR - 1){
				if((str = (char*)realloc(str,sizeof(char)*SIZEBR*2)) == NULL){
					perror("Err realloc");
					return -1;
				}
				str[index++] = c;
			}
			else{
				str[index++] = c;
			}
		}
		pthread_mutex_unlock(Lock);
	}*/
	int j = 0;
	//float res;
	*sizes_ = 0;
	char* substr = (char*) malloc(sizeof(char)*256);
	for(int i = 0; i < len; i = i+j){
		int k;
		for(j = i, k = 0; j < len; ++j, ++k){
			if((str[j] == ' ') ||(str[j] == '\n')){
				substr[k] = '\0';
				break;
			}
			substr[k] = str[j];
		}
		if(i == 0){
			data[0] = atof(substr);
			continue;
		}
		if(i != 0){
			data[1] = atof(substr);
			if(data[1] == 0){
				perror("Division 0");
				return -10;
			}
			result_mass[index++] = data[0] / data[1];
			*sizes_ += 1;
			data[0] = data[1];
			//printf("%f ", res);
		}
	}
	free(substr);


	munmap(str,len);
    munmap(Lock,sizeof(pthread_mutex_t*));
    munmap(result_mass,getpagesize());
	munmap(sizes_, sizeof(int));

    close(fd_sh_data_name);
    close(fd_mutex_name);
	close(fd_sh_size_data_name);
    close(fd_filename);

	shm_unlink(sh_data_name);
    shm_unlink(mutex_name);
    shm_unlink(filename);
    shm_unlink(sh_size_data_name);
	return 0;
}

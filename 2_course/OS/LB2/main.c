#include "unistd.h"
#include "string.h"
#include "stdio.h"

int main(){
    int fd[2];
    if(pipe(fd) < 0){
        printf("Error pipe create\n");
        return -1;
    }
    char *filename = NULL;
    size_t sizename = 0;
    getline(&filename,&sizename,stdin);
    filename[strlen(filename)-1] = '\0';
    int id = fork();
    if(id == -1){
        printf("Error fork\n");
        return -1;
    }else if(id == 0){
        close(fd[1]);
        dup2(fd[0],0);
        execl("./child","child",filename,(char*) NULL);
    } else {
        close(fd[0]);
        char ch;
        while(scanf("%c",&ch) != EOF){
            write(fd[1],&ch,sizeof(ch));  
        }
        close(fd[1]);
    }
    return 0;
}


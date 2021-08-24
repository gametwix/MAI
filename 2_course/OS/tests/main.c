#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
    int fd[2],count; //file descriptor, counter
    if ( pipe(fd) < 0 ) {
        perror("Cannot create pipe");
        return EXIT_FAILURE;
    }
    char fname[100];
    //input filename
    printf("Input file name: ");
    scanf("%[^\n]s", fname);
    //open file
    FILE* fp = fopen(fname, "r");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    // FORK
    int id = fork();
    //error FORK
    if (id == -1)
    {
        perror("Fork error");
        return EXIT_FAILURE;
    }
    //CHILD WORK
    else if (id == 0)
    {
        close(STDIN_FILENO);
        dup(fileno(fp));
        close(fileno(fp));
        
        close(STDOUT_FILENO);
        dup(fd[0]);
        close(fd[0]);
        
        close(fd[1]);
        execlp("./calc", NULL);
    }
    //PARENT WORK
    else
    {
        close(fd[1]);
        close(fileno(fp));
        
        char buffer[100];
        int readen = read(fd[0],buffer, 100);
        while (readen > 0) {
            write(STDOUT_FILENO,buffer,readen);
            readen = read(fd[0],buffer, 100);
        }
        
        close(fd[0]);        
        wait(NULL);
    }
    return 0;
}


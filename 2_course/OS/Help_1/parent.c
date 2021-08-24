// Лабораторная работа № 2
// Вариант 16

#include "stdio.h"
#include "string.h"
#include "unistd.h"

int main() {
    printf("Введите имя файла: ");
    char filename [200];
    scanf("%s", filename);
    FILE *file_to_write = fopen(filename, "w");
    int fd1[2];
    int fd2[2];
    if (pipe(fd2) < 0) {
        printf("Pipe error!");
        return -1;
    }
    if (pipe(fd1) < 0) {
        printf("Pipe error!");
        return -1;
    }
    int ID = fork();
    if (ID < 0) {
        printf("Fork error!");
        return -1;
    } else if (ID > 0) { // Родительский процесс
        close(fd1[0]);
        close(fd2[1]);
        char inp[200];
        char err[200];
        int is_err;
        while(scanf("%s",inp) > 0)
        {
            inp[strlen(inp)] = '\n';
            write(fd1[1],inp,strlen(inp));
            read(fd2[0],&is_err,sizeof(is_err));
            if(is_err){
                read(fd2[0],err,sizeof(err));
                printf("Error line: %s\n",err);
            }
            memset(inp,'\0',200);
        }

        close(fd1[1]);
        close(fd2[0]);
    } else { // Дочерний процесс
        close(fd1[1]);
        close(fd2[0]);
        dup2(fd1[0],STDIN_FILENO);
        dup2(fileno(file_to_write),STDOUT_FILENO);
        char arg[1] = {(char) fd2[1]};
        execl("./child","child",arg,(char *) NULL);
    }
    fclose(file_to_write);
}
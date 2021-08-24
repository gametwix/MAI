#include "stdio.h"
#include "unistd.h"


int string_validation(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        i++;
    }
    if (line[i-1] == '.' || line[i-1] == ';') {
        return 0;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if(argc < 2)
        return 0;
    int pipe = (int) argv[1][0];
    int err;
    char line[200];
    while(scanf("%s", line) > 0) {
        if (string_validation(line) == 0) {
            printf("%s\n", line);
            fflush(stdout);
            err = 0;
            write(pipe,&err, sizeof(err));
        } else {
            err = 1;
            write(pipe,&err, sizeof(err));
            write(pipe,line, sizeof(line));
        }
    }
}
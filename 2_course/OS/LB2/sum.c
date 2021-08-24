#include "stdio.h"
#include "string.h"

int main(int argc, char **argv){
    if(argc != 2){
        return -1;
    }
    long long sum = 0;
    int num;
    char ch;
    FILE *file;
    file = fopen(argv[1], "w");
    while(scanf("%d%c",&num,&ch) != EOF){
        sum += num;
        if(ch == '\n'){
            fprintf(file,"%lld\n",sum);
            sum = 0;
        }
    }
    fclose(file);
    return 0;
}


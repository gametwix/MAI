#include <stdio.h>
#include "functions.h"

int main(){
    int sw = -1;
    while(scanf("%d",&sw) > 0){
        if(sw == 1){
            float size_1, size_2;
            scanf("%f %f",&size_1,&size_2);
            printf("%f\n",Square(size_1,size_2));
        } else if(sw == 2) {
            long x = 0;
            scanf("%ld",&x);
            printf("%s\n",Translation(x));
        }
    }
    return 0;
}
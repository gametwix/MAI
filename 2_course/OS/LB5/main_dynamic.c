#include <dlfcn.h>
#include <stdio.h>


int main(){
    float (*Square)(float, float) = NULL;
    char* (*Translation)(long) = NULL;
    int sw = -1;
    char* libs[] = {"lib1.so","lib2.so"};
    int lib = 0;
    void* handle = NULL;
    handle = dlopen(libs[lib],RTLD_LAZY);
    if (!handle) {
        printf("%s\n", dlerror());
        return 1;
    }
    Square = dlsym(handle,"Square");
    Translation = dlsym(handle,"Translation");
    while(scanf("%d",&sw) > 0){
        if(sw == 1){
            float size_1, size_2;
            scanf("%f %f",&size_1,&size_2);
            printf("%f\n",(Square)(size_1,size_2));
        } else if(sw == 2) {
            long x = 0;
            scanf("%ld",&x);
            printf("%s\n",Translation(x));
        } else if(sw == 0) {
            dlclose(handle);
            lib = (lib + 1) % 2;
            handle = dlopen(libs[lib],RTLD_LAZY);
            Square = dlsym(handle,"Square");
            Translation = dlsym(handle,"Translation");
        }
    }
    dlclose(handle);
}
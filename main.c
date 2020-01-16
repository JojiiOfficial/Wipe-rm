#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>

bool isDir(const char *path);


bool deleteFile(const char *file){
    if (!isDir(file)){
        FILE *f;
        if (!(f = fopen(file, "r+"))) {
            printf("Error opening file!\n");
            return false;
        }
        fseek(f, 0, SEEK_END);
        long int size = ftell(f);
        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < size; i++){
            fputc(0, f);
        }
        
        fflush(f);
        fclose(f);
    } else {
        printf("is dir");
    }
    return false;
}

bool isDir(const char *path){
    DIR *dir = opendir(path);
    if (dir != NULL){
        closedir(dir);
        return true;
    }
    return false;
}

void main(){
    deleteFile("test");
}

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

char** listDir(DIR *dir){
    struct dirent *de;
    char **dd = (char**) malloc(sizeof(char)+10000);
    int i = 0;
    while((de = readdir(dir)) != NULL){
        if (de == NULL){
            break;
        }
        char *name = de->d_name;
        if ((!strcmp(".", name)) || (!strcmp("..", name))){
            continue;
        }
        dd[i] = name;
        i++;
    }
    if (i == 0){
        return NULL;
    }
    return dd;
}

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0){
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

bool deleteFile(const char *file){
    if (!isDirectory(file)){
        FILE *f;
        if (!(f = fopen(file, "r+"))) {
            printf("Error opening file: %s\n",file);
            return false;
        }
        printf("deleting file: %s\n", file);
        fseek(f, 0, SEEK_END);
        long int size = ftell(f);
        fseek(f, 0, SEEK_SET);
        for (int i = 0; i <= size; i++){
            fputc(0, f);
        }
        
        fflush(f);
        fclose(f);
    } else {
        DIR *dir = opendir(file);
        struct dirent *de;
        int i = 0;

        while((de = readdir(dir)) != NULL){
            if (de == NULL){
                break;
            }
            if ((!strcmp(".", de->d_name)) || (!strcmp("..", de->d_name))){
                continue;
            }

            char *path = (char*) malloc(strlen(file) + strlen(de->d_name) + 2*sizeof(char*) + 1);
            memset(path, 0, sizeof(path));
            strcat(path, file);
            strcat(path, "/");
            strcat(path, de->d_name);
            deleteFile(path);
            free(path);

            i++;
        }
        free(de);
        if (dir != NULL){
            closedir(dir);
        }
    }
    return false;
}

void main(){
    deleteFile("test");
}

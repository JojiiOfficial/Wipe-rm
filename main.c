#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>

void remalloc(char *in, size_t addSize){
    char val = *in;
    in = (char *) malloc(addSize);
   // in[0] = val;
}

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
    return dd;
}

bool deleteFile(const char *file){
    DIR *dir = opendir(file);
    if (dir == NULL){
        /*FILE *f;
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
        fclose(f);*/
    } else {
        char **dirdata = listDir(dir);
        int i = 0;
        while (1){
            if (dirdata[i] == NULL){
                break;
            }
            char *file = dirdata[i];
            printf("%d, %s\n",i,file);
            i++;
        }
        if (dir != NULL){
            closedir(dir);
        }
    }
    return false;
}

void main(){
    deleteFile("./");
}

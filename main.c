#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0){
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

bool delete(const char *file, bool recursive, bool quiet, bool verbose, bool force, bool zeroOnly){
    if (!isDirectory(file)){
        FILE *f;
        if (!(f = fopen(file, "r+"))) {
            printf("Error opening file: '%s'\n",file);
            if (verbose && !force){
                printf("Use -f to skip errors\n");
            }
            return false;
        }
        if (!quiet){
            char *pre = "deleting";
            if(zeroOnly){
                pre = "zeroing";
            }
            printf("%s file: '%s'! ", pre, file);
        }

        fseek(f, 0, SEEK_END);
        long int size = ftell(f);
        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < size; i++){
            fputc(0, f);
        }
        fflush(f);
        fclose(f);
        if (verbose){
            printf("Overwritten %d bytes\n", size);
        } else {
            printf("\n");
        }

        if (!zeroOnly){
            if (remove(file) != 0){
                printf("Error deleting file: %s\n", file);
                return false;
            }
        }
    } else {
        if (!recursive){
            printf("'%s' is a folder. Use -r to delete it recursively\n", file);
            return false;
        }
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
            delete(path, recursive, quiet, verbose, force, zeroOnly);
            i++;
        }

        free(de);
        if (dir != NULL){
            closedir(dir);
        }
        if (remove(file) != 0){
            printf("Error removing folder: %s\n", file);
            return false;
        }
    }
    return true;
}

void usage(char* s, short exitcode){
    printf("Usage: %s [-hrfqv] [file...]\n",s);
    exit(exitcode);
}

void main(int argc, char** argv){
    int opt;
    bool recursive, force, verbose, quiet, zeroOnly;

    while ((opt = getopt(argc, argv, "rfqvhz")) != -1) {
        switch (opt) {
        case 'r': recursive = true; break;
        case 'f': force = true; break;
        case 'q': quiet = true; break;
        case 'v': verbose = true; break;
        case 'z': zeroOnly = true; break;
        case 'h': usage(argv[0],0); break;
        default:
            usage(argv[0], EXIT_FAILURE);
        }
    }

    for (int i = 1; i < argc; i++) {
        if (!strncmp(argv[i], "-",1)){
            continue;
        }
        bool success = delete(argv[i], recursive, quiet, verbose, force, zeroOnly);
        if (!success){
            if (!force){
                exit(EXIT_FAILURE);
            }
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <dirent.h>
#include <menu.h>


char *leeDir(char *dir){
    DIR *dirP = opendir(dir);
    struct dirent *d_dir;

    char *espacioDirectorios = NULL;
    int tamanototal = 0;
    
    if (dirP == NULL){
        printf("error al abrir directorio");
    }else{
        while ((d_dir = readdir(dirP))!=NULL)
        {
            //asignar memoria por nombre de archivo/directorio
            int tamDirectorio = sizeof(char) * (strlen(d_dir->d_name) + 1);
            tamanototal = tamanototal + tamDirectorio;
        }
        espacioDirectorios = (char *)malloc(tamanototal);

        closedir(dirP);
        dirP = opendir(dir);
        int ptr=0;
        while ((d_dir = readdir(dirP))!=NULL)
        {
            char *currItem = (char *)calloc(strlen(d_dir->d_name)+1, sizeof(char));
            strcat(currItem, d_dir->d_name);
            strcat(currItem, "\n");
            strcpy(&espacioDirectorios[ptr], currItem);
            ptr += (strlen(currItem));
        }
        espacioDirectorios[ptr] = '\0';
    }

    closedir(dirP);
    return espacioDirectorios;
}

int main(int argc, char const *argv[]){
    char currDir[512]; 
    int i;
    int nArchivos = 0;

    getcwd(currDir, sizeof(currDir));
    char *strArchivos = leeDir(currDir);

    int tamArrArchivos = strlen(strArchivos);
    char *opcionesArchivos[99];
    char *currItem = (char *)calloc(99, sizeof(char));

    while(*strArchivos != '\0'){
        if(*strArchivos != '\n'){
            strcpy(currItem, strArchivos);
        }else{
            ++strArchivos;
            ++nArchivos;
        }
        //opcionesArchivos[nArchivos] = malloc(strlen(currItem)+1);
    }

    printf("%i\n", nArchivos);

    return 0;
}
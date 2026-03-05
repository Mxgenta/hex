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
    int nDirectorios = 0;
    
    if (dirP == NULL){
        printf("error al abrir directorio");
    }else{
        while ((d_dir = readdir(dirP))!=NULL)
        {
            //asignar memoria por nombre de archivo/directorio
            int tamDirectorio = sizeof(char) * (strlen(d_dir->d_name) + 1);
            ++nDirectorios;
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
    int tamPalabra = 0;

    //leer directorio actual
    getcwd(currDir, sizeof(currDir));
    char *strArchivos = leeDir(currDir);

    //revisar el string que regreso la funcion leeDir
    int tamArrArchivos = strlen(strArchivos);

    for(i=0;i<tamArrArchivos;i++){
        if(strArchivos[i] == '\n'){
            ++nArchivos;
        }
    }

    int tamanosDirectorios[nArchivos];

    int n=0, a=0;
    for(i=0;i<tamArrArchivos;i++){
        if(strArchivos[i] != '\n'){
            a++;
            tamanosDirectorios[n] = a;
        }else{
            ++n;
            a=0;
        }
    }
    char *opcionesArchivos[nArchivos];

    //asignar a opcionesArchivos
    char strt[99];
    for(int i = 0; i < nArchivos; i++){
        opcionesArchivos[i] = calloc(tamanosDirectorios[i], sizeof(char));
        for(i=0;i<tamArrArchivos;i++){
        if(strArchivos[i] != '\n'){
            a++;
            tamanosDirectorios[n] = a;
        }else{
            ++n;
            a=0;
        }
    }
    }


    for (int i = 0; i < nArchivos; i++)
        printf("%s\n", opcionesArchivos[i]);
    return 0;

    return 0;
}
//navegar entre archivos de un directorio
//y mostrar su contenido en hexadecimal

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

//hacer entorno grafico

//leer directorio
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
            strcpy(&espacioDirectorios[ptr], d_dir->d_name);
            ptr += strlen(d_dir->d_name);
            espacioDirectorios[ptr] = '\r';
        }
        espacioDirectorios[ptr] = '\0';
    }

    closedir(dirP);
    return espacioDirectorios;
}

//funciones del hex editor


int main(int argc, char const *argv[]){
    //inicializar pantalla con modo raw
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    
    char *opt_char[] = {
        "opcion1",
        "opcion2",
        "opcion3",
        (char *)NULL,
    };
    int c;

    //elementos del menu
    ITEM **opciones;
    MENU *menu;
    WINDOW *menu_window;

    //todo el rollo de hacer las opciones
    //todo: hacer algo que cuente cuantos elementos hay por directorio
    int n_opciones = 3;
    opciones = (ITEM **)calloc(n_opciones + 1, sizeof(ITEM *));
    for(int i = 0; i<n_opciones;i++){
        opciones[i] = new_item(opt_char[i], opt_char[i]);
    }
    opciones[n_opciones] = (ITEM *)NULL;

    //hacer un menu
	mvprintw(LINES - 2, 0, "F1 to Exit");
	post_menu(menu);
	refresh();

	while((c = getch()) != KEY_F(1))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
		}
	}	

	free_item(opciones[0]);
	free_item(opciones[1]);
	free_menu(menu);
	endwin();
    getch();

    endwin();
    
    return 0;
}

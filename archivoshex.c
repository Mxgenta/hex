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

//hacer entorno grafico
//leer directorio

int visorDirectorios(){
    clear();

    int c = getch();
	
    while (c != 24) { // Termina con CTRL-X
	    switch (c) {
		    case KEY_LEFT:
			    break;
	    }
	    c = getch();
    }

    return 0;
}

int main(int argc, char const *argv[]){
    //inicializar pantalla con modo raw
    initscr();
    raw();
    keypad(stdscr, TRUE);

    

    return 0;
}


//menu.cpp

#include <ncurses.h>
#include "menu.h"
#include "utils.h"
int mostrarMenu() {
    limpiarPantalla();
    printw("=== SOPA DE LETRAS ===\n");
    printw("1. Crear juego\n");
    printw("2. Configurar nivel\n");
    printw("3. Jugar\n");
    printw("4. Ver puntaje\n");
    printw("5. Salir\n");
    printw("Elige una opcion: \n");
    refresh();


    int opcion;
    
    scanf("%d", &opcion);

    return opcion;
}





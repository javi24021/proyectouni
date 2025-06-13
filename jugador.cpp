


#include <ncurses.h>
#include "jugador.h"
#include "utils.h"

void registrarJugador(Jugador& jugador) {
    limpiarPantalla();
    printw("Ingrese su nombre: ");
    char nombre[50];
    getstr(nombre);
    jugador.nombre = nombre;
    jugador.puntaje = 0;
    printw("Jugador registrado: %s\n", jugador.nombre.c_str());
    pausar();
}
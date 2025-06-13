


//utils.h
#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include "jugador.h"

void iniciarNcurses();
void limpiarPantalla();
void pausar();
void guardarPuntaje(Jugador& jugador);
void mostrarPuntaje(Jugador& jugador);

#endif
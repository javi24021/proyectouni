
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

typedef struct {
    std::string nombre;
    int puntaje;
} Jugador;

void registrarJugador(Jugador& jugador);

#endif



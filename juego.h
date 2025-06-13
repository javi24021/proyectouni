#ifndef JUEGO_H
#define JUEGO_H

#include <string>
#include "config.h"
#include "jugador.h"

typedef struct {
    std::string texto;
    int fila;
    int columna;
    std::string direccion;
    bool encontrada;
} Palabra;

typedef struct {
    char sopa[20][20];
    int filas;
    int columnas;
    Palabra palabra[20];
    int numPalabras;
} Juego;

void crearJuego(Juego &juego, Nivel nivel, int nivelElegido, std::string& nombreArchivo);
void cargarJuego(Juego &juego, std::string nombreArchivo);
void mostrarSopa(Juego juego);
void mostrarSopaTemporal(Juego juego, Palabra palabra, bool correcta); // Añadido
void Jugar(Juego &juego, Jugador &jugador);
bool validarPalabra(Juego juego, Palabra palabra);
void colocarPalabra(Juego &juego, Palabra palabra);

#endif
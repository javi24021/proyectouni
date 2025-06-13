#include "utils.h"
#include <fstream>

void iniciarNcurses() {
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    echo(); // Activa el eco para ver las entradas
    cbreak(); // Captura teclas inmediatamente
    curs_set(1); // Muestra el cursor
}

void limpiarPantalla() {
    clear();
    refresh();
}

void pausar() {
    getch();
    limpiarPantalla();
}

void guardarPuntaje(Jugador& jugador) {
    std::ofstream archivo("puntajes.txt", std::ios::app);
    if (archivo) {
        time_t ahora = time(0);
        tm* tiempo = localtime(&ahora);
        archivo << jugador.nombre << " " << tiempo->tm_mday << "/" << (tiempo->tm_mon + 1) << "/" << (tiempo->tm_year + 1900)
                << " " << jugador.puntaje << "\n";
        archivo.close();
    }
}
void mostrarPuntaje(Jugador& jugador) {
    limpiarPantalla();
    printw("Puntaje actual de %s: %d\n", jugador.nombre.c_str(), jugador.puntaje);
    printw("\nPuntajes guardados:\n");
    std::ifstream archivo("puntajes.txt");
    if (archivo) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            printw("%s\n", linea.c_str());
        }
        archivo.close();
    } else {
        printw("No hay puntajes guardados.\n");
    }
    pausar();
}
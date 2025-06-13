#include <ncurses.h>
#include <ctime>
#include "menu.h"
#include "jugador.h"
#include "juego.h"
#include "utils.h"

int main() {
    iniciarNcurses();
    Juego juego;
    Jugador jugador;
    int opcion;
    int nivelElegido = 0;

    do {
        opcion = mostrarMenu();
        switch (opcion) {
            case 1:
                limpiarPantalla();
                //MostrarEntrada(); // Asegúrate de que esté definido en menu.h
                printw("Elige nivel (1, 2 o 3): ");
                scanw("%d", &nivelElegido);
                if (nivelElegido < 1 || nivelElegido > 3) {
                    printw("Nivel inválido.\n");
                    pausar();
                    break;
                }
                {
                    std::string nombreArchivo;
                    crearJuego(juego, NIVELES[nivelElegido - 1], nivelElegido, nombreArchivo);
                    printw("Juego creado.\n");
                    pausar();
                }
                break;
            case 2:
                limpiarPantalla();
                //MostrarEntrada();
                printw("Elige nivel (1, 2 o 3): ");
                scanw("%d", &nivelElegido);
                if (nivelElegido < 1 || nivelElegido > 3) {
                    printw("Nivel inválido.\n");
                    pausar();
                    break;
                }
                printw("Nivel %d configurado.\n", nivelElegido);
                pausar();
                break;
            case 3:
                limpiarPantalla();
                if (nivelElegido == 0) {
                    printw("Configura un nivel primero.\n");
                    pausar();
                    break;
                }
                registrarJugador(jugador);
                {
                    std::string nombreArchivo = "sopa" + std::to_string(nivelElegido + 1) + ".dat";
                    cargarJuego(juego, nombreArchivo);
                }
                Jugar(juego, jugador);
                break;
            case 4:
                limpiarPantalla();
                mostrarPuntaje(jugador);
                break;
            case 5:
                printw("Saliendo...\n");
                pausar();
                break;
            default:
                printw("Opción incorrecta.\n");
                pausar();
                break;
        }
    } while (opcion != 5);

    endwin();
    return 0;
}

#include <fstream>
#include <string>
#include "juego.h"
#include "utils.h"

void crearJuego(Juego &juego, Nivel nivel, int nivelElegido, std::string& nombreArchivo) {
    iniciarNcurses();
    juego.filas = nivel.filas;
    juego.columnas = nivel.columnas;

    for (int i = 0; i < juego.filas; i++)
        for (int j = 0; j < juego.columnas; j++)
            juego.sopa[i][j] = ' ';

    printw("Ingrese el título del juego: ");
    char titulo[100];
    getstr(titulo);
    nombreArchivo = "sopa" + std::to_string(nivelElegido + 1) + ".dat";

    printw("Ingrese cantidad de palabras: ");
    scanw("%d", &juego.numPalabras);

    for (int p = 0; p < juego.numPalabras; p++) {
        limpiarPantalla();
        mostrarSopa(juego);
        printw("\nPalabra %d\nIngrese palabra: ", p + 1);
        char palabra[50];
        getstr(palabra);
        juego.palabra[p].texto = palabra;
        juego.palabra[p].encontrada = false;

        printw("Fila (0-%d): ", juego.filas - 1);
        scanw("%d", &juego.palabra[p].fila);
        printw("Columna (0-%d): ", juego.columnas - 1);
        scanw("%d", &juego.palabra[p].columna);
        printw("Dirección (H/V): ");
        char dir[2];
        getstr(dir);
        juego.palabra[p].direccion = dir;

        if (!validarPalabra(juego, juego.palabra[p])) {
            printw("Error: La palabra no cabe. Reintente.\n");
            pausar();
            p--;
            continue;
        }

        mostrarSopaTemporal(juego, juego.palabra[p], true); // Ahora declarada
        printw("\nConfirmar? (Enter): ");
        if (getch() == 10) {
            colocarPalabra(juego, juego.palabra[p]);
        } else {
            p--;
        }
    }

    printw("\nLlenar con letras? (*): ");
    if (getch() == '*') {
        for (int i = 0; i < juego.filas; i++)
            for (int j = 0; j < juego.columnas; j++)
                if (juego.sopa[i][j] == ' ')
                    juego.sopa[i][j] = 'A' + rand() % 26;
    }

    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        printw("Error al crear %s.\n", nombreArchivo.c_str());
        pausar();
        return;
    }
    archivo << juego.filas << " " << juego.columnas << "\n";
    for (int i = 0; i < juego.filas; i++) {
        for (int j = 0; j < juego.columnas; j++)
            archivo << juego.sopa[i][j] << " ";
        archivo << "\n";
    }
    archivo << juego.numPalabras << "\n";
    for (int p = 0; p < juego.numPalabras; p++)
        archivo << juego.palabra[p].texto << " " << juego.palabra[p].fila << " "
                << juego.palabra[p].columna << " " << juego.palabra[p].direccion << "\n";
    archivo.close();

    printw("\nJuego guardado en %s\n", nombreArchivo.c_str());
    pausar();
}

void cargarJuego(Juego &juego, std::string nombreArchivo) {
    iniciarNcurses();
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        printw("No se pudo abrir %s.\n", nombreArchivo.c_str());
        pausar();
        return;
    }

    archivo >> juego.filas >> juego.columnas;
    for (int i = 0; i < juego.filas; i++)
        for (int j = 0; j < juego.columnas; j++)
            archivo >> juego.sopa[i][j];

    archivo >> juego.numPalabras;
    for (int p = 0; p < juego.numPalabras; p++) {
        archivo >> juego.palabra[p].texto >> juego.palabra[p].fila
                >> juego.palabra[p].columna >> juego.palabra[p].direccion;
        juego.palabra[p].encontrada = false;
    }
    archivo.close();
}

void mostrarSopa(Juego juego) {
    limpiarPantalla();
    printw("Sopa de Letras\n\n");
    for (int j = 0; j < juego.columnas; j++) printw("%2d ", j);
    printw("\n");
    for (int i = 0; i < juego.filas; i++) {
        printw("%2d ", i);
        for (int j = 0; j < juego.columnas; j++) {
            bool esParte = false;
            for (int p = 0; p < juego.numPalabras; p++)
                if (juego.palabra[p].encontrada && ((juego.palabra[p].direccion == "H" &&
                    i == juego.palabra[p].fila && j >= juego.palabra[p].columna &&
                    j < juego.palabra[p].columna + juego.palabra[p].texto.size()) ||
                    (juego.palabra[p].direccion == "V" &&
                    j == juego.palabra[p].columna && i >= juego.palabra[p].fila &&
                    i < juego.palabra[p].fila + juego.palabra[p].texto.size())))
                    esParte = true;
            if (esParte) {
                attron(COLOR_PAIR(1));
                printw("%c ", juego.sopa[i][j]);
                attroff(COLOR_PAIR(1));
            } else {
                printw("%c ", juego.sopa[i][j]);
            }
        }
        printw("\n");
    }
    printw("\nPalabras: ");
    for (int p = 0; p < juego.numPalabras; p++)
        printw("%s%s", juego.palabra[p].encontrada ? "(Encontrada) " : "(Pendiente) ",
               juego.palabra[p].texto.c_str());
    printw("\n");
    refresh();
}

void mostrarSopaTemporal(Juego juego, Palabra palabra, bool correcta) {
    limpiarPantalla();
    printw("Sopa de Letras (Vista previa)\n\n");
    for (int j = 0; j < juego.columnas; j++) printw("%2d ", j);
    printw("\n");
    for (int i = 0; i < juego.filas; i++) {
        printw("%2d ", i);
        for (int j = 0; j < juego.columnas; j++) {
            bool esParte = false;
            if (palabra.direccion == "H" && i == palabra.fila && j >= palabra.columna &&
                j < palabra.columna + palabra.texto.size())
                esParte = true;
            else if (palabra.direccion == "V" && j == palabra.columna && i >= palabra.fila &&
                     i < palabra.fila + palabra.texto.size())
                esParte = true;
            if (esParte) {
                attron(COLOR_PAIR(correcta ? 1 : 2));
                printw("%c ", juego.sopa[i][j]);
                attroff(COLOR_PAIR(correcta ? 1 : 2));
            } else {
                printw("%c ", juego.sopa[i][j]);
            }
        }
        printw("\n");
    }
    printw("\nPalabras confirmadas: ");
    for (int p = 0; p < juego.numPalabras; p++)
        printw("%s%s", juego.palabra[p].encontrada ? "(OK) " : "(X) ",
               juego.palabra[p].texto.c_str());
    printw("\n");
    refresh();
}

void colocarPalabra(Juego &juego, Palabra palabra) {
    for (size_t i = 0; i < palabra.texto.size(); i++) {
        int fila = palabra.fila, col = palabra.columna;
        if (palabra.direccion == "H") col += i;
        else if (palabra.direccion == "V") fila += i;
        if (fila < juego.filas && col < juego.columnas)
            juego.sopa[fila][col] = palabra.texto[i];
    }
}

void Jugar(Juego& juego, Jugador& jugador) {
    iniciarNcurses();
    int restantes = juego.numPalabras;
    time_t inicio = time(0);

    while (restantes > 0) {
        mostrarSopa(juego);
        printw("Ingrese palabra: ");
        char palabra[50];
        getstr(palabra);
        std::string palabraStr(palabra);

        printw("Ingrese fila (0-%d): ", juego.filas - 1);
        int fila;
        scanw("%d", &fila);

        printw("Ingrese columna (0-%d): ", juego.columnas - 1);
        int col;
        scanw("%d", &col);

        printw("Ingrese dirección (H/V): ");
        char dir[2];
        getstr(dir);
        std::string dirStr(dir);

        // Validar
        if (fila < 0 || fila >= juego.filas || col < 0 || col >= juego.columnas || 
            (dirStr != "H" && dirStr != "V")) {
            printw("Posición o dirección inválida.\n");
            pausar();
            continue;
        }

        bool encontrada = false;
        for (int p = 0; p < juego.numPalabras; p++) {
            if (!juego.palabra[p].encontrada && juego.palabra[p].texto == palabraStr &&
                juego.palabra[p].fila == fila && juego.palabra[p].columna == col &&
                juego.palabra[p].direccion == dirStr) {
                juego.palabra[p].encontrada = true;
                restantes--;
                encontrada = true;
                break;
            }
        }
        if (!encontrada) {
            attron(COLOR_PAIR(2));
            printw("Incorrecta.\n");
            attroff(COLOR_PAIR(2));
            pausar();
        }
    }

    time_t fin = time(0);
    jugador.puntaje = (juego.numPalabras * 100) / (difftime(fin, inicio) + 1);
    printw("\n Tu puntaje %d\n", jugador.puntaje);
    guardarPuntaje(jugador);
}

bool validarPalabra(Juego juego, Palabra palabra) {
    for (size_t i = 0; i < palabra.texto.size(); i++) {
        int fila = palabra.fila, col = palabra.columna;
        if (palabra.direccion == "H") col += i;
        else fila += i;
        if (fila >= juego.filas || col >= juego.columnas) return false;
        if (juego.sopa[fila][col] != ' ' && juego.sopa[fila][col] != palabra.texto[i]) return false;
    }
    return true;
}


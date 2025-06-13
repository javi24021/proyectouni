

// config.h


#ifndef CONFIG_H
#define CONFIG_H
#include <string>

extern int MAX_FILAS;
extern int MAX_COLUMNAS;

typedef struct {
    int filas;
    int columnas;
} Nivel;
extern Nivel NIVELES[3];
#endif

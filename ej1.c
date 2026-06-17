#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { [cite: 46]
    void* dirrecion; [cite: 47]
    size_t bytes; [cite: 48]
    char archivo[100]; [cite: 49]
} bloqueMemoria; [cite: 50]

bloqueMemoria* crearBloqueMemoria(size_t bytes, const char* archivo) { [cite: 51]
    bloqueMemoria* bloque = (bloqueMemoria*)malloc(sizeof(bloqueMemoria)); [cite: 52]
    if (bloque == NULL) { [cite: 53]
        return NULL; [cite: 54]
    } [cite: 55]
    bloque->dirrecion = malloc(bytes); [cite: 56]
    if (bloque->dirrecion == NULL) { [cite: 57]
        free(bloque); [cite: 58]
        return NULL; [cite: 59]
    } [cite: 60]
    bloque->bytes = bytes; [cite: 61]
    strncpy(bloque->archivo, archivo, sizeof(bloque->archivo) - 1); [cite: 62]
    bloque->archivo[sizeof(bloque->archivo) - 1] = '\0'; [cite: 63]
    return bloque; [cite: 64]
}
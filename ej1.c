#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
    int id;
    char nickname[30];
    int edad;
    char pais[30];
} usuario;

typedef struct {
    void* direccion;
    size_t bytes;
    char archivo[100];
    int línea;
} BloqueMemoria;

BloqueMemoria registro[100];


 malloc(size) mi_malloc(size, __FILE__, __LINE__)
 free(ptr) mi_free(ptr, __FILE__, __LINE__)
void* mi_malloc(size_t size, const char* archivo, int línea) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error al asignar memoria en %s:%d\n", archivo, línea);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

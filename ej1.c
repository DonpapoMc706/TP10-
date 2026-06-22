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
int totalBloques = 0;

void *mi_malloc(size_t bytes, const char *archivo, int línea) {
      void *ptr = malloc(bytes);
        if (ptr != NULL) {
            for (int i = 0; i < 100; i++) {
                if (registro[i].direccion == NULL) {
                    registro[i].direccion = ptr;
                    registro[i].bytes = bytes;
                    strncpy(registro[i].archivo, archivo, sizeof(registro[i].archivo) - 1);
                    registro[i].archivo[sizeof(registro[i].archivo) - 1] = '\0';
                    registro[i].línea = línea;
                    totalBloques++;
                    break;
        
                }
            }
        }
    return ptr;
    } 
#define malloc(x) mi_malloc(x, __FILE__, __LINE__)
#define free(x) mi_free(x, __FILE__, __LINE__)
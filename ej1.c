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
         {
            registro[totalBloques].direccion = ptr; {
                if (registro[totalBloques].direccion == NULL) {
                    registro[totalBloques].direccion = ptr;
                    registro[totalBloques].bytes = bytes;
                    strncpy(registro[totalBloques].archivo, archivo, sizeof(registro[totalBloques].archivo) - 1);
                    registro[totalBloques].archivo[sizeof(registro[totalBloques].archivo) - 1] = '\0';
                    registro[totalBloques].línea = línea;
                    totalBloques++; 
                }
            }
        }
    return ptr;
    } 
    void mi_free(void* ptr, const char* archivo, int línea) {
        free(ptr);
        for (int i = 0; i < totalBloques; i++) {
            if (registro[i].direccion == ptr) {
                for (int j = i; j < totalBloques - 1; j++) {
                    registro[j] = registro[j + 1];
                }
                totalBloques--;
                break;
            }
    
    
}
#define malloc(x) mi_malloc(x, __FILE__, __LINE__)
#define free(x) mi_free(x, __FILE__, __LINE__)
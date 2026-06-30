#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
                    registro[totalBloques].direccion = ptr;
                    registro[totalBloques].bytes = bytes;
                    strncpy(registro[totalBloques].archivo, archivo, sizeof(registro[totalBloques].archivo) - 1);
                    registro[totalBloques].archivo[sizeof(registro[totalBloques].archivo) - 1] = '\0';
                    registro[totalBloques].línea = línea;
                    totalBloques++; 
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
    }
    void mostrarMemoriaReservada() {
        printf("=====BLOQUES ACTIVOS=====\n");
        for (int i = 0; i < totalBloques; i++) {
            printf("Direccín: %p, Bytes: %zu, Archivo: %s, Línea: %d\n",
                     registro[i].direccion,
                     registro[i].bytes,
                     registro[i].archivo,
                     registro[i].línea);
        }
       int() altaUsuario(usuario lista, int* cantidad, int maxUsuarios) {
            if (*cantidad >= maxUsuarios) {
                printf("No se pueden agregar mas usuarios. Se ha alcanzado el límite máximo.\n");
                return 0;
            }
        }
        usuario*nuevoUsuario = (usuario*)malloc(sizeof(usuario));
        if (nuevoUsuario == NULL) {
            printf("Error al reservar memoria para el nuevo usuario.\n");
            return 0;
        }
        printf("Ingrese el ID del usuario: ");
        scanf("%d", &nuevoUsuario->id);
        do {
            printf("El nickname no puede estar vacío o comenzar con un número. Ingrese el nickname del usuario: ");
            scanf("%s", nuevoUsuario->nickname);
          }  while (strlen(nuevoUsuario->nickname) == 0 || isdigit(nuevoUsuario->nickname[0]))
        
        do {
            printf("La edad debe estar entre 5 y 100. Ingrese la edad del usuario: ");
            scanf("%d", &nuevoUsuario->edad);
         } while (nuevoUsuario->edad < 5 || nuevoUsuario->edad > 100);
        printf("Ingrese el país del usuario: ");
        scanf("%s", nuevoUsuario->pais);

        return 1;
    }
#define malloc(x) mi_malloc(x, __FILE__, __LINE__)
#define free(x) mi_free(x, __FILE__, __LINE__)

int main() {
    int maxUsuarios = 5;
    int cantidad =0;
    usuario* listaUsuarios[5];

    printf("---sistema de registros ----");
    altaUsuario(listaUsuarios, &cantidad, maxUsuarios);
    printf("reservando memoria");
    mostrarMemoriaReservada();
    if (cantidad > 0) {
        free(listaUsuarios[0]);
    }
   return 0;
}
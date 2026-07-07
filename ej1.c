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
    int linea;
} BloqueMemoria;

BloqueMemoria registro[100];
int totalBloques = 0;

void *mi_malloc(size_t bytes, const char *archivo, int linea) {
    void *ptr = malloc(bytes);
    if (ptr != NULL) {
        registro[totalBloques].direccion = ptr;
        registro[totalBloques].bytes = bytes;
        strncpy(registro[totalBloques].archivo, archivo, sizeof(registro[totalBloques].archivo) - 1);
        registro[totalBloques].archivo[sizeof(registro[totalBloques].archivo) - 1] = '\0';
        registro[totalBloques].linea = linea;
        totalBloques++; 
    }
    return ptr;
} 

void mi_free(void* ptr, const char* archivo, int linea) {
    if (ptr == NULL) return;
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
        printf("Direccion: %p, Bytes: %zu, Archivo: %s, Linea: %d\n",
                 registro[i].direccion,
                 registro[i].bytes,
                 registro[i].archivo,
                 registro[i].linea);
    }
}

#define malloc(x) mi_malloc(x, __FILE__, __LINE__)
#define free(x) mi_free(x, __FILE__, __LINE__)

int altaUsuario(usuario** lista, int* cantidad, int maxUsuarios) {
    usuario* nuevoUsuario = (usuario*)malloc(sizeof(usuario));
    if (nuevoUsuario == NULL) {
        printf("Error al reservar memoria para el nuevo usuario.\n");
        return 0;
    }
    
    printf("Ingrese el ID del usuario: ");
    scanf("%d", &nuevoUsuario->id);

    int valido = 0;
    do {
        valido = 1;
        printf("El nickname no puede estar vacio o comenzar con un numero. Ingrese el nickname del usuario: ");
        scanf("%s", nuevoUsuario->nickname);
    } while (strlen(nuevoUsuario->nickname) == 0 || isdigit(nuevoUsuario->nickname[0]));

    do {
        printf("La edad debe estar entre 5 y 100. Ingrese la edad del usuario: ");
        scanf("%d", &nuevoUsuario->edad);
    } while (nuevoUsuario->edad < 5 || nuevoUsuario->edad > 100);

    printf("Ingrese el pais del usuario: ");
    scanf("%s", nuevoUsuario->pais);

    lista[*cantidad] = nuevoUsuario;
    (*cantidad)++;

    return 1;
}

int bajaUsuario(usuario** lista, int* cantidad, int id) {
    for (int i = 0; i < *cantidad; i++) {
        if (lista[i]->id == id) {
            free(lista[i]);
            for (int j = i; j < *cantidad - 1; j++) {
                lista[j] = lista[j + 1];
            }
            (*cantidad)--;
            return 1;
        }
    }
    return 0;
}

int main() {
    int maxUsuarios = 5;
    int cantidad = 0;
    int opcion = 0;

    usuario** listaUsuarios = (usuario**)malloc(maxUsuarios * sizeof(usuario*));
    
    do {
        printf("\n1. Alta de usuario\n");
        printf("2. Mostrar memoria reservada\n");
        printf("3. Baja de usuario\n");
        printf("4. Mostrar usuarios\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad == maxUsuarios) {
                    maxUsuarios += 5;
                    void* vieja_direccion = listaUsuarios;
                    listaUsuarios = (usuario**)realloc(listaUsuarios, maxUsuarios * sizeof(usuario*));
                    
                    for (int i = 0; i < totalBloques; i++) {
                        if (registro[i].direccion == vieja_direccion) {
                            registro[i].direccion = listaUsuarios;
                            registro[i].bytes = maxUsuarios * sizeof(usuario*);
                            break;
                        }
                    }
                    printf("\n[SISTEMA] Capacidad de usuarios aumentada a %d.\n", maxUsuarios);
                }

                if (altaUsuario(listaUsuarios, &cantidad, maxUsuarios)) {
                    printf("Usuario agregado exitosamente. Total de usuarios: %d\n", cantidad);
                } else {
                    printf("Error al agregar usuario.\n");
                }
                break;
                
            case 2:
                mostrarMemoriaReservada();
                break;
                
            case 3:
                if (cantidad > 0) {
                    int id;
                    printf("Ingrese el ID del usuario a eliminar: ");
                    scanf("%d", &id);
                    if (bajaUsuario(listaUsuarios, &cantidad, id)) {
                        printf("Usuario eliminado exitosamente.\n");
                    } else {
                        printf("No se pudo eliminar el usuario. ID no encontrado.\n");
                    }
                } else {
                    printf("No hay usuarios registrados para eliminar.\n");
                }
                break;

            case 4:
                if (cantidad == 0) {
                    printf("No hay usuarios registrados. \n");
                } else {
                    printf("=====USUARIOS REGISTRADOS=====\n");
                    for (int i = 0; i < cantidad; i++) {
                        printf("ID: %d, Nickname: %s, Edad: %d, Pais: %s\n",
                               listaUsuarios[i]->id,
                               listaUsuarios[i]->nickname,
                               listaUsuarios[i]->edad,
                               listaUsuarios[i]->pais);
                    }
                } 
                break;
                
            case 5:
                printf("Saliendo del programa.\n");
                break;
                
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        } 
        
    } while (opcion != 5);   
    
    printf("\nLiberando memoria de usuarios restantes...\n");
    for (int i = 0; i < cantidad; i++) {
        free(listaUsuarios[i]);
    }
    
    free(listaUsuarios);
    mostrarMemoriaReservada();
    
    return 0;
}
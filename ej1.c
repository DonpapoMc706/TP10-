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
        }
       int altaUsuario(usuario** lista, int* cantidad, int maxUsuarios) {
            if (*cantidad >= maxUsuarios) {
                printf("No se pueden agregar mas usuarios. Se ha alcanzado el límite máximo.\n");
                return 0;
            }
        usuario*nuevoUsuario = (usuario*)malloc(sizeof(usuario));
        if (nuevoUsuario == NULL) {
            printf("Error al reservar memoria para el nuevo usuario.\n");
            return 0;
        }
        printf("Ingrese el ID del usuario: ");
        scanf("%d", &nuevoUsuario->id);

        int valido = 0;
        do {
            valido = 1;
            printf("El nickname no puede estar vacío o comenzar con un número. Ingrese el nickname del usuario: ");
            scanf("%s", nuevoUsuario->nickname);
          }  while (strlen(nuevoUsuario->nickname) == 0 || isdigit(nuevoUsuario->nickname[0]));

        do {
            printf("La edad debe estar entre 5 y 100. Ingrese la edad del usuario: ");
            scanf("%d", &nuevoUsuario->edad);
         } while (nuevoUsuario->edad < 5 || nuevoUsuario->edad > 100);

        printf("Ingrese el país del usuario: ");
        scanf("%s", nuevoUsuario->pais);

        lista[*cantidad] = nuevoUsuario;
        (*cantidad)++;

        return 1;
    }
#define malloc(x) mi_malloc(x, __FILE__, __LINE__)
#define free(x) mi_free(x, __FILE__, __LINE__)

int main() {
    int maxUsuarios = 5;
    int cantidad =0;
    int opcion = 0;
    usuario* listaUsuarios[5];
    
    do {
        printf("1. Alta de usuario\n");
        printf("2. Mostrar memoria reservada\n");
        printf("3. Baja de usuario\n");
        printf("4. Mostrar usuarios\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (altaUsuario(listaUsuarios, &cantidad, maxUsuarios)) {
                    printf("Usuario agregado exitosamente.\n");
                } else { 
                    printf("No se pudo agregar el usuario.\n");
                }
                 break;
                 case 2:
                mostrarMemoriaReservada();
                break;
                case 3:
                if (cantidad > 0) {
                    int idBaja;
                    printf("Ingrese el ID del usuario a dar de baja: ");
                    scanf("%d", &idBaja);
                    int encontrado = 0;
                    for (int i = 0; i < cantidad; i++) {
                        if (listaUsuarios[i]->id == idBaja) {
                            free(listaUsuarios[i]);
                            for (int j = i; j < cantidad - 1; j++) {
                                listaUsuarios[j] = listaUsuarios[j + 1];
                            }
                            cantidad--;
                            encontrado = 1;
                            printf("Usuario con ID %d dado de baja exitosamente.\n", idBaja);
                        }
                    }
                }
            
                            break;
                            case 4:
                            if (cantidad == 0) {
                                printf("No hay usuarios registrados. \n");
                            } else {
                                printf("=====USUARIOS REGISTRADOS=====\n");
                                for (int i = 0; i < cantidad; i++) {
                                    printf("ID: %d, Nickname: %s, Edad: %d, País: %s\n",
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
                                    printf("Opciíon inválida. Intente nuevamente.\n");
                                    break;
                            } 
                                    
                                }
                                }while (opcion != 5);   
                                
                    
return 0;
}
                       
        
    
// Autores: Sergio Orjuela 9040203

#include "tablaHash.h"
#include "articulo.h"
#include <cstdio>
#include <cstring>

int main() {
    TablaHash<Articulo> inventario;
    char comando[21]{}, nombre[31]{};
    int  n_entradas{}, codigo{}, cantidad{};
    scanf("%d", &n_entradas);

    for(int i{}; i < n_entradas; i++){
        scanf("%20s", comando);

        if(strcmp(comando, "AGREGAR") == 0) {
            scanf("%d %30s %d", &codigo, nombre, &cantidad);
            if (inventario.consultar(codigo)) { printf("repetido\n"); }
            else{
                inventario.insertar(codigo, Articulo(codigo,nombre,cantidad));
                printf("ok\n");
            }
        }
        else if(strcmp(comando, "ELIMINAR") == 0) {
            scanf("%d", &codigo);

            if(inventario.eliminar(codigo)) {
                printf("ok\n");
            }
            else { printf("no existe\n"); }
        }
        else if(strcmp(comando, "CONSULTAR") == 0) {
            scanf("%d", &codigo);
            Registro<Articulo>* objetivo{ inventario.consultar(codigo) };

            if(objetivo) { objetivo->valor.listar(); }
            else { printf("no existe\n"); }
        }
        else if(strcmp(comando, "REPONER") == 0) {
            scanf("%d %d", &codigo, &cantidad);
            Registro<Articulo>* objetivo{ inventario.consultar(codigo) };

            if (objetivo) {
                objetivo->valor.reponer(cantidad);
                printf("ok\n");
            } else {
                printf("no existe\n");
            }
        }
        else if(strcmp(comando, "LISTAR") == 0) {
            if (!inventario.vacia()){
                inventario.listar();
            }    
        }
    }

    return 0;
}

// Autores: Sergio Orjuela 9040203, Joseph Salazar 9038594, Juan Jose Franco 9035048

#include "listaEnlazadaSimple.h"
#include "articulo.h"
#include <cstdio>
#include <cstring>

int obtener_codigo(const Articulo& articulo) {
    return articulo.getCodigo();
}

int main() {
    Lista<Articulo> inventario;
    char comando[21]{}, nombre[31]{};
    int  n_entradas{}, codigo{}, cantidad{};
    scanf("%d", &n_entradas);

    for(int i{}; i < n_entradas; i++){
        scanf("%20s", comando);

        if(strcmp(comando, "AGREGAR") == 0) {
            scanf("%d %30s %d", &codigo, nombre, &cantidad);

            if (inventario.consultar(obtener_codigo, codigo)) { printf("repetido\n"); }
            else {
                inventario.agregar(Articulo(codigo,nombre,cantidad));
                printf("ok\n");
            }
        }
        else if(strcmp(comando, "ELIMINAR") == 0) {
            int pos{};
            scanf("%d", &codigo);

            if(inventario.consultar(obtener_codigo, codigo, &pos)) {
                inventario.eliminar(pos);
                printf("ok\n");
            }
            else { printf("no existe\n"); }
        }
        else if(strcmp(comando, "CONSULTAR") == 0) {
            scanf("%d", &codigo);
            Nodo<Articulo>* objetivo{ inventario.consultar(obtener_codigo, codigo) };

            if(objetivo) { objetivo->dato.listar(); }
            else { printf("no existe\n"); }
        }
        else if(strcmp(comando, "REPONER") == 0) {
            scanf("%d %d", &codigo, &cantidad);
            Nodo<Articulo>* objetivo{ inventario.consultar(obtener_codigo, codigo) };

            if (objetivo) {
                objetivo->dato.reponer(cantidad);
                printf("ok\n");
            } else {
                printf("no existe\n");
            }
        }
        else if(strcmp(comando, "LISTAR") == 0) {
            if(!inventario.vacia()) {
                Nodo<Articulo>* actual{ inventario.nodo_en(0) }; // Vamos a recorrer toda la lista partiendo del nodo cabeza hasta n
                for (int j{}; j < inventario.tamano(); j++) {
                    actual->dato.listar();
                    actual = actual->siguiente;
                }
            }
        }
    }

    return 0;
}

// Autores: Sergio Orjuela 9040203, Joseph Salazar 9038594, Juan Jose Franco 9035048

#include "listaEnlazadaSimple.h"
#include <cstdio>
#include <cstring>
#include "articulo.h"

int obtener_codigo(const Articulo& a) {
    return a.getCodigo();
}

int main() {
    Lista<Articulo> inventario;
    char comando[20]{}, nombre[30]{};
    int  n_entradas{}, codigo{}, cantidad{};
    scanf("%d", &n_entradas);

    for(int i{}; i < n_entradas; i++){
        scanf("%19s", comando);
        if(strcmp(comando, "AGREGAR") == 0) { // AGREGAR
            scanf("%d %s %d", &codigo, nombre, &cantidad);
            if (inventario.consultar(obtener_codigo, codigo)) {
                printf("repetido\n");
            } else {
                inventario.agregar(Articulo(codigo,nombre,cantidad));
                printf("ok\n");
            }
        }
        else if(strcmp(comando, "ELIMINAR") == 0) { // ELIMINAR
            int pos{};
            scanf("%d", &codigo);

            if (inventario.consultar(obtener_codigo, codigo, pos)) {
                inventario.eliminar(pos);
                printf("ok\n");
            } else {
                printf("no existe\n");
            }
        }
        else if(strcmp(comando, "CONSULTAR") == 0) { // CONSULTAR
            Nodo<Articulo>* nodo_obj{};
            scanf("%d", &codigo);

            if (inventario.consultar(obtener_codigo, codigo, nodo_obj)) {
                nodo_obj->dato.listar();
            } else {
            printf("no existe\n");
            }
        }
        else if(strcmp(comando, "REPONER") == 0) { // REPONER
            int cantidad{};
            Nodo<Articulo>* nodo_obj{};
            scanf("%d %d", &codigo, &cantidad);

            if (inventario.consultar(obtener_codigo, codigo, nodo_obj)) {
                nodo_obj->dato.reponer(cantidad);
                printf("ok\n");
            } else {
            printf("no existe\n");
            }
        }
        else if(strcmp(comando, "LISTAR") == 0) { // LISTAR
            if(!inventario.vacia()) {
                Nodo<Articulo>* actual = inventario.nodo_en(0); // Vamos a recorrer toda la lista partiendo del nodo cabeza hasta n
                for (int j{}; j<inventario.tamano(); j++) {
                    actual->dato.listar();
                    actual = actual->siguiente;
                }
            }
        }
    }

    return 0;
}

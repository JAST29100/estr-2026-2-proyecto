// Autores: Sergio Orjuela 9040203, Joseph Salazar 9038594, Juan Jose Franco 9035048

#include "listaEnlazadaSimple.h"
#include <cstdio>
#include "articulo.h"
int main() {
  Lista<Articulo> inventario;
  int  n_entradas{}, codigo{}, cantidad{};
  char comando{}, nombre[30];
  scanf("%d", &n_entradas);
  for(int i{}; i<n_entradas; i++){
    scanf(" %c", &comando);
    while (getchar() != ' ' && getchar() != '\n');
    switch (comando) {
        case 'A':
            scanf("%d %s %d", &codigo, nombre, &cantidad);
            inventario.agregar(Articulo(codigo,nombre,cantidad));
            printf("ok\n");
            break;
        case 'E':
        {
            int pos{};
            scanf("%d", &codigo);
            if (inventario.consultar([](const Articulo& a) { return a.getCodigo(); }, codigo, pos)) {
                inventario.eliminar(pos);
                printf("ok\n");
            } else {
                printf("no existe\n");
            }
        }
            break;
        case 'C':
        {
            Nodo<Articulo>* nodo_obj{};
            scanf("%d", &codigo);
            if (inventario.consultar([](const Articulo& a) { return a.getCodigo(); }, codigo, nodo_obj)) {
                nodo_obj->dato.listar();
            } else {
            printf("no existe\n");
            }
            break;
        }
        case 'R':
        {
            int cantidad{};
            Nodo<Articulo>* nodo_obj{};
            scanf("%d %d", &codigo, &cantidad);
            if (inventario.consultar([](const Articulo& a) { return a.getCodigo(); }, codigo, nodo_obj)) {
                nodo_obj->dato.reponer(cantidad);
                printf("ok\n");
            }else {
            printf("no existe\n");
            }

        }
            break;
        case 'L':
            Nodo<Articulo>* actual = inventario.nodo_en(0); // Vamos a recorrer toda la lista partiendo del nodo cabeza hasta n
            for (int j{}; j<inventario.tamano(); j++) {
                actual->dato.listar();
                actual = actual->siguiente;
            }
            break;
    }
  }
  return 0;
}

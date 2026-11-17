// Autores: Sergio Orjuela 9040203 Joseph Salazar 9038594 Juan Franco 9035048

#include "articulo.h"
#include <cstdio>
#include <cstring>
#include <map>

int main() {
    std::map<int, Articulo> inventario;
    char comando[21]{}, nombre[31]{};
    int n_entradas{}, codigo{}, cantidad{};
    scanf("%d", &n_entradas);

    for(int i{}; i < n_entradas; i++){
        scanf("%20s", comando);

        if(strcmp(comando, "AGREGAR") == 0) {
            scanf("%d %30s %d", &codigo, nombre, &cantidad);
            if (inventario.count(codigo)) { printf("repetido\n"); }
            else{
                inventario.insert({codigo, Articulo(codigo,nombre,cantidad)});
                printf("ok\n");
            }
        }
        else if(strcmp(comando, "ELIMINAR") == 0) {
            scanf("%d", &codigo);

            if(inventario.erase(codigo)) {
                printf("ok\n");
            }
            else { printf("no existe\n"); }
        }
        else if(strcmp(comando, "CONSULTAR") == 0) {
            scanf("%d", &codigo);
            std::map<int, Articulo>::iterator objetivo{ inventario.find(codigo) };

            if(objetivo != inventario.end()) { objetivo->second.listar(); }
            else { printf("no existe\n"); }
        }
        else if(strcmp(comando, "REPONER") == 0) {
            scanf("%d %d", &codigo, &cantidad);
            std::map<int, Articulo>::iterator objetivo{ inventario.find(codigo) };

            if (objetivo != inventario.end()) {
                objetivo->second.reponer(cantidad);
                printf("ok\n");
            } else {
                printf("no existe\n");
            }
        }
        else if(strcmp(comando, "LISTAR") == 0) {
            for(const auto& a : inventario){
                a.second.listar();
            }
        }
    }

    return 0;
}

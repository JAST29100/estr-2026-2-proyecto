// Autores: Sergio Orjuela 9040203, Joseph Salazar 9038594, Juan Jose Franco 9035048

#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>
#include <cstdio>
#include <cassert>

class Articulo{
    int codigo{};
    std::string nombre{};
    int cantidad{};

    public:
    Articulo(int codigo, std::string nombre, int cantidad): codigo{codigo},
        nombre{nombre}, cantidad{cantidad} {}

    int getCodigo() const {
        return this->codigo;
    }
    // Devolvemos por referencia el tipo string, el primer const evita modificarlo de forma externa
    // El segundo const garantiza que el método no lo toca, y con ambos se preserva encapsulamiento
    const std::string& getNombre() const {
        return this->nombre;
    }
    int getCantidad() const {
        return this->cantidad;
    }

    void reponer(int reposicion) { cantidad += reposicion; }
    void listar() const { printf("%d %s %d\n", this->codigo, this->nombre.c_str(), this->cantidad); }
};

#endif

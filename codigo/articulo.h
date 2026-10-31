#ifndef ARTICULO_H
#define ARTICULO_H

#include <string>
#include <cstdio>
#include <cassert>

class Articulo{
    private:
        int codigo;
        std::string nombre;
        int cantidad;

    public:
        // Garantizamos codigo positivo, nombre valido y cantidad no negativa antes de inicializar
        Articulo(int codigo, std::string nombre, int cantidad){
            assert(codigo > 0);
            assert(!nombre.empty());
            assert(cantidad >= 0);

            this->codigo = codigo;
            this->nombre = nombre;
            this->cantidad = cantidad;
        }
        int getCodigo() const{
            return this->codigo;
        }
        // Devolvemos por referencia el tipo string, el primer const evita modificarlo de forma externa
        // El segundo const garantiza que el método no lo toca, y con ambos se preserva encapsulamiento
        const std::string &getNombre() const{
            return this->nombre;
        }
        int getCantidad() const{
            return this->cantidad;
        }
        void reponer(int reposicion){ // Garantizamos reposicion positiva antes de reponer
            assert(reposicion > 0);
            cantidad += reposicion;
        }
        void listar() const{
            printf("%d %s %d\n", this->codigo, this->nombre.c_str(), this->cantidad);
        }
};

#endif

// Autores: Joseph Salazar 9038594

#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include "listaEnlazadaSimple.h"
#include <cassert>

template <typename Valor>
struct Registro {
    int llave{};
    Valor valor{};

    Registro() {}
    Registro(int l, Valor v): llave{l}, valor{v} {}
};

template <typename Valor>
int obtenerLlave(const Registro<Valor>& r) {
    return r.llave;
}

template <typename Valor>
class TablaHash {
private:
    Lista<Registro<Valor>> *casillas{};
    int m{};
    int n{};

    int h(int clave) const {
        return clave % m;
    }
    Nodo<Registro<Valor>>* buscarNodo(int clave) {
        int posicion {h(clave)};

        return casillas[posicion].consultar(obtenerLlave, clave);
    }

public:
    TablaHash(int tam): casillas{nullptr}, m{tam} {
        assert(tam > 0);

        casillas = new Lista<Registro<Valor>>[m];
    }
    ~TablaHash() {
        delete[] casillas;
    }

    void insertar(int clave, Valor valor) {
        assert(clave >= 0);

        Nodo<Registro<Valor>> *encontrado{buscarNodo(clave)};

        if(encontrado) { encontrado->dato.valor = valor; }
        else {
            int posicion {h(clave)};
            Registro<Valor> nuevo {clave, valor};
            casillas[posicion].agregar(nuevo);
            n++;
        }
    }
    // Devuelve un ptr al registro si existe, si no devuelve nullptr
    Registro<Valor> *buscar(int clave) {
        assert(clave >= 0);

        Nodo<Registro<Valor>> *encontrado {buscarNodo(clave)};
        Registro<Valor> *res{};

        if(encontrado) { res = &encontrado->dato; }

        return res;
    }
    void eliminar(int clave) {
        assert(clave >= 0);

        int posicion {h(clave)};
        int indice{};

        casillas[posicion].consultar(obtenerLlave, clave, &indice);

        if(indice != -1) {
            casillas[posicion].eliminar(indice);
            n--;
        }
    }
};

#endif // TABLA_HASH_H

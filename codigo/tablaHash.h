// Autores: Joseph Salazar 9038594

#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include "listaEnlazadaSimple.h"
#include <cassert>

// Registro es una pareja de Llave y Valor.
template <typename Valor>
struct Registro {
    int llave{};
    Valor valor{};

    Registro() {}
    Registro(int l, Valor v): llave{l}, valor{v} {}
};

// Devuelve la llave de un registro.
template <typename Valor>
int obtenerLlave(const Registro<Valor>& r) {
    return r.llave;
}

// Devuelve el primo estrictamente mayor mas cercano al num.
inline int siguientePrimo(int num) {
    int siguiente{num+1};
    if(siguiente > 2 && siguiente % 2 == 0) { siguiente++; }

    while(true) {
        bool es_primo{siguiente >= 2};
        for(int i{3}; i <= siguiente / i && es_primo; i += 2) {
            if(siguiente % i == 0) { es_primo = false; }
        }

        if(es_primo) { return siguiente; }
        siguiente += 2;
    }
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
    Nodo<Registro<Valor>>* buscarNodo(int clave) const {
        int posicion {h(clave)};

        return casillas[posicion].consultar(obtenerLlave, clave);
    }

public:
    TablaHash(int tam = 7): casillas{nullptr}, m{tam}, n{} {
        assert(tam > 0);

        casillas = new Lista<Registro<Valor>>[m];
    }
    ~TablaHash() {
        delete[] casillas;
    }

    void rehash(int tam) {
        assert(tam > n); // Garantizamos que se mantenga el factor de carga de 1.

        Lista<Registro<Valor>> *n_casillas {new Lista<Registro<Valor>>[tam]};
        for(int i{}; i < m; i++) {
            Nodo<Registro<Valor>> *actual{casillas[i].nodo_en(0)};

            while(actual) {
                int posicion{actual->dato.llave % tam};
                n_casillas[posicion].agregar(actual->dato);
                actual = actual->siguiente;
            }
        }

        delete[] casillas;
        casillas = n_casillas;
        m = tam;
    }

    Registro<Valor> *buscar(int clave) {
        assert(clave >= 0);

        Nodo<Registro<Valor>> *encontrado {buscarNodo(clave)};
        Registro<Valor> *res{};

        if(encontrado) { res = &encontrado->dato; }

        return res;
    }
    void insertar(int clave, Valor valor) {
        assert(clave >= 0);

        Nodo<Registro<Valor>> *encontrado{buscarNodo(clave)};

        if(encontrado) { encontrado->dato.valor = valor; }
        else {
            // Hacemos rehash si el factor de carga supera 1.
            if(n + 1 > m) { rehash(siguientePrimo(m*2)); }

            Registro<Valor> nuevo {clave, valor};
            casillas[h(clave)].agregar(nuevo);
            n++;
        }
    }
    // Devuelve un ptr al registro si existe, si no devuelve nullptr
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

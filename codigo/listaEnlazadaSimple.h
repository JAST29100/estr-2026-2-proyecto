// Autores: Joseph Salazar 9038594, Juan Franco 9035048, Sergio Orjuela 9040203

#ifndef LISTA_ENLAZADA_SIMPLE_H
#define LISTA_ENLAZADA_SIMPLE_H

#include <cassert>

template <typename Elemento>
struct Nodo {
    Elemento dato;
    Nodo* siguiente;

    Nodo(): dato{}, siguiente{} {}
    Nodo(Elemento e): dato{e}, siguiente{} {}
    Nodo(Elemento e, Nodo* sig): dato{e}, siguiente{sig} {}
};

template <typename Elemento>
class Lista {
    Nodo<Elemento>* cabeza;
    Nodo<Elemento>* cola;
    int n;

    public:
    Lista(): cabeza{}, cola{}, n{} {}
    ~Lista() {
        while(!vacia()) {
            eliminar(0);
        }
    }

    void insertar(int p, Elemento e) {
        assert(p >= 0 && p <= n);

        Nodo<Elemento>* nuevo {new Nodo(e)};
        if(vacia()){
            cabeza = nuevo;
            cola = nuevo;
        } else if(p == 0) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else if(p == n) {
            cola->siguiente = nuevo;
            cola = nuevo;
        } else {
            Nodo<Elemento>* previo {nodo_en(p-1)};
            Nodo<Elemento>* proximo {previo->siguiente};

            previo->siguiente = nuevo;
            nuevo->siguiente = proximo;
        }
        n++;
    }
    void agregar(Elemento e) {
        Nodo<Elemento>* nuevo {new Nodo(e)};
        if(vacia()) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        n++;
    }
    void asignar(int p, Elemento e) {
        assert(p >= 0 && p < n);
        Nodo<Elemento>* actual {nodo_en(p)};
        actual->dato = e;
    }
    void eliminar(int p) {
        assert(p < n && p >= 0);
        if(n == 1) {
            delete cabeza;
            cabeza = nullptr;
            cola = nullptr;
        } else if(p == 0) {
            Nodo<Elemento>* temp{cabeza};
            cabeza = cabeza->siguiente;
            delete temp;
        } else if(p == n-1) {
            Nodo<Elemento>* temp{nodo_en(p-1)};
            delete cola;
            cola = temp;
            cola->siguiente = nullptr;
        } else {
            Nodo<Elemento>* previo{nodo_en(p-1)};
            Nodo<Elemento>* actual{previo->siguiente};
            previo->siguiente = actual->siguiente;
            delete actual;
        }
        n--;
    }
    Nodo<Elemento>* nodo_en(int p) const {
        assert(p >= 0 && p < n);
        Nodo<Elemento>* actual{cabeza};
        for(int i{}; i < p; i++) { actual = actual->siguiente; }
        return actual;
    }

    // Devuelve el nodo buscado, tiene un parametro opcional para devolver el indice del nodo.
    template<typename Getter, typename Valor>
    Nodo<Elemento>* consultar(Getter obtener_atributo, Valor buscado, int *indice = nullptr) const {
        Nodo<Elemento> *actual{cabeza}, *encontrado{};
        if(indice) { *indice = -1; }
        int i{};

        while(actual && !encontrado) {
            if(obtener_atributo(actual->dato) != buscado) {
                actual = actual->siguiente;
                i++;
            }
            else {
                encontrado = actual;
                if(indice) { *indice = i; }
            }
        }

        return encontrado;
    }

    int tamano() const { return n; }
    bool vacia() const { return n == 0; }

};

#endif // LISTA_ENLAZADA_SIMPLE_H

#pragma once

#include <iostream>
#include <string>
using namespace std;

struct Moneda {
    int id;
    float valor; // valor en soles
    string nombre;
    Moneda* siguiente;
    Moneda* anterior;
    Moneda()
        : id(1), valor(1.0), nombre("PEN"), anterior(nullptr),
        siguiente(nullptr) {}
};
class CMonedas {
private:
    int cantidadMonedas;
    Moneda* listaMonedas;
    Moneda* ultimaMoneda;

    void cambiarId(Moneda* moneda) {
        if (moneda == nullptr)
            return;
        moneda->id--;
        cambiarId(moneda->siguiente);
    }

    void imprimirLista(Moneda* moneda) {
        if (moneda == nullptr) {
            return;
        }
        cout << moneda->id << " \t" << moneda->nombre;
        printf("\t%.2f\n", moneda->valor);
        imprimirLista(moneda->siguiente);
    }

public:
    CMonedas() {
        listaMonedas = new Moneda();
        ultimaMoneda = listaMonedas;
        cantidadMonedas = 1;
    }
    ~CMonedas() {}

    Moneda* buscarPorNombre(string nombre) {
        Moneda* aux = listaMonedas;
        while (aux != nullptr) {
            if (aux->nombre == nombre) {
                return aux;
            }
            aux = aux->siguiente;
        }
        return nullptr;
    }
    float getValorPorNombreRecursivo(Moneda* listaMonedas, string nombre) {
        if (listaMonedas->nombre == nombre) {
            return listaMonedas->valor;
        }
        else if (listaMonedas == nullptr) {
            return 1.0;
        }
        return getValorPorNombreRecursivo(listaMonedas->siguiente, nombre);
    }

    float getValorPorNombre(string nombre) {
        Moneda* aux = listaMonedas;
        while (aux != nullptr) {
            if (aux->nombre == nombre) {
                return aux->valor;
            }
            aux = aux->siguiente;
        }
        return 1.0;
    }
    template <typename T> Moneda* buscarPorId(T id) {
        Moneda* aux = listaMonedas;
        while (aux != nullptr) {
            if (aux->id == id) {
                return aux;
            }
            aux = aux->siguiente;
        }
        return nullptr;
    }
    template <typename T> void agregarMoneda(string nombre, T valor) {
        Moneda* nuevaMoneda = buscarPorNombre(nombre);
        // si la moneda ya existe solo se actualiza el valor
        if (nuevaMoneda != nullptr) {
            nuevaMoneda->valor = valor;
        }
        else {
            // si la moneda no existe se crea una nueva
            nuevaMoneda = new Moneda();
            nuevaMoneda->nombre = nombre;
            nuevaMoneda->valor = valor;
            nuevaMoneda->id = ultimaMoneda->id + 1;
            nuevaMoneda->anterior = ultimaMoneda;
            ultimaMoneda->siguiente = nuevaMoneda;
            ultimaMoneda = nuevaMoneda;
            cantidadMonedas++;
        }
    }
    void eliminarMonedaPorId(int id) {
        Moneda* aux = buscarPorId(id);
        if (aux != nullptr) {
            if (aux == ultimaMoneda) {
                aux->anterior->siguiente = nullptr;
                delete aux;
            }
            else if (aux == listaMonedas) {
                aux->siguiente->anterior = nullptr;
                cambiarId(aux->siguiente);
                delete aux;
            }
            else {
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                cambiarId(aux->siguiente);
                delete aux;
            }
        }
    }

    int getCantidadMonedas() { return cantidadMonedas; }

    void imprimirMonedas() {
        cout << "\nID\tMONEDA\tVALOR EN SOLES"
            << "\n";
        imprimirLista(listaMonedas);
        cout << '\n';
    }

    // guardar los valores en un archivo de texto
    void guardarMonedas() {}
    Moneda* getListaMonedas() { return listaMonedas; }

    void setListaMonedas(Moneda* listaMonedas) {
        this->listaMonedas = listaMonedas;
        Moneda* aux = listaMonedas;
        while (aux->siguiente != nullptr) {
            aux = aux->siguiente;
            cantidadMonedas++;
        }
        ultimaMoneda = aux;
    }
    float getValorCambio(Moneda* monedaInicial, Moneda* nuevaMoneda) {
        float valor = 1 / monedaInicial->valor;
        return 0.1;
    }
};


#pragma once
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

struct Saldo {
    int id;
    float dinero = 0;
    string tipoMoneda;
    Saldo* siguiente;
    Saldo() : id(1), dinero(0), siguiente(nullptr), tipoMoneda("PEN") {}
};

class CCuenta {
private:
    int id;
    string user;
    string password;
    string name;

    int cantidadSaldos;
    Saldo* listaSaldos;
    Saldo* ultimo;

    auto getBuscarPorTipoMoneda() {
        return [&](string tipoMoneda) {
            Saldo* actual = listaSaldos;
            if (listaSaldos == nullptr) {
                return listaSaldos;
            }
            while (actual != nullptr) {
                if (actual->tipoMoneda == tipoMoneda) {
                    return actual;
                }
                actual = actual->siguiente;
            }
            return actual;
        };
    }

public:
    CCuenta() {
        int id = 0;
        string name = "undefined";
        listaSaldos = new Saldo();
        ultimo = listaSaldos;
        cantidadSaldos = 1;
    }
    CCuenta(string name, string user, string password) {
        this->name = name;
        this->user = user;
        this->password = password;
        listaSaldos = new Saldo();
        ultimo = listaSaldos;
        cantidadSaldos = 1;
    }
    ~CCuenta() {}

    void setId(int id) { this->id = id; }
    int getId() { return this->id; }

    void setName(string name) { this->name = name; }

    string getName() { return this->name; }

    void setUser(string user) { this->user = user; }
    string getUser() { return this->user; }

    void setPassword(string password) { this->password = password; }
    string getPassword() { return this->password; }

    void retirarSaldo(float saldo, string tipoMoneda) {

        auto funcionBuscar = getBuscarPorTipoMoneda();
        Saldo* buscado = funcionBuscar(tipoMoneda);
        if (buscado == nullptr || buscado->dinero <= 0) {
            cout << "No tiene saldo en la cuenta esa cuenta" << '\n';
        }
        else {
            if (buscado->dinero < saldo) {
                cout << "Saldo insuficiente" << '\n';
            }
            else
                buscado->dinero -= saldo;
        }
    }

    bool addSaldo(float saldo, string tipoMoneda) {
        if (saldo < 0) {
            cout << "No se pudo realizar el deposito" << '\n';
            return false;
        }
        else {
            auto funcionBuscar = getBuscarPorTipoMoneda();
            Saldo* buscado = funcionBuscar(tipoMoneda);
            if (buscado == nullptr) {
                Saldo* nuevoSaldo = new Saldo();
                nuevoSaldo->tipoMoneda = tipoMoneda;
                nuevoSaldo->dinero = saldo;
                nuevoSaldo->id = ultimo->id + 1;
                ultimo->siguiente = nuevoSaldo;
                ultimo = nuevoSaldo;
                cantidadSaldos++;
            }
            else {
                buscado->dinero += saldo;
            }
        }
        return true;
    }
    void imprimirLista(Saldo* saldo) {
        if (saldo == nullptr) {
            return;
        }
        cout << saldo->id << '\t';
        cout << saldo->tipoMoneda << "\t";
        printf("%.2f\n", saldo->dinero);
        imprimirLista(saldo->siguiente);
    }

    void imprimirCuenta() {
		cout << "Nombre: " << name << '\n';
		cout << "Usuario: " << user << '\n';
		cout << "Password: " << password << '\n';
		cout << "Saldos: " << '\n';
		imprimirLista(listaSaldos);
    }

    void imprimirSaldos() {
        cout << "\nID\tMONEDA\tSALDO"
            << "\n";
        imprimirLista(listaSaldos);
        cout << '\n';
    }

    template <typename T> Saldo* buscarPorId(Saldo* lista, T id) {
        if (lista == nullptr || lista->id == id) {
            return lista;
        };
        return buscarPorId(lista->siguiente, id);
    }

    Saldo* getListaSaldos() { return listaSaldos; }
    int getCantidadSaldos() { return cantidadSaldos; }
};

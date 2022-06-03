#pragma once

#include "Comentario.h"
#include "Cuenta.h"
#include "Monedas.h"
#include "cuentasfilemanager.h"
#include "filemanager.h"
#include "monedasfilemanager.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <string>
#include <vector>

#define FIRST_ID 100

class CController {

private:
    string CUENTAS_FILE = "cuentas.cs";
    string MONEDAS_FILE = "monedas.cs";
    CFileManager* fm;
    CCuentasFileManager* cuentasFM;
    CMonedasFileManager* monedasFM;
    vector<CCuenta*> cuentas;

    CMonedas* monedas;

    CComentarios* comentarios;

public:
    CController() {

        monedasFM = new CMonedasFileManager(MONEDAS_FILE);
        cuentasFM = new CCuentasFileManager(CUENTAS_FILE);
        cuentas = cuentasFM->cargarCuentas();
        monedas = new CMonedas();
        Moneda* sol = monedas->buscarPorNombre("PEN");
        Moneda* dolar = monedas->buscarPorNombre("USD");
        Moneda* euro = monedas->buscarPorNombre("EUR");
        monedas->agregarMoneda("PEN", 1.0);
        monedas->agregarMoneda("USD", 3.83);
        monedas->agregarMoneda("EUR", 4.03);
        monedasFM->escribirMoneda(monedas->getListaMonedas());
        // monedas->setListaMonedas(monedasFM->cargarMonedas());
        comentarios = new CComentarios();
    }
    ~CController() {}
    CCuenta* buscarCuentaPorUsuario(string user) {
        CCuenta* buscada = nullptr;
        for_each(cuentas.begin(), cuentas.end(), [=, &buscada](CCuenta* cuenta) {
            if (user == cuenta->getUser()) {
                buscada = cuenta;
            }
            });
        return buscada;
    }

    void actualizarDatos() { cuentasFM->actualizarUsuarios(cuentas); }

    string seleccionarTipoMoneda() {
        monedas->imprimirMonedas();
        cout << "\n0)\tSalir" << '\n';
        int opcion;
        do {
            cout << "Seleccione una opcion: ";
            cin >> opcion;
        } while (opcion < 0 || opcion > monedas->getCantidadMonedas());
        if (opcion == 0)
            return "";
        auto moneda = monedas->buscarPorId(opcion);
        return moneda->nombre;
    }

    void registrarCuenta(CCuenta* cuenta) {
        cuenta->setId(cuentas.size() + FIRST_ID);
        cuentas.push_back(cuenta);
        fm->escribir(cuenta->getUser() + ".cs",
            "Se ha creado la cuenta a nombre de " + cuenta->getName());
        actualizarDatos();
    }

    void eliminarCuenta(CCuenta* cuenta) {
        cuentas.erase(cuentas.begin() + (cuenta->getId() - FIRST_ID));
        actualizarDatos();
        //fm->eliminarArchivo(cuenta->getUser() + ".cs");
        string operacion =
            "Se ha eliminado su cuenta satisfactoriamente\n";
        fm->escribir(cuenta->getUser() + ".cs", operacion);
        cout << "Su cuenta ha sido eliminada correctamente" << '\n';
    }
    void agregarSaldo(CCuenta* cuenta, string tipoMoneda, float saldo) {
        saldo = (int)((saldo) * 100) / 100.0;
        if (cuenta->addSaldo(saldo, tipoMoneda)) {
            actualizarDatos();
            cout << "Se depositado satisfactoriamente " << saldo << " en la cuenta "
                << tipoMoneda << '\n';
            string operacion =
                "Se ha agregado " + to_string(saldo) + " a la cuenta " + tipoMoneda;
            fm->escribir(cuenta->getUser() + ".cs", operacion);
        }
    }

    CCuenta* iniciarSesion(string user, string password) {
        CCuenta* cuentaObjetivo = buscarCuentaPorUsuario(user);
        if (cuentaObjetivo != nullptr &&
            cuentaObjetivo->getPassword() == password) {
            return cuentaObjetivo;
        }
        return nullptr;
    }

    void retirarDinero(CCuenta* cuenta) {
        cout << "\t\tRETIROS"
            << "\n\n";
        float montoRetirar;
        cuenta->imprimirSaldos();
        int idMoneda;
        cout << "Seleccione el tipo de moneda: ";
        cin >> idMoneda;
        Saldo* saldo = cuenta->buscarPorId(cuenta->getListaSaldos(), idMoneda);
        if (saldo != nullptr) {
            cout << "Digite el monto a retirar: ";
            cin >> montoRetirar;
            cuenta->retirarSaldo(montoRetirar, saldo->tipoMoneda);
            actualizarDatos();
            string operacion = "Se ha retirado " + to_string(montoRetirar) +
                " de la cuenta " +
                monedas->buscarPorId(idMoneda)->nombre;
            fm->escribir(cuenta->getUser() + ".cs", operacion);
        }
        else {
            cout << "No tiene dinero en esa cuenta" << '\n';
        }
    }

    void cambioDivisas(CCuenta* cuenta) {
        cout << "\t\tCAMBIO DE DIVISAS"
            << "\n\n";
        int opcion;
        cuenta->imprimirSaldos();
        cout << "Seleccione la moneda que desea cambiar: ";
        cin >> opcion;
        Saldo* saldo = cuenta->buscarPorId(cuenta->getListaSaldos(), opcion);
        string monedaInicial = saldo->tipoMoneda;
        if (saldo != nullptr && saldo->dinero > 0) {
            monedas->imprimirMonedas();
            cout << "Seleccione la nueva moneda: ";
            cin >> opcion;
            Moneda* monedaNueva = monedas->buscarPorId(opcion);
            if (monedaNueva != nullptr) {
                float valorInicial;
                cout << "Digite el monto a convertir: ";
                cin >> valorInicial;
                if (valorInicial > 0 && valorInicial <= saldo->dinero) {
                    cuenta->retirarSaldo(valorInicial, monedaInicial);
                    // convirtiendo a soles
                    float valorInicialSoles =
                        valorInicial * monedas->getValorPorNombreRecursivo(
                            monedas->getListaMonedas(), monedaInicial);
                    // convetir a la nueva moneda
                    // los * 100 y / 100 son para redondear a dos cifras de cimales
                    float valorConvertido =
                        (int)((valorInicialSoles / monedaNueva->valor) * 100) / 100.0;
                    cuenta->addSaldo(valorConvertido, monedaNueva->nombre);
                    actualizarDatos();
                    cout << "Su cambio se ha realizado correctamente" << '\n';

                    string operacion = "Se ha cambiado " + to_string(valorInicial) + " " +
                        monedaInicial + " a " +
                        to_string(valorConvertido) + " " +
                        monedaNueva->nombre;
                    fm->escribir(cuenta->getUser() + ".cs", operacion);

                }
                else {
                    cout << "No se pudo realizar el cambio,\nel monto minimo a convertir "
                        "es 5"
                        << '\n';
                }

            }
            else {
                cout << "No se ha encontrado esa moneda" << '\n';
            }
        }
        else {
            cout << "No tiene dinero en esa cuenta" << '\n';
        }
    }
    void mostrarHistorial(CCuenta* cuenta) {
        string fileName = cuenta->getUser() + ".cs";
        cout << "\n\tFECHA\t\tOPERACION"
            << "\n\n";
        string history = fm->leerArchivo(fileName);
        cout << history << '\n';
        cout << '\n';
    }
    void agregarComentario(string autor, string texto) {
        comentarios->push(autor, texto);
        comentarios->escribirComentarios(fm);
    }
    void imprimirComentarios() { comentarios->imprimirPila(fm); }

    void merge(vector<CCuenta*> &cuentas, int l, int m, int r) {

        int n1 = m - l + 1;
        int n2 = r - m;

        vector<CCuenta*> cuentasLeft;
        vector<CCuenta*> cuentasRight;

        for (int i = 0; i < n1; i++) {
            cuentasLeft.push_back(cuentas[l + i]);
        }

        for (int j = 0; j < n2; j++) {
            cuentasRight.push_back(cuentas[m + j + 1]);
        }

        // index of vector left and right
        int i1 = 0, i2 = 0;
        // index of merged vector
        int i = l;

        while (i1 < n1 && i2 < n2) {
            if (cuentasLeft[i1]->getName()[0] <= cuentasRight[i2]->getName()[0]) {
                cuentas[i] = cuentasLeft[i1];
                i1++;
            }
            else {
                cuentas[i] = cuentasRight[i2];
                i2++;
            }
            i++;
        }
        // Copy the remaining elements of cuentasLeft if there are any
        while (i1 < n1) {
            cuentas[i] = cuentasLeft[i1];
            i1++;
            i++;
        }

        // Copy the remaining elements of cuentasRight if there are any
        while (i2 < n2) {
            cuentas[i] = cuentasRight[i2];
            i2++;
            i++;
        }
    }

    void mergeSort(vector<CCuenta*> &cuentas, int l, int r) {

        if (l >= r)
            return;

        int m = (l + r) / 2;

        mergeSort(cuentas, l, m);
        mergeSort(cuentas, m + 1, r);
        merge(cuentas, l, m, r);
    }

    void selectionSort() {

        for (int i = 0; i < cuentas.size() - 1; i++) {
            int menor = i;
            for (int j = i; j < cuentas.size(); j++) {
                if (cuentas[j]->getName()[0] < cuentas[menor]->getName()[0]) {
                    menor = j;
                }
            }
            // swap
            CCuenta* aux = cuentas[menor];
            cuentas[menor] = cuentas[i];
            cuentas[i] = aux;
        }
    }

    void ordenarCuentas() {
        // selectionSort();
        vector<CCuenta*> cuentasOrdenadas;
        //copiar datos de cuentas a cuentasOrdenadas
        for(CCuenta* c : cuentas)
        {
            cuentasOrdenadas.push_back(c);
        }

        mergeSort(cuentasOrdenadas, 0, cuentas.size() - 1);
        for (auto i : cuentasOrdenadas) {
            cout << i->getId() << "  " << i->getName() << '\n';
        }
    }

	//buscar cuenta por ID
	CCuenta* buscarPorId(int id) {
		for (auto i : cuentas) {
            cout << i->getId() << "  " << i->getName() << '\n';
			if (i->getId() == id) {
				return i;
			}
		}
		return nullptr;
	}

	//binary search by ID
	CCuenta* binarySearchId(int id) {
		int l = 0, r = cuentas.size() - 1;
		while (l <= r) {
			int m = (l + r) / 2;
            if (cuentas[m])
                cout << cuentas[m]->getId() << "  " << cuentas[m]->getName() << '\n';

			if (cuentas[m]->getId() == id) {
				return cuentas[m];
			}
			else if (cuentas[m]->getId() < id) {
				l = m + 1;
			}
			else {
				r = m - 1;
			}
		}
		return nullptr;
	}
    void mostrarCuentas() {
		cout << "ID\tNOMBRE\n\n";
		for (auto i : cuentas) {
			cout << i->getId() << "  " <<  i->getName() << '\n';
		}
    }
};

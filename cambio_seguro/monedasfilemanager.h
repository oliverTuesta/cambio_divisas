#pragma once

#include "Monedas.h"
#include "filemanager.h"

using namespace std;
class CMonedasFileManager : public CFileManager {
private:
public:
    CMonedasFileManager(string fileName) : CFileManager(fileName) {}
    ~CMonedasFileManager() {}
    void escribirMoneda(Moneda* moneda) {
        if (moneda == nullptr) {
            return;
        }
        ofstream file;
        file.open(fileName, ios::out | ::ios::binary);
        if (file.is_open()) {
            file.write((const char*)&moneda, sizeof(Moneda));
        }
        else {
            std::cout << "error al guardar lista de monedas" << std::endl;
        }
    }
    Moneda* cargarMonedas() {
        ifstream file;
        Moneda* m = nullptr;
        file.open(fileName, ios::out | ::ios::binary);
        if (file.is_open()) {
            file.seekg(0 * sizeof(&m), ios::beg);
            file.read((char*)&m, sizeof(Moneda));
        }
        else {
            std::cout << "error al guardar lista de monedas" << std::endl;
        }
        return m;
    }
};

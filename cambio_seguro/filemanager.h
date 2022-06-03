#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class CFileManager {
protected:
    string fileName;

public:
    CFileManager(string fileName) { this->fileName = fileName; }
    ~CFileManager() {}

    string leerArchivo(string fileName) {
        ifstream file;
        file.open(fileName, ios::in);
        string text = "";
        string line;
        if (file.is_open()) {
            while (!file.eof()) {
                getline(file, line);
                text += line + '\n';
            }
        }
        return text;
    }

	//eliminar archvios dado un nombre
	void eliminarArchivo(string fileName) {
		remove(fileName.c_str());
	}


    void leerCaracteres() {
        ifstream file;
        file.open(fileName, ios::in);
        if (file.is_open()) {
            char data;
            while (!file.eof()) {
                file >> data;
                cout << data << " ";
            }
            file.close();
        }
        else
            cout << "Cannot open the file: " << fileName << '\n';
        cout << '\n';
    }

    // Agregar mas notas al archivo notas
    //
    //
    void escribirFecha(string fileName) {
        ofstream file;
        file.open(fileName, ios::app);

        time_t now = time(0);
        tm* ltm = localtime(&now);

        if (file.is_open()) {
            file << ltm->tm_hour << ":";
            file << ltm->tm_min;
            file << "   " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/"
                << 1900 + ltm->tm_year << "  :  ";
            file.close();
        }
    }

    void borrar(string fileName) {

        ofstream file;
        file.open(fileName, ios::out);
        if (file.is_open())
            file << " ";
    }

    void escribirAntes(string fileName, string texto) {
        ofstream file;
        file.open(fileName, ios::out);
        if (file.is_open()) {
            file << texto;
            file.close();
        }
    }

    template <typename T> void escribir(string fileName, T dato) {
        escribirFecha(fileName);
        ofstream file;
        file.open(fileName, ios::app);
        if (file.is_open()) {
            file << dato << '\n';
            file.close();
        }
        else {
            cout << "Error al escribir el archivo" << '\n';
        }
    }
};
#pragma once
#include "filemanager.h"
#include <iostream>
#include <string>

using namespace std;

class CComentarios {
private:
  struct Nodo {
    string autor;
    string texto;
    Nodo *siguiente;
    Nodo() : siguiente(nullptr) {}
  };

public:
  string antes;
  Nodo *head;
  CComentarios() { head = nullptr; }
  ~CComentarios() {}

  void push(string autor, string texto) {
    Nodo *nuevo = new Nodo();
    nuevo->autor = autor;
    nuevo->texto = texto;
    nuevo->siguiente = head;
    head = nuevo;
  }

  void escribirComentarios(CFileManager *fm) {
    antes = fm->leerArchivo("comentarios.cs");
    // cout << "antes: " << antes << '\n';
    Nodo *aux = head;
    string comentario;
    // while (aux != nullptr) {
    //  comentario += "\n" + aux->autor + ":\n\t" + aux->texto + "\n\n";
    // aux = aux->siguiente;
    //}
    // Escribe el primer comentario de la pila
    comentario += "\n" + aux->autor + ":\n\t" + aux->texto + "\n\n";
    fm->escribirAntes("comentarios.cs", comentario + antes);
  }

  void imprimirPila(CFileManager *fm) {
    cout << "\t\tCOMENTARIOS\n" << '\n';
    cout << fm->leerArchivo("comentarios.cs");
  }
};

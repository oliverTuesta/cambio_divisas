#pragma once
#include <iostream>
#include <algorithm>
#include "ArbolNode.h"

using namespace std;

template <class T>
class ArbolBinarioAVL
{
private:
    Node<T> *root;
    // arbol binario de busqueda balanceado
    int altura(Node<T> *n)
    {
        if (n == NULL)
            return 0;
        return n->altura;
    }

    int balance(Node<T> *n)
    {
        if (n == NULL)
            return 0;
        return altura(n->left) - altura(n->right);
    }

    // rotar a la derecha
    Node<T> *rotarDerecha(Node<T> *n)
    {
        Node<T> *q = n->left;
        n->left = q->right;
        q->right = n;
        n->altura = max(altura(n->left), altura(n->right)) + 1;
        q->altura = max(altura(q->left), altura(q->right)) + 1;
        return q;
    }

    // rotar a la izquierda
    Node<T> *rotarIzquierda(Node<T> *n)
    {
        Node<T> *q = n->right;
        n->right = q->left;
        q->left = n;
        n->altura = max(altura(n->left), altura(n->right)) + 1;
        q->altura = max(altura(q->left), altura(q->right)) + 1;
        return q;
    }

    // rotar a la izquierda y derecha
    Node<T> *rotarDobleIzquierda(Node<T> *n)
    {
        n->left = rotarIzquierda(n->left);
        return rotarDerecha(n);
    }

    // rotar a la derecha y izquierda
    Node<T> *rotarDobleDerecha(Node<T> *n)
    {
        n->right = rotarDerecha(n->right);
        return rotarIzquierda(n);
    }

    // balancear el arbol
    Node<T> *balancear(Node<T> *n)
    {
        if (balance(n) == 2)
        {
            if (balance(n->left) >= 0)
                return rotarDerecha(n);
            else
                return rotarDobleIzquierda(n);
        }
        if (balance(n) == -2)
        {
            if (balance(n->right) <= 0)
                return rotarIzquierda(n);
            else
                return rotarDobleDerecha(n);
        }
        return n;
    }

    // insertar un nodo en el arbol
    Node<T> *insertar(Node<T> *n, int key, T data)
    {
        if (n == NULL)
        {
            n = new Node<T>(key, data);
        }
        else if (key < n->key)
        {
            n->left = insertar(n->left, key, data);
        }
        else if (key > n->key)
        {
            n->right = insertar(n->right, key, data);
        }
        else
        {
            cout << "El nodo ya existe" << endl;
        }
        n->altura = max(altura(n->left), altura(n->right)) + 1;
        return balancear(n);
    }

    // imprimir preOrder
    void _preOrder(Node<T> *n)
    {
        if (n != NULL)
        {
            cout << n->data->toString() << endl;
            _preOrder(n->left);
            _preOrder(n->right);
        }
    }

    // buscar nodo
    T buscar(Node<T> *node, int key)
    {
        if (node)
            cout << "id: " << node->key << endl;
        if (node == NULL)
        {
            return NULL;
        }
        else if (key < node->key)
        {
            return buscar(node->left, key);
        }
        else if (key > node->key)
        {
            return buscar(node->right, key);
        }
        else
        {
            return node->data;
        }
    }

public:
    ArbolBinarioAVL()
    {
        root = NULL;
    }

    // insertar un nodo
    void insertar(int key, T data)
    {
        root = insertar(root, key, data);
    }

    void imprimir()
    {
        if (root == NULL)
        {
            cout << "Arbol vacio" << endl;
        }
        else
        {
            cout << "\nPreOrder: \n";
            _preOrder(root);
            cout << endl;
        }
    }

    T buscar(int key)
    {
        return buscar(root, key);
    }
};

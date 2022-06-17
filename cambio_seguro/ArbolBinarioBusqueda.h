#pragma once

#include <iostream>
#include "ArbolNode.h"
using namespace std;

template <class T>
class ArbolBinarioBusqueda
{
private:
    Node<T> *root;
    void insertar(Node<T> *&node, int key, T data)
    {
        if (node == NULL)
        {
            node = new Node<T>(key, data);
        }
        else if (key < node->key)
        {
            insertar(node->left, key, data);
        }
        else if (key > node->key)
        {
            insertar(node->right, key, data);
        }
    }
    void postOrder(Node<T> *node)
    {
        if (node != NULL)
        {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->data->toString() << endl;
        }
    }
    void preOrder(Node<T> *node)
    {
        if (node != NULL)
        {
            cout << node->data->toString() << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }
    void inOrder(Node<T> *node)
    {
        if (node != NULL)
        {
            inOrder(node->left);
            cout << node->data->toString() << endl;
            inOrder(node->right);
        }
    }

    // buscar un nodo en el arbol dada una llave
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
    ArbolBinarioBusqueda()
    {
        root = NULL;
    }
    ~ArbolBinarioBusqueda()
    {
        delete root;
    }
    void insertar(int key, T data)
    {
        insertar(root, key, data);
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
            preOrder(root);
            cout << endl;
        }
    }

    T buscar(int key)
    {
        return buscar(root, key);
    }
};

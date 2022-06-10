#pragma once

#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
    int key;
    T data;
    Node<T> *left;
    Node<T> *right;
    Node(int key, T data)
    {
        this->key = key;
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

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
    Node<T> *buscar(Node<T> *node, int key)
    {
        if (node == NULL || node->key == key)
        {
            return node;
        }
        cout << node->data->getId() << "  " << node->data->getName() << '\n';
        if (key < node->key)
        {
            return buscar(node->left, key);
        }
        else
        {
            return buscar(node->right, key);
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
            cout << "InOrder: \n";
            inOrder(root);
            cout << endl;
            cout << "\nPostOrder: \n";
            postOrder(root);
            cout << endl;
        }
    }
    Node<T> *buscar(int key)
    {
        cout << "aqui1" << endl;
        return buscar(root, key);
    }
};

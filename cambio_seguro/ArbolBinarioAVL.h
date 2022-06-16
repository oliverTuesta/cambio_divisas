#pragma once
#include <iostream>
#include <algorithm>
#include "ArbolNode.h"

using namespace std;

template <class T>
class ArbolBinarioAVL
{
private:
    Node<T>* root;
    // arbol binario de busqueda balanceado

    int altura(Node<T>* n)
    {
        if (n == NULL)
            return 0;
        return n->altura;
    }

    int balance(Node<T>* n)
    {
        if (n == NULL)
            return 0;
        return altura(n->left) - altura(n->right);
    }

    // rotar a la derecha
    Node<T>* rotarDerecha(Node<T>* n)
    {
        Node<T>* q = n->left;
        n->left = q->right;
        q->right = n;
        n->altura = max(altura(n->left), altura(n->right)) + 1;
        q->altura = max(altura(q->left), altura(q->right)) + 1;
        return q;
    }

    // rotar a la izquierda
    Node<T>* rotarIzquierda(Node<T>* n)
    {
        Node<T>* q = n->right;
        n->right = q->left;
        q->left = n;
        n->altura = max(altura(n->left), altura(n->right)) + 1;
        q->altura = max(altura(q->left), altura(q->right)) + 1;
        return q;
    }

    // insertar nodo
    Node<T>* insertar(Node<T>* n, int key, T data)
    {
        if (n == NULL)
        {
            n = new Node<T>(key, data);
            return n;
        }
        if (key < n->key)
        {
            n->left = insertar(n->left, key, data);
        }
        else if (key > n->key)
        {
            n->right = insertar(n->right, key, data);
        }
        else
        {
            n->data = data;
        }
        n->altura = max(altura(n->left), altura(n->right)) + 1;
        int bal = balance(n);
        if (bal > 1 && key < n->left->key)
        {
            return rotarDerecha(n);
        }
        if (bal < -1 && key > n->right->key)
        {
            return rotarIzquierda(n);
        }
        if (bal > 1 && key > n->left->key)
        {
            n->left = rotarIzquierda(n->left);
            return rotarDerecha(n);
        }
        if (bal < -1 && key < n->right->key)
        {
            n->right = rotarDerecha(n->right);
            return rotarIzquierda(n);
        }
        return n;
    }

    // preorden
    void preOrder(Node<T>* n)
    {
        if (n != NULL)
        {
            cout << n->data->toString() << endl;
            preOrder(n->left);
            preOrder(n->right);
        }
    }

public:
    ArbolBinarioAVL()
    {
        root = NULL;
    }
    void insertar(int key, T data)
    {
        root = insertar(root, key, data);
    }
    void preOrder()
    {
        preOrder(root);
    }
};

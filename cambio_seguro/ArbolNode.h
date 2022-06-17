#pragma once

template <class T>
class Node
{
public:
    int key;
    T data;
    Node<T> *left;
    Node<T> *right;
    int altura;
    Node(int key, T data)
    {
        this->key = key;
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
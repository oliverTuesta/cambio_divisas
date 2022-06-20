#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class NTree
{
private:
    T data;
    vector<NTree<T> *> children;
    int height;

    // insert
    void insert(T data, NTree<T> *node)
    {
        if (node == NULL)
        {
            node = new NTree<T>(data);
            return;
        }

        if (data < node->data)
        {
            if (node->left == NULL)
            {
                node->left = new NTree<T>(data);
                return;
            }
            insert(data, node->left);
        }
        else
        {
            if (node->right == NULL)
            {
                node->right = new NTree<T>(data);
                return;
            }
            insert(data, node->right);
        }
    }

    // print
    void print(NTree<T> *node)
    {
        if (node == NULL)
            return;

        print(node->left);
        cout << node->data << " ";
        print(node->right);
    }

public:
    NTree(T data)
    {
        this->data = data;
        this->height = 0;
    }
};
#pragma once

#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class NodeHash
{
public:
    T data;
    int key;
    NodeHash<T>* next;
    NodeHash<T>* prev;
    NodeHash(int key, T data)
    {
        this->key = key;
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

template <class T>
class HashTable
{
private:
    int size;
    NodeHash<T>** table;

    int hashFunction(int key)
    {
        return key % size;
    }

public:
    HashTable(int size)
    {
        this->size = size;
        table = new NodeHash<T> *[size];
        for (int i = 0; i < size; i++)
        {
            table[i] = NULL;
        }
    }
    void insert(int key, T data)
    {
        int hash_value = hashFunction(key);
        NodeHash<T>* new_node = new NodeHash<T>(key, data);
        if (table[hash_value] == NULL)
        {
            table[hash_value] = new_node;
        }
        else
        {
            NodeHash<T>* temp = table[hash_value];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->prev = temp;
        }
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {

            NodeHash<T>* temp = table[i];
            if (temp)
                cout << "\nIndex " << i << "\n";
            while (temp != NULL)
            {
                cout << temp->data->getIdeNombre() << endl;
                temp = temp->next;
            }
        }
    }
};

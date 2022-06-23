#pragma once
#include <iostream>
#include <string>
#include "Cuenta.h"

using namespace std;

// Define character size
#define CHAR_SIZE 256

// Define the node structure
struct NodeTrie
{
    char data;
    NodeTrie *children[CHAR_SIZE];
    bool isEndOfWord;
    CCuenta* cuenta;
};

// Define the class
class ArbolTrie
{
    NodeTrie *root;

    // Function to create a new node
    NodeTrie* newNodeTrie(char data)
    {
        NodeTrie *temp = new NodeTrie;
        temp->data = data;
        temp->isEndOfWord = false;
        for (int i = 0; i < CHAR_SIZE; i++)
            temp->children[i] = NULL;
        return temp;
    }

    // Function to insert a new node in the Trie
    void insert(NodeTrie *root, string key, CCuenta* cuenta)
    {
        NodeTrie *pCrawl = root;
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i];
            if (!pCrawl->children[index])
                pCrawl->children[index] = newNodeTrie(index);
            pCrawl = pCrawl->children[index];
        }
        pCrawl->isEndOfWord = true;
        pCrawl->cuenta = cuenta;
    }

    // Function to search a string in the Trie
    // Returns true if string is found in Trie, else false
    bool search(NodeTrie *root, string key)
    {
        if (root == NULL)
            return false;
        NodeTrie *pCrawl = root;
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i];
            if (pCrawl->children[index] == NULL)
                return false;
            pCrawl = pCrawl->children[index];
        }
        return (pCrawl != NULL && pCrawl->isEndOfWord);
    }

    // Function to print the Trie
    void print(NodeTrie *root, string str)
    {
        if (root == NULL)
            return;
        for (int i = 0; i < CHAR_SIZE; i++)
            if (root->children[i])
                print(root->children[i], str + root->data);
        if (root->isEndOfWord)
            cout << str << endl;
    }

    // Function to search into the Trie
    // return CCuenta * if found, else NULL
    CCuenta* searchCuenta(NodeTrie *root, string key)
    {
        if (root == NULL)
            return NULL;
        NodeTrie *pCrawl = root;
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i];
            if (pCrawl->children[index] == NULL)
                return NULL;
            pCrawl = pCrawl->children[index];
        }
        return (pCrawl != NULL && pCrawl->isEndOfWord) ? pCrawl->cuenta : NULL;
    }
public:
    ArbolTrie()
    {
        root = newNodeTrie('\0');
    }

    // Function to insert a new string in the Trie
    void insert(string key, CCuenta* cuenta)
    {
        insert(root, key, cuenta);
    }

    // Function to search a string in the Trie
    // Returns true if string is found in Trie, else false
    bool search(string key)
    {
        return search(root, key);
    }

    // Function to print the Trie
    void print()
    {
        print(root, "");
    }

    // Function to search into the Trie
    // return CCuenta * if found, else NULL
    CCuenta* searchCuenta(string key)
    {
        return searchCuenta(root, key);
    }
};

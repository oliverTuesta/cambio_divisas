#include "TrieTree.h"
#include <iostream>
#include <vector>

using namespace std;

// radix sort
int getMax(vector<int> &v)
{
    int max = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }
    return max;
}

// count sort
void countSort(vector<int> &v, int exp)
{
    int output[v.size()];
    int i, count[10] = {0};
    for (i = 0; i < v.size(); i++)
    {
        count[(v[i] / exp) % 10]++;
    }
    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (i = v.size() - 1; i >= 0; i--)
    {
        output[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
    }
    for (i = 0; i < v.size(); i++)
    {
        v[i] = output[i];
    }
}

// radix sort
void radixSort(vector<int> &v)
{
    int m = getMax(v);
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        countSort(v, exp);
    }
}

// C++ implementation of Trie data structure
int main()
{
    Trie *head = new Trie();

    head->insert("hello");
    cout << head->search("hello") << " "; // print 1

    head->insert("helloworld");
    cout << head->search("helloworld") << " "; // print 1

    cout << head->search("helll") << " "; // print 0 (Not found)

    head->insert("hell");
    cout << head->search("hell") << " "; // print 1

    head->insert("h");
    cout << head->search("h"); // print 1

    cout << endl;

    head->deletion(head, "hello");
    cout << head->search("hello") << " "; // print 0

    cout << head->search("helloworld") << " "; // print 1
    cout << head->search("hell");              // print 1

    cout << endl;

    head->deletion(head, "h");
    cout << head->search("h") << " ";    // print 0
    cout << head->search("hell") << " "; // print 1
    cout << head->search("helloworld");  // print 1

    cout << endl;

    head->deletion(head, "helloworld");
    cout << head->search("helloworld") << " "; // print 0
    cout << head->search("hell") << " ";       // print 1

    head->deletion(head, "hell");
    cout << head->search("hell"); // print 0

    cout << endl;

    if (head == nullptr)
    {
        cout << "Trie empty!!\n"; // Trie is empty now
    }

    cout << head->search("hell"); // print 0

    cout << "\n\nRadix sort: \n";
    // testing radix sort
    vector<int> v = {11, 2, 53, 7, 8, 9, 1, 5, 6, 10};
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    radixSort(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    return 0;
}

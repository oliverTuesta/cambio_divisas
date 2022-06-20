#include "TrieTree.h"
#include <iostream>

using namespace std;

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

    return 0;
}
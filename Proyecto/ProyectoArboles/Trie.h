#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    bool finPalabra;
    unordered_map<char, TrieNode*> hijos;

    TrieNode() : finPalabra(false) {}
};

class Trie {
private:
    TrieNode* raiz;

public:
    Trie();
    ~Trie();

    void insertar(const string& palabra);
    void eliminar(const string& palabra);
    vector<string> autocompletar(const string& prefijo);
};

#endif

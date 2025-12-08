#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct TrieNode {
    bool esFin;
    unordered_map<char, TrieNode*> hijos;

    TrieNode() : esFin(false) {}
};

class Trie {
private:
    TrieNode* raiz;

    void dfs(TrieNode* nodo, string prefijo, vector<string>& resultados) {
        if (!nodo) return;

        if (nodo->esFin)
            resultados.push_back(prefijo);

        for (auto& par : nodo->hijos) {
            dfs(par.second, prefijo + par.first, resultados);
        }
    }

public:
    Trie() { raiz = new TrieNode(); }

    void insertar(const string& palabra) {
        TrieNode* actual = raiz;
        for (char c : palabra) {
            if (!actual->hijos.count(c))
                actual->hijos[c] = new TrieNode();
            actual = actual->hijos[c];
        }
        actual->esFin = true;
    }

    vector<string> autocompletar(const string& prefijo) {
        TrieNode* actual = raiz;

        for (char c : prefijo) {
            if (!actual->hijos.count(c))
                return {};
            actual = actual->hijos[c];
        }

        vector<string> resultados;
        dfs(actual, prefijo, resultados);
        return resultados;
    }
};

#endif

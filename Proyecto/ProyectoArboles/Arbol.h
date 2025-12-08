#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include <vector>
using namespace std;

#include "Nodo.h"
#include "Trie.h"

class Arbol {
private:
    Nodo* raiz;
    int ultimoId;
    Trie trie;  // Día 5-6

public:
    Arbol();
    ~Arbol();

    Nodo* getRaiz() const;
    int getUltimoId() const;

    Nodo* buscarRuta(const string& ruta);

    // Día 3
    Nodo* crearCarpeta(const string& ruta, const string& nombre);
    Nodo* crearArchivo(const string& ruta, const string& nombre, const string& contenido);

    // Día 5–6
    vector<string> autocompletar(const string& prefijo);

    // Día 4
    void guardarJSON(const string& archivo);
    void cargarJSON(const string& archivo);
};

#endif

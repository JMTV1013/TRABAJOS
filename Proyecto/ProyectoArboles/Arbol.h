#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

#include "Nodo.h"
#include "Trie.h"

class Arbol {
private:
    Nodo* raiz;
    int ultimoId;
    Trie trie;

    unordered_map<int, Nodo*> indiceId;
    vector<Nodo*> papelera;

public:
    Arbol();
    ~Arbol();

    Nodo* buscarRuta(const string& ruta);
    Nodo* buscarPorId(int id);

    Nodo* crearCarpeta(const string& ruta, const string& nombre);
    Nodo* crearArchivo(const string& ruta, const string& nombre, const string& contenido);

    bool eliminar(const string& ruta);
    bool restaurar(int id);
    void vaciarPapelera();
    void listarPapelera();

    bool mover(const string& origen, const string& destino);
    bool renombrar(const string& ruta, const string& nuevoNombre);

    vector<string> autocompletar(const string& prefijo);
    void exportarPreorden(ofstream& out);

    void guardarJSON(const string& archivo);
    void cargarJSON(const string& archivo);
};

#endif

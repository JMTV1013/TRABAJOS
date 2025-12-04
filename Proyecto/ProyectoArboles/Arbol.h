#ifndef ARBOL_H
#define ARBOL_H

#include <string>
using namespace std;

#include "Nodo.h"

class Arbol {
private:
    Nodo* raiz;
    int ultimoId;

public:
    Arbol();
    ~Arbol();

    Nodo* getRaiz() const;
    int getUltimoId() const;

    Nodo* buscarRuta(const string& ruta);

    // Se implementarán en días posteriores:
    // crearCarpeta
    // crearArchivo
    // eliminar
    // mover
    // guardarJSON
    // cargarJSON
};

#endif

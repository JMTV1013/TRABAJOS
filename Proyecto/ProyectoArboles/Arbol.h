#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include "Nodo.h"

using namespace std;
class Arbol {
private:
    Nodo* raiz;
    int ultimoId;

public:
    Arbol();
    ~Arbol();

    Nodo* getRaiz() const;
    int getUltimoId() const;

    Nodo* buscarRuta(const string& ruta); // se implementará en Día 2

    // funciones que se implementarán más adelante:
    // crearCarpeta
    // crearArchivo
    // eliminar
    // mover
    // guardarJSON
    // cargarJSON
};

#endif

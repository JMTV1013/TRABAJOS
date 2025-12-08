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

    // insertar nodos:
    Nodo* crearCarpeta(const string& ruta, const string& nombre);
    Nodo* crearArchivo(const string& ruta, const string& nombre, const string& contenido);

    // JSON:
    void guardarJSON(const string& archivo);
    void cargarJSON(const string& archivo);
};

#endif

#include "Arbol.h"
#include <sstream>
#include <iostream>

using namespace std;

// Función auxiliar para liberar memoria del árbol
static void liberarNodo(Nodo* n) {
    if (!n) return;
    for (auto* hijo : n->hijos) {
        liberarNodo(hijo);
    }
    delete n;
}

// Constructor
Arbol::Arbol() {
    raiz = new Nodo(0, "root", "carpeta");
    ultimoId = 1;
}

// Destructor
Arbol::~Arbol() {
    liberarNodo(raiz);
}

Nodo* Arbol::getRaiz() const {
    return raiz;
}

int Arbol::getUltimoId() const {
    return ultimoId;
}

// Buscar un nodo mediante ruta tipo "/Carpeta/Subcarpeta"
Nodo* Arbol::buscarRuta(const string& ruta) {
    if (ruta == "/" || ruta == "/root" || ruta == "")
        return raiz;

    stringstream ss(ruta);
    string segmento;
    Nodo* actual = raiz;

    while (getline(ss, segmento, '/')) {
        if (segmento.empty()) continue;

        bool encontrado = false;
        for (auto* hijo : actual->hijos) {
            if (hijo->nombre == segmento) {
                actual = hijo;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            return nullptr;
        }
    }

    return actual;
}

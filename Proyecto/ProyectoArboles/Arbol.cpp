#include "Arbol.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// ===================================================
// Liberar memoria del árbol
// ===================================================
static void liberarNodo(Nodo* n) {
    if (!n) return;
    for (auto* hijo : n->hijos)
        liberarNodo(hijo);
    delete n;
}

// ===================================================
// Constructor
// ===================================================
Arbol::Arbol() {
    raiz = new Nodo(0, "root", "carpeta");
    ultimoId = 1;
}

// ===================================================
// Destructor
// ===================================================
Arbol::~Arbol() {
    liberarNodo(raiz);
}

Nodo* Arbol::getRaiz() const { return raiz; }
int Arbol::getUltimoId() const { return ultimoId; }

// ===================================================
// Buscar ruta (Día 2)
// ===================================================
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
        if (!encontrado) return nullptr;
    }

    return actual;
}

// ===================================================
// Día 3 — Crear Carperta
// ===================================================
Nodo* Arbol::crearCarpeta(const string& ruta, const string& nombre) {
    Nodo* padre = buscarRuta(ruta);
    if (!padre || padre->tipo != "carpeta") {
        cout << "Ruta padre invalida.\n";
        return nullptr;
    }

    Nodo* nueva = new Nodo(ultimoId++, nombre, "carpeta");
    nueva->padre = padre;
    padre->hijos.push_back(nueva);

    return nueva;
}

// ===================================================
// Día 3 — Crear Archivo
// ===================================================
Nodo* Arbol::crearArchivo(const string& ruta, const string& nombre, const string& contenido) {
    Nodo* padre = buscarRuta(ruta);
    if (!padre || padre->tipo != "carpeta") {
        cout << "Ruta padre invalida.\n";
        return nullptr;
    }

    Nodo* nuevo = new Nodo(ultimoId++, nombre, "archivo");
    nuevo->contenido = contenido;
    nuevo->padre = padre;
    padre->hijos.push_back(nuevo);

    return nuevo;
}

// ===================================================
// Día 4 — NODO → JSON
// ===================================================
static json nodoAJson(Nodo* n) {
    json j;
    j["id"] = n->id;
    j["nombre"] = n->nombre;
    j["tipo"] = n->tipo;
    j["contenido"] = n->contenido;

    j["children"] = json::array();
    for (auto* hijo : n->hijos)
        j["children"].push_back(nodoAJson(hijo));

    return j;
}

// ===================================================
// Día 4 — JSON → NODO
// ===================================================
static Nodo* jsonANodo(const json& j, Nodo* padre = nullptr) {
    Nodo* n = new Nodo(j["id"], j["nombre"], j["tipo"]);
    n->contenido = j["contenido"];
    n->padre = padre;

    for (auto& hijo : j["children"]) {
        Nodo* h = jsonANodo(hijo, n);
        n->hijos.push_back(h);
    }

    return n;
}

// ===================================================
// Guardar JSON
// ===================================================
void Arbol::guardarJSON(const string& archivo) {
    json j;
    j["root"] = nodoAJson(raiz);
    j["ultimoId"] = ultimoId;

    ofstream out(archivo);
    out << j.dump(4);
    out.close();

    cout << "Guardado en " << archivo << endl;
}

// ===================================================
// Cargar JSON
// ===================================================
void Arbol::cargarJSON(const string& archivo) {
    ifstream in(archivo);
    if (!in.is_open()) {
        cout << "No se pudo abrir " << archivo << endl;
        return;
    }

    json j;
    in >> j;
    in.close();

    liberarNodo(raiz);

    raiz = jsonANodo(j["root"], nullptr);
    ultimoId = j["ultimoId"];

    cout << "Cargado desde " << archivo << endl;
}

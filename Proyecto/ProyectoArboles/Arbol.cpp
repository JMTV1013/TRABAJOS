#include "Arbol.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Liberar memoria
static void liberarNodo(Nodo* n) {
    if (!n) return;
    for (auto* h : n->hijos)
        liberarNodo(h);
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

Nodo* Arbol::getRaiz() const { return raiz; }
int Arbol::getUltimoId() const { return ultimoId; }

// Buscar ruta
Nodo* Arbol::buscarRuta(const string& ruta) {
    if (ruta == "/" || ruta == "/root" || ruta == "")
        return raiz;

    stringstream ss(ruta);
    string seg;
    Nodo* actual = raiz;

    while (getline(ss, seg, '/')) {
        if (seg.empty()) continue;

        bool enc = false;
        for (auto* h : actual->hijos) {
            if (h->nombre == seg) {
                actual = h;
                enc = true;
                break;
            }
        }
        if (!enc) return nullptr;
    }

    return actual;
}

// Crear carpeta
Nodo* Arbol::crearCarpeta(const string& ruta, const string& nombre) {
    Nodo* padre = buscarRuta(ruta);
    if (!padre || padre->tipo != "carpeta") {
        cout << "Ruta padre invalida.\n";
        return nullptr;
    }

    Nodo* nueva = new Nodo(ultimoId++, nombre, "carpeta");
    nueva->padre = padre;
    padre->hijos.push_back(nueva);

    trie.insertar(nombre);

    return nueva;
}

// Crear archivo
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

    trie.insertar(nombre);

    return nuevo;
}

// Autocompletar
vector<string> Arbol::autocompletar(const string& prefijo) {
    return trie.autocompletar(prefijo);
}

// Nodo → JSON
static json nodoAJson(Nodo* n) {
    json j;
    j["id"] = n->id;
    j["nombre"] = n->nombre;
    j["tipo"] = n->tipo;
    j["contenido"] = n->contenido;

    j["children"] = json::array();
    for (auto* h : n->hijos)
        j["children"].push_back(nodoAJson(h));

    return j;
}

// JSON → Nodo
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

// Guardar JSON
void Arbol::guardarJSON(const string& archivo) {
    json j;
    j["root"] = nodoAJson(raiz);
    j["ultimoId"] = ultimoId;

    ofstream out(archivo);
    out << j.dump(4);
    out.close();

    cout << "Guardado en " << archivo << endl;
}

// Cargar JSON
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

    raiz = jsonANodo(j["root"]);
    ultimoId = j["ultimoId"];

    cout << "Cargado desde " << archivo << endl;
}

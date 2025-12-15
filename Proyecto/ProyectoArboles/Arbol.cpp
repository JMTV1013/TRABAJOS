#include "Arbol.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// ---------- util ----------
static void liberarNodo(Nodo* n) {
    if (!n) return;
    for (auto* h : n->hijos)
        liberarNodo(h);
    delete n;
}

// ---------- constructor / destructor ----------
Arbol::Arbol() {
    raiz = new Nodo(0, "root", "carpeta");
    ultimoId = 1;
    indiceId[0] = raiz;
}

Arbol::~Arbol() {
    liberarNodo(raiz);
}

// ---------- operaciones existentes ----------
Nodo* Arbol::buscarRuta(const string& ruta) {
    if (ruta == "/" || ruta.empty())
        return raiz;

    stringstream ss(ruta);
    string seg;
    Nodo* actual = raiz;

    while (getline(ss, seg, '/')) {
        if (seg.empty()) continue;
        bool ok = false;
        for (auto* h : actual->hijos) {
            if (h->nombre == seg) {
                actual = h;
                ok = true;
                break;
            }
        }
        if (!ok) return nullptr;
    }
    return actual;
}

Nodo* Arbol::buscarPorId(int id) {
    if (indiceId.count(id))
        return indiceId[id];
    return nullptr;
}

Nodo* Arbol::crearCarpeta(const string& ruta, const string& nombre) {
    Nodo* padre = buscarRuta(ruta);
    if (!padre || padre->tipo != "carpeta") return nullptr;

    Nodo* n = new Nodo(ultimoId++, nombre, "carpeta");
    n->padre = padre;
    padre->hijos.push_back(n);

    indiceId[n->id] = n;
    trie.insertar(nombre);
    return n;
}

Nodo* Arbol::crearArchivo(const string& ruta, const string& nombre, const string& contenido) {
    Nodo* padre = buscarRuta(ruta);
    if (!padre || padre->tipo != "carpeta") return nullptr;

    Nodo* n = new Nodo(ultimoId++, nombre, "archivo");
    n->contenido = contenido;
    n->padre = padre;
    padre->hijos.push_back(n);

    indiceId[n->id] = n;
    trie.insertar(nombre);
    return n;
}

bool Arbol::eliminar(const string& ruta) {
    Nodo* n = buscarRuta(ruta);
    if (!n || n == raiz) return false;

    auto& v = n->padre->hijos;
    v.erase(remove(v.begin(), v.end(), n), v.end());
    papelera.push_back(n);
    return true;
}

bool Arbol::restaurar(int id) {
    for (auto it = papelera.begin(); it != papelera.end(); ++it) {
        if ((*it)->id == id) {
            raiz->hijos.push_back(*it);
            (*it)->padre = raiz;
            papelera.erase(it);
            return true;
        }
    }
    return false;
}

void Arbol::vaciarPapelera() {
    for (auto* n : papelera)
        liberarNodo(n);
    papelera.clear();
}

void Arbol::listarPapelera() {
    for (auto* n : papelera)
        cout << n->id << " - " << n->nombre << endl;
}

bool Arbol::mover(const string& o, const string& d) {
    Nodo* n = buscarRuta(o);
    Nodo* dest = buscarRuta(d);
    if (!n || !dest || dest->tipo != "carpeta") return false;

    auto& v = n->padre->hijos;
    v.erase(remove(v.begin(), v.end(), n), v.end());
    n->padre = dest;
    dest->hijos.push_back(n);
    return true;
}

bool Arbol::renombrar(const string& ruta, const string& nuevo) {
    Nodo* n = buscarRuta(ruta);
    if (!n) return false;
    n->nombre = nuevo;
    trie.insertar(nuevo);
    return true;
}

vector<string> Arbol::autocompletar(const string& prefijo) {
    return trie.autocompletar(prefijo);
}

// ---------- export ----------
static void preorden(Nodo* n, ofstream& out) {
    if (!n) return;
    out << n->id << " " << n->nombre << endl;
    for (auto* h : n->hijos)
        preorden(h, out);
}

void Arbol::exportarPreorden(ofstream& out) {
    preorden(raiz, out);
}

// =====================================================
// ==================== JSON ============================
// =====================================================

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

static Nodo* jsonANodo(const json& j, Nodo* padre, unordered_map<int, Nodo*>& indice) {
    Nodo* n = new Nodo(j["id"], j["nombre"], j["tipo"]);
    n->contenido = j["contenido"];
    n->padre = padre;
    indice[n->id] = n;

    for (auto& hijo : j["children"]) {
        Nodo* h = jsonANodo(hijo, n, indice);
        n->hijos.push_back(h);
    }
    return n;
}

void Arbol::guardarJSON(const string& archivo) {
    json j;
    j["ultimoId"] = ultimoId;
    j["root"] = nodoAJson(raiz);

    ofstream out(archivo);
    out << j.dump(4);
    out.close();
}

void Arbol::cargarJSON(const string& archivo) {
    ifstream in(archivo);
    if (!in.is_open()) return;

    json j;
    in >> j;
    in.close();

    liberarNodo(raiz);
    indiceId.clear();
    papelera.clear();

    raiz = jsonANodo(j["root"], nullptr, indiceId);
    ultimoId = j["ultimoId"];
}

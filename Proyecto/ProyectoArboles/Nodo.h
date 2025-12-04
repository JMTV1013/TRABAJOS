#ifndef NODO_H
#define NODO_H

#include <string>
#include <vector>
using namespace std;

struct Nodo {
    int id;
    string nombre;
    string tipo;    // el tipo puede ser carpeta o archivo
    string contenido;
    vector<Nodo*> hijos;
    Nodo* padre;

    Nodo(int id, const string& nombre, const string& tipo)
        : id(id), nombre(nombre), tipo(tipo), contenido(""), padre(nullptr) {
    }
};

#endif

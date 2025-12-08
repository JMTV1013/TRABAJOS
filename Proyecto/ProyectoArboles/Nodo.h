#ifndef NODO_H
#define NODO_H

#include <string>
#include <vector>

using namespace std;

struct Nodo {
    int id;
    string nombre;
    string tipo;       // carpeta o archivo
    string contenido;

    Nodo* padre;
    vector<Nodo*> hijos;

    Nodo(int _id, const string& _nombre, const string& _tipo)
        : id(_id), nombre(_nombre), tipo(_tipo), padre(nullptr) {
    }
};

#endif

#include <iostream>
#include "Arbol.h"

using namespace std;

int main() {
    cout << "Proyecto Árboles - Día 2\n";

    Arbol arbol;

    if (arbol.getRaiz() != nullptr) {
        cout << "Raíz creada: " << arbol.getRaiz()->nombre << "\n";
    }

    cout << "Buscando '/': ";
    auto* r1 = arbol.buscarRuta("/");
    cout << (r1 ? "Encontrado\n" : "No encontrado\n");

    cout << "Buscando '/root': ";
    auto* r2 = arbol.buscarRuta("/root");
    cout << (r2 ? "Encontrado\n" : "No encontrado\n");

    cout << "Buscando '/CarpetaFake': ";
    auto* r3 = arbol.buscarRuta("/CarpetaFake");
    cout << (r3 ? "Encontrado\n" : "No encontrado\n");

    return 0;
}

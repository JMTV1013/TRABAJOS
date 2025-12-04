#include <iostream>
#include "Arbol.h"


using namespace std;
int main() {
    cout << "Proyecto Árboles - Día 1\n";

    Arbol arbol;
    cout << "Raíz creada con nombre: "
        << arbol.getRaiz()->nombre
        << std::endl;

    return 0;
}

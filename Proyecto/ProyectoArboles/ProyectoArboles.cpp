#include <iostream>
#include "Arbol.h"

using namespace std;

int main() {
    Arbol arbol;

    // Crear algunos nodos
    arbol.crearCarpeta("/", "Documentos");
    arbol.crearCarpeta("/Documentos", "Tareas");
    arbol.crearArchivo("/Documentos/Tareas", "tarea1.txt", "texto prueba");
    arbol.crearArchivo("/Documentos/Tareas", "tarjeta.png", "imagen");
    arbol.crearArchivo("/Documentos/Tareas", "tabla.xlsx", "hoja cálculo");

    // Prueba de autocompletado
    cout << "\nAutocompletando 'ta':\n";
    vector<string> r = arbol.autocompletar("ta");
    for (auto& x : r)
        cout << "  - " << x << endl;

    // Guardar
    arbol.guardarJSON("arbol.json");

    // Cargar
    arbol.cargarJSON("arbol.json");

    return 0;
}

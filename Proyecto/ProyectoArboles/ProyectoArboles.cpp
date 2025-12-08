#include <iostream>
#include "Arbol.h"

using namespace std;

int main() {
    Arbol arbol;

    // Día 3 — Crear carpetas y archivos
    arbol.crearCarpeta("/", "Documentos");
    arbol.crearCarpeta("/Documentos", "Tareas");
    arbol.crearArchivo("/Documentos/Tareas", "tarea1.txt", "Contenido de prueba");

    // Guardar
    arbol.guardarJSON("arbol.json");

    // Cargar
    arbol.cargarJSON("arbol.json");

    return 0;
}

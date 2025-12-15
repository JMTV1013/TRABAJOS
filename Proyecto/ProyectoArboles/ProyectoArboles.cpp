#include <iostream>
#include <sstream>
#include <fstream>
#include "Arbol.h"

using namespace std;

int main() {
    Arbol arbol;
    string linea;

    // 🔹 Cargar el árbol desde JSON al iniciar
    arbol.cargarJSON("datos.json");

    while (true) {
        cout << "> ";
        getline(cin, linea);
        stringstream ss(linea);
        string cmd;
        ss >> cmd;

        if (cmd == "exit") {
            // 🔹 Guardar el árbol en JSON antes de salir
            arbol.guardarJSON("datos.json");
            break;
        }

        else if (cmd == "help") {
            cout << "Comandos disponibles:\n";
            cout << "  mkdir <ruta> <nombre>          - Crear carpeta\n";
            cout << "  touch <ruta> <nombre> <texto>  - Crear archivo\n";
            cout << "  rm <ruta>                      - Eliminar nodo (va a papelera)\n";
            cout << "  trash                          - Mostrar papelera\n";
            cout << "  restore <id>                   - Restaurar nodo de papelera\n";
            cout << "  mv <origen> <destino>          - Mover nodo\n";
            cout << "  search <prefijo>               - Autocompletar nombres\n";
            cout << "  export <archivo>               - Exportar árbol en preorden\n";
            cout << "  exit                           - Salir del programa\n";
        }

        else if (cmd == "mkdir") {
            string r, n;
            ss >> r >> n;
            arbol.crearCarpeta(r, n);
        }
        else if (cmd == "touch") {
            string r, n, c;
            ss >> r >> n;
            getline(ss, c);
            arbol.crearArchivo(r, n, c);
        }
        else if (cmd == "rm") {
            string r;
            ss >> r;
            arbol.eliminar(r);
        }
        else if (cmd == "trash") {
            arbol.listarPapelera();
        }
        else if (cmd == "restore") {
            int id;
            ss >> id;
            arbol.restaurar(id);
        }
        else if (cmd == "mv") {
            string o, d;
            ss >> o >> d;
            arbol.mover(o, d);
        }
        else if (cmd == "search") {
            string p;
            ss >> p;
            for (auto& s : arbol.autocompletar(p))
                cout << s << endl;
        }
        else if (cmd == "export") {
            string f;
            ss >> f;
            ofstream out(f);
            arbol.exportarPreorden(out);
        }
        else {
            cout << "Comando no reconocido. Escribe 'help' para ver los comandos disponibles.\n";
        }
    }

    return 0;
}

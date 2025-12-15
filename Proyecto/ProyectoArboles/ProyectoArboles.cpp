#include <iostream>
#include <sstream>
#include <fstream>
#include "Arbol.h"

using namespace std;

int main() {
    Arbol arbol;
    string linea;

    while (true) {
        cout << "> ";
        getline(cin, linea);
        stringstream ss(linea);
        string cmd;
        ss >> cmd;

        if (cmd == "exit") break;
        else if (cmd == "mkdir") {
            string r, n; ss >> r >> n;
            arbol.crearCarpeta(r, n);
        }
        else if (cmd == "touch") {
            string r, n, c; ss >> r >> n;
            getline(ss, c);
            arbol.crearArchivo(r, n, c);
        }
        else if (cmd == "rm") {
            string r; ss >> r;
            arbol.eliminar(r);
        }
        else if (cmd == "trash") {
            arbol.listarPapelera();
        }
        else if (cmd == "restore") {
            int id; ss >> id;
            arbol.restaurar(id);
        }
        else if (cmd == "mv") {
            string o, d; ss >> o >> d;
            arbol.mover(o, d);
        }
        else if (cmd == "search") {
            string p; ss >> p;
            for (auto& s : arbol.autocompletar(p))
                cout << s << endl;
        }
        else if (cmd == "export") {
            string f; ss >> f;
            ofstream out(f);
            arbol.exportarPreorden(out);
        }
    }
    return 0;
}

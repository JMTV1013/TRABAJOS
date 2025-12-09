using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        ArbolBinarioBusqueda arbol = new ArbolBinarioBusqueda();
        string comando;

        Console.WriteLine("=== Gestor de Números con Árbol Binario de Búsqueda ===");
        Console.WriteLine("Escribe 'ayuda' para ver los comandos.");

        do
        {
            Console.Write("> ");
            comando = Console.ReadLine().Trim().ToLower();

            switch (comando)
            {
                case "insertar":
                    Console.Write("Número a insertar: ");
                    if (int.TryParse(Console.ReadLine(), out int ins))
                    {
                        arbol.Insertar(ins);
                        Console.WriteLine("Insertado.");
                    }
                    break;

                case "buscar":
                    Console.Write("Número a buscar: ");
                    if (int.TryParse(Console.ReadLine(), out int busc))
                    {
                        if (arbol.Buscar(busc, out List<int> ruta))
                            Console.WriteLine("Encontrado. Ruta: " + string.Join(" -> ", ruta));
                        else
                            Console.WriteLine("No encontrado. Ruta recorrida: " + string.Join(" -> ", ruta));
                    }
                    break;

                case "eliminar":
                    Console.Write("Número a eliminar: ");
                    if (int.TryParse(Console.ReadLine(), out int del))
                    {
                        arbol.Eliminar(del);
                        Console.WriteLine("Eliminado (si existía).");
                    }
                    break;

                case "inorden":
                    arbol.Inorden();
                    break;

                case "preorden":
                    arbol.Preorden();
                    break;

                case "posorden":
                    arbol.Posorden();
                    break;

                case "altura":
                    Console.WriteLine("Altura: " + arbol.Altura());
                    break;

                case "tamano":
                    Console.WriteLine("Tamaño: " + arbol.Tamano());
                    break;

                case "exportar":
                    Console.Write("Nombre del archivo: ");
                    string archivo = Console.ReadLine();
                    arbol.ExportarInorden(archivo);
                    Console.WriteLine("Archivo exportado.");
                    break;

                case "ayuda":
                    Console.WriteLine("Comandos:");
                    Console.WriteLine(" insertar, buscar, eliminar");
                    Console.WriteLine(" inorden, preorden, posorden");
                    Console.WriteLine(" altura, tamano");
                    Console.WriteLine(" exportar");
                    Console.WriteLine(" salir");
                    break;

                case "salir":
                    break;

                default:
                    Console.WriteLine("Comando no reconocido.");
                    break;
            }

        } while (comando != "salir");

        Console.WriteLine("Saliendo...");
    }
}

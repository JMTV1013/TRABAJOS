using System;

class BatallaNaval
{
    // aqui hago el tablero, es una cuadricula 10x10 con "~" que es agua
    static string[,] tablero = new string[10, 10];

    static void Main()
    {
        // se llen ael tablero con "agua"
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                tablero[i, j] = "~";
            }
        }

        // primero muestro el tablero vacio
        Console.WriteLine("Tablero vacio:");
        MostrarTablero();

        // pongo un portaaviones de 5 casillas
        Console.WriteLine("\nPorta aviones:");
        ColocarBarco(2, 3, 5, "H");
        MostrarTablero();

        // pongo un submarino de 3 casillas
        Console.WriteLine("\nSubmarino:");
        ColocarBarco(5, 5, 3, "V");
        MostrarTablero();

        Console.ReadKey();
    }

    // esta funcion muestra el tablero en la consola
    static void MostrarTablero()
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                Console.Write(tablero[i, j] + " ");
            }
            Console.WriteLine();
        }
    }

    // esta funcion coloca un barco en el tablero
    // primero = fila donde empieza
    // Segundo = columna donde empieza
    // tercero = de cuantas casillas es el barco
    // cuarto = orientacion "H" horizontal o "V" vertical
    static void ColocarBarco(int fila, int col, int tamaño, string orientacion)
    {
        if (orientacion == "H")
        {
            // si es horizontal se mueve en columnas
            for (int j = 0; j < tamaño; j++)
            {
                tablero[fila, col + j] = "O"; // "O" simboliza lo que mide el barco
            }
        }
        else if (orientacion == "V")
        {
            // si es vertical se mueve en filas
            for (int i = 0; i < tamaño; i++)
            {
                tablero[fila + i, col] = "O";
            }
        }
    }
}

using System;

namespace BatallaNaval
{
    class Program
    {
        const int TAM = 8; // tamaño del tablero 8x8

        // funcion para crear tablero lleno de '-'
        static char[,] CrearTablero(int tamaño)
        {
            char[,] tablero = new char[tamaño, tamaño];
            for (int i = 0; i < tamaño; i++)
                for (int j = 0; j < tamaño; j++)
                    tablero[i, j] = '-';
            return tablero;
        }

        // funcion para mostrar el tablero
        // si mostrarBarcos es falso no enseña los barcos
        static void MostrarTablero(char[,] tablero, bool mostrarBarcos)
        {
            for (int i = 0; i < tablero.GetLength(0); i++)
            {
                for (int j = 0; j < tablero.GetLength(1); j++)
                {
                    if (tablero[i, j] == 'B' && !mostrarBarcos)
                        Console.Write("- ");
                    else
                        Console.Write(tablero[i, j] + " ");
                }
                Console.WriteLine();
            }
        }

        // en esta parte coloco un barco en el tablero
        static void ColocarBarco(char[,] tablero, int tamañoBarco)
        {
            int fila, col;
            char orientacion;

            while (true)
            {
                Console.Write("fila inicial (0-" + (tablero.GetLength(0) - 1) + "): ");
                fila = int.Parse(Console.ReadLine());

                Console.Write("columna inicial (0-" + (tablero.GetLength(1) - 1) + "): ");
                col = int.Parse(Console.ReadLine());

                Console.Write("horizontal (h) o vertical (v): ");
                orientacion = char.Parse(Console.ReadLine().ToLower());

                // si es horizontal verifico que no se salga ni se encime
                if (orientacion == 'h' && col + tamañoBarco <= tablero.GetLength(1) && fila >= 0 && fila < tablero.GetLength(0))
                {
                    bool libre = true;
                    for (int i = 0; i < tamañoBarco; i++)
                        if (tablero[fila, col + i] == 'B') libre = false;

                    if (libre)
                    {
                        for (int i = 0; i < tamañoBarco; i++)
                            tablero[fila, col + i] = 'B';
                        break;
                    }
                    else
                        Console.WriteLine("ya hay un barco en esa posicion\n");
                }
                // si es vertical verifico filas
                else if (orientacion == 'v' && fila + tamañoBarco <= tablero.GetLength(0) && col >= 0 && col < tablero.GetLength(1))
                {
                    bool libre = true;
                    for (int i = 0; i < tamañoBarco; i++)
                        if (tablero[fila + i, col] == 'B') libre = false;

                    if (libre)
                    {
                        for (int i = 0; i < tamañoBarco; i++)
                            tablero[fila + i, col] = 'B';
                        break;
                    }
                    else
                        Console.WriteLine("ya hay un barco en esa posicion\n");
                }
                else
                    Console.WriteLine("posicion invalida, intenta de nuevo\n");
            }
        }

        // funcion disparar: revisa si se le dio a un barco o no
        static int Disparar(char[,] tablero, int barcosRestantes)
        {
            int fila, col;

            while (true)
            {
                Console.Write("fila a disparar: ");
                fila = int.Parse(Console.ReadLine());

                Console.Write("columna a disparar: ");
                col = int.Parse(Console.ReadLine());

                if (fila >= 0 && fila < tablero.GetLength(0) && col >= 0 && col < tablero.GetLength(1))
                    break;
                else
                    Console.WriteLine("posicion invalida, intenta de nuevo\n");
            }

            if (tablero[fila, col] == 'B')
            {
                Console.WriteLine("acertaste!");
                tablero[fila, col] = 'X';
                barcosRestantes--;
            }
            else if (tablero[fila, col] == '-')
            {
                Console.WriteLine("no se acerto");
                tablero[fila, col] = 'O';
            }
            else
            {
                Console.WriteLine("ya disparaste aqui");
            }

            return barcosRestantes;
        }

        static void Main()
        {
            int[] tamañosBarcos = { 3, 4, 5 };

            // creo tableros para ambos jugadores
            char[,] tableroJugador1 = CrearTablero(TAM);
            char[,] tableroJugador2 = CrearTablero(TAM);

            // jugador 1 coloca barcos
            Console.WriteLine("jugador 1: coloca tus barcos");
            MostrarTablero(tableroJugador1, true);
            foreach (int barco in tamañosBarcos)
            {
                Console.WriteLine("\ncoloca un barco de tamaño " + barco);
                ColocarBarco(tableroJugador1, barco);
                MostrarTablero(tableroJugador1, true);
            }

            Console.Clear();

            // jugador 2 coloca barcos
            Console.WriteLine("jugador 2: coloca tus barcos");
            MostrarTablero(tableroJugador2, true);
            foreach (int barco in tamañosBarcos)
            {
                Console.WriteLine("\ncoloca un barco de tamaño " + barco);
                ColocarBarco(tableroJugador2, barco);
                MostrarTablero(tableroJugador2, true);
            }

            Console.Clear();

            int barcosRestantes1 = 3 + 4 + 5;
            int barcosRestantes2 = 3 + 4 + 5;
            bool turnoJugador1 = true;

            // bucle de turnos
            while (barcosRestantes1 > 0 && barcosRestantes2 > 0)
            {
                if (turnoJugador1)
                {
                    Console.WriteLine("\nturno del jugador 1");
                    MostrarTablero(tableroJugador2, false);
                    barcosRestantes2 = Disparar(tableroJugador2, barcosRestantes2);
                }
                else
                {
                    Console.WriteLine("\nturno del jugador 2");
                    MostrarTablero(tableroJugador1, false);
                    barcosRestantes1 = Disparar(tableroJugador1, barcosRestantes1);
                }
                turnoJugador1 = !turnoJugador1;
            }

            // resultado final
            if (barcosRestantes1 == 0)
                Console.WriteLine("\njugador 2 gana!");
            else
                Console.WriteLine("\njugador 1 gana!");

            Console.WriteLine("\ntablero final jugador 1:");
            MostrarTablero(tableroJugador1, true);
            Console.WriteLine("\ntablero final jugador 2:");
            MostrarTablero(tableroJugador2, true);

            Console.WriteLine("\npresiona una tecla para salir...");
            Console.ReadKey();
        }
    }
}

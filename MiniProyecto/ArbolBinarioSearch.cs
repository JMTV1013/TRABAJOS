using System;
using System.Collections.Generic;
using System.IO;

public class ArbolBinarioBusqueda
{
    public Nodo Raiz;

    // Insertar
    public void Insertar(int clave)
    {
        Raiz = InsertarRec(Raiz, clave);
    }

    private Nodo InsertarRec(Nodo raiz, int clave)
    {
        if (raiz == null)
            return new Nodo(clave);

        if (clave < raiz.Clave)
            raiz.Izquierda = InsertarRec(raiz.Izquierda, clave);
        else if (clave > raiz.Clave)
            raiz.Derecha = InsertarRec(raiz.Derecha, clave);

        return raiz;
    }

    // Buscar con ruta
    public bool Buscar(int clave, out List<int> ruta)
    {
        ruta = new List<int>();
        Nodo actual = Raiz;

        while (actual != null)
        {
            ruta.Add(actual.Clave);

            if (clave == actual.Clave)
                return true;

            if (clave < actual.Clave)
                actual = actual.Izquierda;
            else
                actual = actual.Derecha;
        }

        return false;
    }

    // Eliminar
    public void Eliminar(int clave)
    {
        Raiz = EliminarRec(Raiz, clave);
    }

    private Nodo EliminarRec(Nodo raiz, int clave)
    {
        if (raiz == null)
            return raiz;

        if (clave < raiz.Clave)
            raiz.Izquierda = EliminarRec(raiz.Izquierda, clave);
        else if (clave > raiz.Clave)
            raiz.Derecha = EliminarRec(raiz.Derecha, clave);
        else
        {
            // Caso 1: Nodo hoja
            if (raiz.Izquierda == null && raiz.Derecha == null)
                return null;

            // Caso 2: Un solo hijo
            if (raiz.Izquierda == null)
                return raiz.Derecha;
            if (raiz.Derecha == null)
                return raiz.Izquierda;

            // Caso 3: Dos hijos
            Nodo sucesor = Minimo(raiz.Derecha);
            raiz.Clave = sucesor.Clave;
            raiz.Derecha = EliminarRec(raiz.Derecha, sucesor.Clave);
        }

        return raiz;
    }

    private Nodo Minimo(Nodo nodo)
    {
        while (nodo.Izquierda != null)
            nodo = nodo.Izquierda;
        return nodo;
    }

    // Recorridos
    public void Inorden()
    {
        InordenRec(Raiz);
        Console.WriteLine();
    }

    private void InordenRec(Nodo raiz)
    {
        if (raiz == null) return;
        InordenRec(raiz.Izquierda);
        Console.Write(raiz.Clave + " ");
        InordenRec(raiz.Derecha);
    }

    public void Preorden()
    {
        PreordenRec(Raiz);
        Console.WriteLine();
    }

    private void PreordenRec(Nodo raiz)
    {
        if (raiz == null) return;
        Console.Write(raiz.Clave + " ");
        PreordenRec(raiz.Izquierda);
        PreordenRec(raiz.Derecha);
    }

    public void Posorden()
    {
        PosordenRec(Raiz);
        Console.WriteLine();
    }

    private void PosordenRec(Nodo raiz)
    {
        if (raiz == null) return;
        PosordenRec(raiz.Izquierda);
        PosordenRec(raiz.Derecha);
        Console.Write(raiz.Clave + " ");
    }

    // Altura
    public int Altura()
    {
        return AlturaRec(Raiz);
    }

    private int AlturaRec(Nodo nodo)
    {
        if (nodo == null) return -1;
        return 1 + Math.Max(AlturaRec(nodo.Izquierda), AlturaRec(nodo.Derecha));
    }

    // Tamaño
    public int Tamano()
    {
        return TamanoRec(Raiz);
    }

    private int TamanoRec(Nodo nodo)
    {
        if (nodo == null) return 0;
        return 1 + TamanoRec(nodo.Izquierda) + TamanoRec(nodo.Derecha);
    }

    // Exportar inorden
    public void ExportarInorden(string archivo)
    {
        List<int> lista = new List<int>();
        RecopilarInorden(Raiz, lista);
        File.WriteAllLines(archivo, lista.ConvertAll(x => x.ToString()));
    }

    private void RecopilarInorden(Nodo raiz, List<int> lista)
    {
        if (raiz == null) return;
        RecopilarInorden(raiz.Izquierda, lista);
        lista.Add(raiz.Clave);
        RecopilarInorden(raiz.Derecha, lista);
    }
}

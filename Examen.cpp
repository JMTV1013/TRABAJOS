#include <iostream>

using namespace std;

int main()
{
    int prom[9];
    int suma = 0, promediototal = 0, x;
    int mayor = 0, menor = 10;

    for (x = 0; x < 10; ++x){
        cout << "Dame el promedio [" << x + 1 << "]: ";
        cin >> prom[x];
        suma = suma + prom[x];
        if (mayor < prom[x]){
            mayor = prom[x];
        }
        if (menor > prom[x]){
            menor = prom[x];
        }
    }

    promediototal = (suma / 10);

    cout << "\nEl promedio total es de: " << promediototal;
    cout << "\nEl numero mayor es: " << mayor;
    cout << "\nEl numero menor es: " << menor;

    return 0;
}
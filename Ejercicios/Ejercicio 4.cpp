#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string frase; 
    string token;

    cout << "Ingrese una frase: ";
    getline(cin, frase);

    // Paso 1: contar palabras
    stringstream ss1(frase);
    int contador = 0;
    while (ss1 >> token) {
        contador++;
    }

    // Paso 2: crear arreglo dinámico
    string* palabras = new string[contador];

    // Paso 3: volver a tokenizar y guardar
    stringstream ss2(frase);
    int i = 0;
    while (ss2 >> token) {
        palabras[i] = token;
        i++;
    }

    // Mostrar todas las palabras
    cout << "Palabras ingresadas:" << endl;
    for (int j = 0; j < contador; j++) {
        cout << j << ": " << palabras[j] << endl;
    }

    // Elegir palabra por índice
    int indice;
    cout << "Ingrese el índice de la palabra que quiere ver: ";
    cin >> indice;

    if (indice >= 0 && indice < contador) {
        cout << "La palabra en el índice " << indice 
             << " es: " << palabras[indice] << endl;
    } else {
        cout << "Índice fuera de rango." << endl;
    }

    // Liberar memoria
    delete[] palabras;

    return 0;
}

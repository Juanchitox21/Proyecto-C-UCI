#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char frase[256] = "awto";
    
    int inicio = 0;
    int fin = strlen(frase) - 1; // último índice válido

    while (inicio < fin) {
        char temp = frase[inicio];
        frase[inicio] = frase[fin];
        frase[fin] = temp;

        inicio++;
        fin--;
    }

    cout << "La frase invertida es: " << frase << endl;
    return 0;
}
    
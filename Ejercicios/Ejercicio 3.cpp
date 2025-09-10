#include <iostream>
#include <cstring>
using namespace std;

int main(){

    char palabra[50];

    cout << "Ingrese una palabra" << endl;
    cin.getline(palabra, 50);

    cout << "La longitud de la palabra es de: " << " " <<  strlen(palabra) << "Contando espacios "<<  endl;
}
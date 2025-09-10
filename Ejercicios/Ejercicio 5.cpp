#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char Nombre [50];
    char Apellido [50];

    cout << "Ingrese el nombre" << endl;
    cin.getline(Nombre, 50);

    cout << "Ingrese el apelldio" << endl;
    cin.getline(Apellido, 50);

    strcat(Nombre, Apellido);

    cout << "El nombre y el apellido es :" << Nombre;

}
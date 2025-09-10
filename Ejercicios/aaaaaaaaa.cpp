#include <iostream>
using namespace std;

struct libro{
    char titulo[50];
    char autor[50];
    int precio;
};

int main(){

    libro lib1= {"Valentina MANCA","Juan_Quintero",100};

    libro* plib1 = &lib1;

    cout << "El titulo del libro es; " << plib1 -> titulo << endl;
    cout << "El autor del libro es; " << plib1 -> autor << endl;
    cout << "El precio del libro es; " << plib1 -> precio << endl;
    

    plib1 -> precio = 10;
    plib1 -> titulo = "JQ LA VERGA";

    cout << "El titulo del libro es; " << plib1 -> titulo << endl;
    cout << "El autor del libro es; " << plib1 -> autor << endl;
    cout << "El precio del libro es; " << plib1 -> precio << endl;


    return 0;
}
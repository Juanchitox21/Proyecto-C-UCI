#include <iostream>
#include <sstream>
using namespace std;

int main(){

    string frase; 
    string token;
     
    cout << "Ingrese una frase" << endl;
    getline(cin, frase);

    stringstream ss(frase);

    while (ss >> token){
        cout << token << endl;
    }
    



}
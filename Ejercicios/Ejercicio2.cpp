#include <iostream>
using namespace std;

void cargarventas(float ventas[3][4]){
    for(int i = 0;i < 3 ;i++){     
        for(int j = 0; j < 4; j++){
            cout << "Ingrese las ventas de la sucursal " << i + 1 << " y del trimestre " << j + 1 << " :"<< endl;
            cin >> ventas [i][j];
            }
    }
}
float calcularTotalventas(float ventas[3][4]){
    float suma=0;
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            suma = suma + ventas[i][j];   
        }
    }
    return suma;
}

float calcularPromedioTrimestre(float ventas [3][4], int trimestre){
    float suma_Trimestre = 0;
    
    for (int i = 0; i < 3; i++){
        suma_Trimestre+= ventas[i][trimestre];
        
    }
    return suma_Trimestre/3.0;
}

void mostrarventas(float ventas [3][4]){
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 4; j++){
            cout << "Las ventas de la sucursal: " << i + 1 << " " << "en el trimestre: " << j + 1 <<" "<<"fueron de: " << ventas[i][j] << endl;
        }
        
    }
} 
int main()
{
    float ventas[3][4];
    cargarventas(ventas);
    mostrarventas(ventas);
    float total = calcularTotalventas(ventas);
    cout << "El total de las ventas fue de"<< " " << total << endl;
     for (int j = 0; j < 4; j++) {
        float promedio = calcularPromedioTrimestre(ventas, j);
        cout << "Promedio del trimestre " << j + 1 << ": " << promedio << endl;
    }

    return 0;
}



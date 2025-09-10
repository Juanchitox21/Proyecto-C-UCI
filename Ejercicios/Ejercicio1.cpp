#include <iostream>
using namespace std;


int main()
{

    struct estudiante{
        string  nombre;
        int edad;
        float notas[3];
        float promedio;
    };

    estudiante estudiantes[5];

    for(int i = 0 ; i < 5 ; i++){

        cout << "Ingrese el nombre del estudiante" << i+1 << endl;
        cin >> estudiantes[i].nombre;
        cout << "Ingrese la edad del estudiante " << i+1 << endl;
        cin >> estudiantes[i].edad;
                                                        
        float suma = 0;

        for (int j = 0; j < 3; j++){
            cout << "Ingrese la nota" << j+1 << " del estudiante "<< i+1 << endl;
            cin >> estudiantes[i].notas[j];
            suma+= estudiantes[i].notas[j];
        }
        estudiantes[i].promedio = suma/3;
    }
    cout << "RESULTADOS" << endl;
    for(int i = 0; i < 5; i++){
        cout << "Estudiante:" << " " << estudiantes[i].nombre << endl;
        cout << "Edad:" << " " <<  estudiantes[i].edad << endl;
        cout << "Promedio:" << " " << estudiantes[i].promedio << endl;
    }

    return 0;
}
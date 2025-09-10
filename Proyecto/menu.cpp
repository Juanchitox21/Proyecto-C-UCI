#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Estructuras.h"
#include "Funciones.h"

using namespace std;

void ImprimirMenu();
int main() {
char opcion;
ArchivoConfig config;
ArchivoPacientes pacientes;
pacientes.pacientes=nullptr;
SalaUCI* Datos=nullptr;
char nombreArchivo[]="patient_readings_simulation_tiny.bsf";
do {
    
    ImprimirMenu();
    cout << "Ingrese una opción(1-6): ";
    cin >> opcion;

    switch (opcion) {
        case '1':
        if(pacientes.pacientes == nullptr){
            cout << "Cargar archivo de configuración y datos de pacientes." << endl;
            config = Leer_archivo_configuracion("configuracion.txt");
            pacientes = Leer_archivo_pacientes("pacientes_small.csv");
            cout << "Archivos cargados exitosamente." << endl;
    }else{
        cout<<"Los archivos ya han sido cargados"<<endl;
    }
            break;
        case '2':
        if(Datos == nullptr){
            cout << "Leer archivo .bsf." << endl;
            Datos=Leer_archivo_binario(nombreArchivo);
            if(Datos != nullptr)
            {
                cout<<"Lectura exitosa del archivo binario"<<endl;
            }else{
                cout<<"Error al leer el archivo"<<endl;
            }
        }else{
            cout<<"El archivo ya ha sido leido"<<endl;
        }
            break;
        
        case '3':
            cout << "Generar reporte de anomalías." << endl;
             if(Datos != nullptr) {
                 for(int i = 0 ; i < (int)Datos->numero_maquinas ; i++) {
                     Detectar_anomalias_paciente(Datos->maquinas[i], config);
                     Generar_reporte_paciente(Datos->maquinas[i], config);
                 }
                 generar_reportes_de_anomalias(Datos, config);
                 Generar_archivo_binario_anomalias_ECG(Datos, config);
                 cout<<"Los reportes han sido creados correctamente"<<endl;
             } else {
                 cout << "Error al leer el archivo binario." << endl;
             }
            break;
        case '4':{
            cout << "Calcular estadísticas." << endl;
                        if(Datos != nullptr) {
                    cout << "=== Estadísticas por máquina ===" << endl;
                    for (int i = 0; i < Datos->numero_maquinas; i++) {
                        cout << "Máquina " << (int)Datos->maquinas[i].id << endl;
                        for (int j = 0; j < Datos->maquinas[i].numero_mediciones; j++) {
                            for (int k = 0; k < Datos->maquinas[i].mediciones[j].numero_lecturas; k++) {
                                cout << "Paciente " << Datos->maquinas[i].mediciones[j].id_paciente 
                                    << " Sensor " << Datos->maquinas[i].mediciones[j].lecturas[k].tipo
                                    << " Valor: " << Datos->maquinas[i].mediciones[j].lecturas[k].valor[0];
                                if (Datos->maquinas[i].mediciones[j].lecturas[k].tipo== 'P') {
                                    cout << " / " << Datos->maquinas[i].mediciones[j].lecturas[k].valor[1];
                                }
                                cout << endl;
                            }
                        }
                    }
                }
            
}
                break;
            
        case '5':{
            cout << "Exportar datos procesados." << endl;
if(Datos != nullptr) {
                    ofstream out("exportados.csv");
                    if (!out.is_open()) {
                        cerr << "No se pudo abrir el archivo para exportar." << endl;
                    } else {
                        out << "ID_Maquina,ID_Paciente,Fecha,Sensor,Valor1,Valor2\n";
                        for (int i = 0; i < Datos->numero_maquinas; i++) {
                            for (int j = 0; j < Datos->maquinas[i].numero_mediciones; j++) {
                                for (int k = 0; k < Datos->maquinas[i].mediciones[j].numero_lecturas; k++) {
                                    out << (int)Datos->maquinas[i].id << ","
                                        << Datos->maquinas[i].mediciones[j].id_paciente << ","
                                        << Datos->maquinas[i].mediciones[j].fecha_hora << ","
                                        << Datos->maquinas[i].mediciones[j].lecturas[k].tipo << ","
                                        << Datos->maquinas[i].mediciones[j].lecturas[k].valor[0] << ",";
                                    if (Datos->maquinas[i].mediciones[j].lecturas[k].tipo == 'P') out << Datos->maquinas[i].mediciones[j].lecturas[k].valor[1];
                                    out << "\n";
                                }
                            }
                        }
                        out.close();
                        cout << "Datos exportados en: exportados.csv" << endl;
                    }
                    
                }

            break;
        }
        case '6':
            cout << "Salir del programa." << endl;
            Limpiar_apuntador(Datos);
            Limpiar_apuntadores_pacientes(pacientes.pacientes);
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
    }
} while (opcion != '6');
    return 0;   
}
void ImprimirMenu() {
    cout << "Menu principal:" << endl;
    cout << "1. Cargar archivo de configuración y datos de pacientes" << endl;
    cout << "2. Leer archivo .bsf" << endl;
    cout << "3. Generar reporte de anomalías" << endl;
    cout << "4. Calcular estadísticas" << endl;
    cout << "5. Exportar datos procesados" << endl;
    cout << "6. Salir" << endl;
}

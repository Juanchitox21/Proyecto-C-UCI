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
SalaUCI* Datos;
char nombreArchivo[]="patient_readings_simulation_tiny.bsf";
do {
    
    ImprimirMenu();
    cout << "Ingrese una opción(1-6): ";
    cin >> opcion;

    switch (opcion) {
        case '1':
            cout << "Cargar archivo de configuración y datos de pacientes." << endl;
            config = Leer_archivo_configuracion("configuracion.txt");
            pacientes = Leer_archivo_pacientes("pacientes_small.csv");
            cout << "Archivos cargados exitosamente." << endl;
            break;
        case '2':
            cout << "Leer archivo .bsf." << endl;
            Datos=Leer_archivo_binario(nombreArchivo);
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
             } else {
                 cout << "Error al leer el archivo binario." << endl;
             }
            break;
        case '4':{
            cout << "Calcular estadísticas." << endl;
                    Calcular_estadisticas_sensor(Datos);
                break;
            }
        case '5':{
            cout << "Exportar datos procesados." << endl;
                    Exportar_datos_procesados(Datos);
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

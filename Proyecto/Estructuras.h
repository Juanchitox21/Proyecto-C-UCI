#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>

using namespace std;

struct Lectura {
    char tipo;
    double valor[2];
    Lectura(){
        valor[0] = 0.0;
        valor[1] = 0.0;
    }
};
struct Medicion {
    char id_paciente[11];
    char fecha_hora[24];
    int numero_lecturas;
    Lectura* lecturas;
};
struct MaquinaUCI {
    char id;
    int numero_mediciones;
    Medicion* mediciones;
};
struct SalaUCI {
    char id;
    uint8_t numero_maquinas;
    MaquinaUCI* maquinas;
};
struct Umbral{
    char tipo[6];
    char inf[11];
    char sup[11];
};
struct ArchivoConfig {
    Umbral umbrales[5];
    int tamaño=0; 
};
struct Paciente {
    char id[4];
    char tipo_documento[3];
    char documento[11];
    char nombre[30];
    char apellido[30];
    char fecha_nacimiento[11];
    char telefono[11];
    char email[50];
    char tipo_sangre[4];
    char entidad_salud[20];
    char medicina_prepagada[20];
};
struct ArchivoPacientes {
    Paciente* pacientes;
    int tamaño=0;
};

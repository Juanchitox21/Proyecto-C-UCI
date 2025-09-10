#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>


using namespace std;

char* trim(char* str) {
    // Eliminar espacios al inicio
    while (isspace(*str)) str++;
    
    // Si toda la cadena era espacios
    if (*str == '\0') return str;
    
    // Eliminar espacios al final
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    // Escribir terminador
    *(end + 1) = '\0';
    
    return str;
}

bool Comparar_fechas(char fecha1[], char fecha2[]) 
{

    for(int i = 6; i <= 9; i++) {
        if(fecha1[i] > fecha2[i]) {
          return true;
        }else if(fecha1[i] < fecha2[i]) {
          return false;
        }
    }
    for(int i = 3; i <= 4; i++) {
        if(fecha1[i] > fecha2[i]) {
          return true;
        }else if(fecha1[i] < fecha2[i]) {
          return false;
        }
    }
    for(int i = 0; i <= 1; i++) {
        if(fecha1[i] > fecha2[i]) {
          return true;
        }else if(fecha1[i] < fecha2[i]) {
          return false;
        }
    }
    for(int i = 11; i <= 22; i++) {
      
        if(fecha1[i] > fecha2[i]) {
          return true;
        }else if(fecha1[i] < fecha2[i]) {
          return false;
        }
    }
    return false;

}

void Linea_archivo_configuracion(char line[], char tokens[3][10])
{
string token;
stringstream ss(line);
int TokenCount = 0;
while(getline(ss, token, ',')) {
    if(!token.empty()) {
        strcpy(tokens[TokenCount], token.c_str());
        TokenCount++;
        
    }
}
}

ArchivoConfig Ordenar_archiv_configuracion(char lines[][21])
{
ArchivoConfig config;
Umbral umbral;
char line[21];
for(int i = 0; i < 5 ; i++) {
    strcpy(line, lines[i]);
    char tokens[3][10];

    Linea_archivo_configuracion(line, tokens);
    strcpy(umbral.tipo, tokens[0]);
    strcpy(umbral.inf, tokens[1]);
    strcpy(umbral.sup, tokens[2]);
    config.umbrales[config.tamaño] = umbral;
    config.tamaño++;
    }
    return config;
}

void Linea_archivo_pacientes(char line[], char tokens[11][50])
{
  string token;
  string LineFromChar = line;
  stringstream ss(LineFromChar);
  int TokenCount = 0;
  while(getline(ss, token, ';')) {
    if(!token.empty()) {
        strcpy(tokens[TokenCount], token.c_str());
        strcpy(tokens[TokenCount],trim(tokens[TokenCount]));
        TokenCount++;
    }

}
}


ArchivoPacientes Ordenar_archivo_paciente(char** &lines, int &tamaño)
{
ArchivoPacientes Pacientes;
Pacientes.pacientes= new Paciente[tamaño];
Paciente Paciente;
char line[130];
for(int i = 0; i < tamaño; i++) {
    strcpy(line, lines[i]);
    char tokens[11][50];
    Linea_archivo_pacientes(line, tokens);
    strcpy(Paciente.id, tokens[0]);
    strcpy(Paciente.tipo_documento, tokens[1]);
    strcpy(Paciente.documento, tokens[2]);
    strcpy(Paciente.nombre, tokens[3]);
    strcpy(Paciente.apellido, tokens[4]);
    strcpy(Paciente.fecha_nacimiento, tokens[5]);
    strcpy(Paciente.telefono, tokens[6]);
    strcpy(Paciente.email, tokens[7]);
    strcpy(Paciente.tipo_sangre, tokens[8]);
    strcpy(Paciente.entidad_salud, tokens[9]);
    strcpy(Paciente.medicina_prepagada, tokens[10]);
    Pacientes.pacientes[Pacientes.tamaño] = Paciente;
    Pacientes.tamaño++;
    }
    return Pacientes;
}
//Punto 1 del taller 2
ArchivoConfig Leer_archivo_configuracion(const char* nombredelarchivo)
{
    ifstream archivo(nombredelarchivo);
    ArchivoConfig config;
    config.tamaño = 0;

    if(!archivo) { 
        cerr << "no se pudo abrir el archivo de configuracion." << endl;
        return config;

    }

    char line[21];
    char lines[50][21];
    int contador = 0;

    while(archivo.getline(line, sizeof(line))){
      if(strlen(line) > 0) {
        strcpy(lines[contador], line);
        contador++;
      }
    }
    archivo.close();

    for(int i = 0; i < contador; i++) {
      char tokens[3][10];
      Linea_archivo_configuracion(lines[i], tokens);
      Umbral umbral;
      strcpy(umbral.tipo, tokens[0]);
      strcpy(umbral.inf, tokens[1]);
      strcpy(umbral.sup, tokens[2]);

      config.umbrales[config.tamaño] = umbral;
      config.tamaño++;

    }

    cout << "Archivo de configuracion cargado con un total de umbrales de."<< config.tamaño << endl;
    return config;
}
void Agregar_fila(char** &lineas, int &filas) {
    char** temp = new char*[filas + 1];
    for (int i = 0; i < filas; i++) {
        temp[i] = new char[130];
        strcpy(temp[i], lineas[i]);
    }
    temp[filas] = new char[130];
    for(int i = 0; i < filas; i++) {
        delete[] lineas[i];
    }
    delete[] lineas;
    lineas = temp;
}
void Agregar_casilla(double* &valores, int &n) {
    double* temp = new double[n + 1];
    for (int i = 0; i < n; i++) {
        temp[i] = valores[i];
    }
    temp[n] = 0.0;
    delete[] valores;
    valores = temp;
}
void Limpiar_apuntador_char(char** lines, int numeroDeFilas) {

    if (lines == nullptr) {
        return;
    }
    for (int i = 0; i < numeroDeFilas; i++) {
            delete[] lines[i];
    }

    delete[] lines;
}
ArchivoPacientes Leer_archivo_pacientes(const char* nombredelarchivo)
{
    ifstream archivo(nombredelarchivo);
    ArchivoPacientes Pacientes;
    Pacientes.tamaño = 0;

    if(!archivo) { 
        cerr << "no se pudo abrir el archivo de pacientes." << endl;
        return Pacientes;
    }

    char line[130];
    char** lines= new char*[1];
    lines[0] = new char[130];
    int contador = 0;

    while(archivo.getline(line, sizeof(line))){
      if(strlen(trim(line)) > 0) {
        strcpy(lines[contador], line);
        contador++;
        Agregar_fila(lines, contador);
      }
    }

    archivo.close();

    Pacientes= Ordenar_archivo_paciente(lines, contador);
    cout << "El archivo de los pacientes ha sido cargado con un total de " << Pacientes.tamaño << endl;
    Limpiar_apuntador_char(lines, contador);
    return Pacientes;

}

void Limpiar_apuntadores_pacientes(Paciente* &pacientes) 
{
   delete[] pacientes;
   pacientes = nullptr;
}

//Punto 2 del taller 2
bool Es_anomalia(const char tipo[], double valor, const ArchivoConfig &config) {
    for (int i = 0; i < config.tamaño; i++) {
        if (strcmp(config.umbrales[i].tipo, tipo) == 0) {
            double inf = atof(config.umbrales[i].inf);
            double sup = atof(config.umbrales[i].sup);
            if (valor < inf || valor > sup) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void Detectar_anomalias_paciente(const MaquinaUCI &maquina, const ArchivoConfig &config) {
    for (int i = 0; i < maquina.numero_mediciones; i++) {
        Medicion medicion = maquina.mediciones[i];

        for (int j = 0; j < medicion.numero_lecturas; j++) {
            Lectura lectura = medicion.lecturas[j];

            char tipoSensor[6];
            tipoSensor[0] = lectura.tipo;
            tipoSensor[1] = '\0';

            if (strcmp(tipoSensor, "E") != 0) { 
                if (Es_anomalia(tipoSensor, lectura.valor[0], config)) {
                    cout << "Paciente " << medicion.id_paciente << " - " 
                         << tipoSensor << " (" << lectura.valor[0] << "): Anomalia" << endl;
                } else {
                    cout << "Paciente " << medicion.id_paciente << " - " 
                         << tipoSensor << " (" << lectura.valor[0] << "): Normal" << endl;
                }
            } else {
                cout << "Paciente " << medicion.id_paciente << " - ECG (" 
                     << lectura.valor[0] << ")" << endl;
            }
        }
    }
}
//Punto 3 del taller 2
void Generar_reporte_paciente(const MaquinaUCI &maquina, const ArchivoConfig & config) {
	double suma = 0;
	if(maquina.numero_mediciones == 0) {
		cout << "No hay mediciones para generar el reporte." << endl;
		return;
	}

	char nombreArchivo[80];

	nombreArchivo[0] = '\0';
	strcat(nombreArchivo, "mediciones_paciente");
	strcat(nombreArchivo, maquina.mediciones[0].id_paciente);
	strcat(nombreArchivo, ".txt");

	ofstream archivo(nombreArchivo);
	if (!archivo) {
		cout << "Error al crear el archivo de reporte." << endl;
		return;
	}

	archivo << "Reporte de mediciones del paciente" << maquina.mediciones[0].id_paciente << endl;

	char tipos[10];
	int NumTipos = 0;

	for (int i = 0; i < maquina.numero_mediciones; i++) {
		    Medicion &m = maquina.mediciones[i];
		for (int j = 0; j < m.numero_lecturas; j++) {
			char t = m.lecturas[j].tipo;
			bool existe = false;
			for (int k = 0; k < NumTipos; k++) {
				if (tipos[k] == t) {
					existe = true;
					break;
				}
			}
			if (!existe) {
				if (NumTipos < 10) {
					tipos[NumTipos] = t;
					NumTipos++;
				}
			}
		}
	}
        char** fechas= new char*[1];
        fechas[0]=new char[24];
		double* valores= new double[1];
		int n = 0;
	for(int s = 0; s < NumTipos; s++) {
		char sensor = tipos[s];
		archivo << "Sensor:" << sensor << endl;

    suma =0.0;
		

		for(int i = 0; i < maquina.numero_mediciones; i++) {
			    Medicion &m = maquina.mediciones[i];
			for (int j = 0; j < m.numero_lecturas; j++) {
				    Lectura &lectura = m.lecturas[j];
				if(lectura.tipo == sensor) {
					strcpy(fechas[n], m.fecha_hora);
					valores[n] = lectura.valor[0];
					n++;
                    Agregar_casilla(valores, n);
                    Agregar_fila(fechas, n);
				}
			}
		}
        //ORDENAR CRONOLOGICAMENTE
		for(int a = 0; a < n; a++) {
			for(int b = 0; b < n - 1 - a; b++) {
				if(Comparar_fechas(fechas[b], fechas[b + 1])) {
					char tempFecha[24];
					double tempvalor = valores[b];

					strcpy(tempFecha, fechas[b]);
					strcpy(fechas[b], fechas[b + 1]);
					strcpy(fechas[b + 1], tempFecha);


					valores[b] = valores[b + 1];
					valores[b + 1] = tempvalor;
				}
			}
		}
		if (n == 0) {
			archivo << "No hay mediciones para el sensor " << endl;
			continue;
		}
		double minvalor = valores[0], Maxvalor = valores[0], Sumavalores = 0;
		char tipoStr[2];
		tipoStr[0] = sensor;
		tipoStr[1] = '\0';

			for (int i = 0; i < n; i++) {
				if (sensor != 'E') {
					bool esAnomalo = Es_anomalia(tipoStr, valores[i], config);
					if (esAnomalo) {
						archivo << "Fecha: " << fechas[i] << " valor: " << valores[i] << " Anomalia" << endl;
					} else {
						archivo << "Fecha: " << fechas[i] << " valor: " << valores[i] << " Normal" << endl;
					}
				} else {
					archivo << "Fecha: " << fechas[i] << " valor: " << valores[i] << endl;
				}

				if (valores[i] < minvalor) minvalor = valores[i];
				if (valores[i] > Maxvalor) Maxvalor = valores[i];
				suma += valores[i];
			}

			double promedio = suma / n;
			archivo << "Minimo: " << minvalor << endl;
			archivo << "Maximo: " << Maxvalor << endl;
			archivo << "Promedio: " << promedio << endl << endl;
 
		}
		archivo.close();
                Limpiar_apuntador_char(fechas, n);
                delete[] valores;
		cout << "Reporte generado: " << nombreArchivo << endl;
	}
SalaUCI* Leer_archivo_binario(char nombreArchivo[])
{
    fstream archivo_sala(nombreArchivo, ios::in|ios::binary);
    if(!archivo_sala) {
        cout << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }
    SalaUCI* sala = new SalaUCI;
    archivo_sala.read((char*)&sala->id, sizeof(sala->id));
    archivo_sala.read((char*)&sala->numero_maquinas, sizeof(sala->numero_maquinas));
    sala->maquinas = new MaquinaUCI[sala->numero_maquinas];
    for(int i = 0 ; i < sala->numero_maquinas ; i++)
    {
        archivo_sala.read((char*)&sala->maquinas[i].id, sizeof(sala->maquinas[i].id));
        archivo_sala.read((char*)&sala->maquinas[i].numero_mediciones, sizeof(sala->maquinas[i].numero_mediciones));
        sala->maquinas[i].mediciones = new Medicion[sala->maquinas[i].numero_mediciones];
        for(int j = 0 ; j < sala->maquinas[i].numero_mediciones ; j++)
        {
            archivo_sala.read((char*)&sala->maquinas[i].mediciones[j].id_paciente, sizeof(sala->maquinas[i].mediciones[j].id_paciente));
            archivo_sala.read((char*)&sala->maquinas[i].mediciones[j].fecha_hora, sizeof(sala->maquinas[i].mediciones[j].fecha_hora));
            archivo_sala.read((char*)&sala->maquinas[i].mediciones[j].numero_lecturas, sizeof(sala->maquinas[i].mediciones[j].numero_lecturas));
            sala->maquinas[i].mediciones[j].lecturas = new Lectura[sala->maquinas[i].mediciones[j].numero_lecturas];
            for(int k = 0 ; k < sala->maquinas[i].mediciones[j].numero_lecturas ; k++ )
            {
                archivo_sala.read((char*)&sala->maquinas[i].mediciones[j].lecturas[k].tipo, sizeof(sala->maquinas[i].mediciones[j].lecturas[k].tipo));
                if(sala->maquinas[i].mediciones[j].lecturas[k].tipo == 'P')
                {
                    int sistolica, diastolica;
                    archivo_sala.read((char*)&sistolica, sizeof(int));
                    archivo_sala.read((char*)&diastolica, sizeof(int));
                    sala->maquinas[i].mediciones[j].lecturas[k].valor[0] = static_cast<double>(sistolica);
                    sala->maquinas[i].mediciones[j].lecturas[k].valor[1] = static_cast<double>(diastolica);
                }else{
                    archivo_sala.read((char*)&sala->maquinas[i].mediciones[j].lecturas[k].valor[0], sizeof(sala->maquinas[i].mediciones[j].lecturas[k].valor[0]));
                }
            }

        }
    }
    archivo_sala.close();

    return sala;
}
void Limpiar_apuntador(SalaUCI* sala) 
{
for (int i = 0; i < sala->numero_maquinas; i++) {

        for (int j = 0; j < sala->maquinas[i].numero_mediciones; j++) {

            delete[] sala->maquinas[i].mediciones[j].lecturas;
        }

        delete[] sala->maquinas[i].mediciones;
    }

    delete[] sala->maquinas;
    delete sala;
}
double abs_valor(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

bool Es_anomalia_ECG(const Medicion &medicion, const ArchivoConfig &config) {
    double min_medicion = 0.0;
    double max_medicion = 0.0;
    bool primer_valor = true;

    for (int i = 0; i < medicion.numero_lecturas; ++i) {
        if (medicion.lecturas[i].tipo == 'E') {
            if (primer_valor) {
                min_medicion = medicion.lecturas[i].valor[0];
                max_medicion = medicion.lecturas[i].valor[0];
                primer_valor = false;
            } else {
                if (medicion.lecturas[i].valor[0] < min_medicion) {
                    min_medicion = medicion.lecturas[i].valor[0];
                }
                if (medicion.lecturas[i].valor[0] > max_medicion) {
                    max_medicion = medicion.lecturas[i].valor[0];
                }
            }
        }
    }

    double limite_inf_ecg = 0.0;
    double limite_sup_ecg = 0.0;
    bool umbral_encontrado = false;
    
    for (int i = 0; i < config.tamaño; ++i) {
        if (strcmp(config.umbrales[i].tipo, "E") == 0) {
            limite_inf_ecg = atof(config.umbrales[i].inf);
            limite_sup_ecg = atof(config.umbrales[i].sup);
            umbral_encontrado = true;
            break;
        }
    }

    if (!umbral_encontrado || primer_valor) {
        return false;
    }

    double suma_mediciones_abs = abs_valor(min_medicion) + abs_valor(max_medicion);
    double suma_umbrales_abs = abs_valor(limite_inf_ecg) + abs_valor(limite_sup_ecg);

    return suma_mediciones_abs > suma_umbrales_abs;
}
void Generar_archivo_binario_anomalias_ECG(SalaUCI* &Sala, ArchivoConfig &config)
{
    fstream archivo_ECG_anomalo("pacientes_ecg_anomalos.dat", ios::out|ios::binary);
    if (archivo_ECG_anomalo.fail()) {
        cerr << "Error creating binary file: pacientes_ecg_anomalos.dat" << endl;
        return;
    }
    for (int i = 0; i < Sala->numero_maquinas; i++) {
        for (int j = 0; j < Sala->maquinas[i].numero_mediciones; j++) {
            Medicion &m = Sala->maquinas[i].mediciones[j];

            if (Es_anomalia_ECG(Sala->maquinas[i].mediciones[j], config)) {

                int numECG = 0;
                for (int k = 0; k < Sala->maquinas[i].mediciones[j].numero_lecturas; k++) {
                    if (Sala->maquinas[i].mediciones[j].lecturas[k].tipo == 'E') {
                        numECG++;
                    }
                }

                char idPaciente[11] = {0};
                strncpy(idPaciente, Sala->maquinas[i].mediciones[j].id_paciente, 10);
                archivo_ECG_anomalo.write(reinterpret_cast<char*>(idPaciente), 11);

                archivo_ECG_anomalo.write(reinterpret_cast<char*>(&numECG), sizeof(int));

                for (int k = 0; k < Sala->maquinas[i].mediciones[j].numero_lecturas; k++) {
                    if (m.lecturas[k].tipo == 'E') {
                        archivo_ECG_anomalo.write(reinterpret_cast<char*>(Sala->maquinas[i].mediciones[j].fecha_hora), 24);
                        archivo_ECG_anomalo.write(reinterpret_cast<char*>(&Sala->maquinas[i].mediciones[j].lecturas[k].valor[0]), sizeof(double));
                    }
                }
            }
        }
    }

    archivo_ECG_anomalo.close();
}

void generar_reportes_de_anomalias(SalaUCI* &sala, const ArchivoConfig &config) {
    ofstream archivo("anomalias.txt");
    if (!archivo.is_open()) {
        cerr << "Error al crear el archivo de anomalias." << endl;
        return;
    }

    for (int i = 0; i < sala->numero_maquinas; i++) {
        const MaquinaUCI &maquina = sala->maquinas[i];

        for (int j = 0; j < maquina.numero_mediciones; ++j) {
            const Medicion &medicion = maquina.mediciones[j];

            for (int k = 0; k < medicion.numero_lecturas; ++k) {
                const Lectura &lectura = medicion.lecturas[k];

                if (lectura.tipo != 'E') {
                    
                    if (lectura.tipo == 'T') {
                        if (Es_anomalia("T", lectura.valor[0], config)) {
                            archivo << "Paciente id: " << medicion.id_paciente << endl
                                    << "Fecha y Hora: " << medicion.fecha_hora << endl
                                    << "Tipo de Sensor: Temperatura" << endl
                                    << "valor: " << lectura.valor[0] << endl
                                    << "Estado: Anomalia" << endl;
                        }
                    } else if (lectura.tipo == 'O') {
                        if (Es_anomalia("O", lectura.valor[0], config)) {
                            archivo << "Paciente id: " << medicion.id_paciente << endl
                                    << "Fecha y Hora: " << medicion.fecha_hora << endl
                                    << "Tipo de Sensor: Oximetria" << endl
                                    << "valor: " << lectura.valor[0] << endl
                                    << "Estado: Anomalia" << endl;
                        }
                    } else if (lectura.tipo == 'P') {

                        if (Es_anomalia("P_SIS", lectura.valor[0], config)) {
                            archivo << "Paciente id: " << medicion.id_paciente << endl
                                    << "Fecha y Hora: " << medicion.fecha_hora << endl
                                    << "Tipo de Sensor: Presion Arterial Sistolica" << endl
                                    << "valor: " << lectura.valor[0] << endl
                                    << "Estado: Anomalia" << endl;
                        }

                        if (Es_anomalia("P_DIA", lectura.valor[1], config)) {
                            archivo << "Paciente id: " << medicion.id_paciente << endl
                                    << "Fecha y Hora: " << medicion.fecha_hora << endl
                                    << "Tipo de Sensor: Presion Arterial Diastolica" << endl
                                    << "valor: " << lectura.valor[1] << endl
                                    << "Estado: Anomalia" << endl;
                        }
                    }
                }
            }
        }
    }

    archivo.close();
}

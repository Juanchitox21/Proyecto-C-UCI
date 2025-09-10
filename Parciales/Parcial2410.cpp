// Incluye la biblioteca para entrada/salida en consola (cout, endl, etc.)
#include <iostream>
// Incluye la biblioteca para manejar archivos (ifstream)
#include <fstream>
// Incluye la biblioteca para funciones de manejo de cadenas (como strlen, strcpy)
#include <cstring>
// Usa el espacio de nombres estándar para evitar escribir "std::" repetidamente
using namespace std;

// Define la estructura "transaccion" para almacenar información de una transacción
struct transaccion {
    char tipo;        // Carácter que indica el tipo de transacción (ej. 'D' para depósito)
    long monto;       // Cantidad de dinero de la transacción
};

// Define la estructura "cliente" para almacenar información de un cliente
struct cliente {
    char nombre[21];                // Array de 21 caracteres para el nombre (20 + '\0')
    char cuenta[11];                // Array de 11 caracteres para el número de cuenta (10 + '\0')
    char tipo_de_cuenta;            // Carácter que indica el tipo de cuenta (ej. 'A' para ahorro)
    char numero_de_transacciones;    // Número de transacciones asociadas al cliente
    transaccion* transacciones;     // Puntero a un array dinámico de transacciones
};

// Declara una función para liberar la memoria asignada dinámicamente en un cliente
void liberarCliente(cliente& C) {
    // Libera la memoria del array dinámico de transacciones
    delete[] C.transacciones;
    // Establece el puntero a nullptr para evitar accesos accidentales a memoria liberada
    C.transacciones = nullptr;
    // Resetea el número de transacciones a 0
    C.numero_de_transacciones = 0;
}

// Declara una función que lee los datos de un cliente desde un archivo binario
cliente leer_Archivo(const char* nombre_Archivo) {
    // Crea una instancia de la estructura cliente y la inicializa con ceros
    cliente C = {};
    
    // Abre el archivo especificado en modo lectura y binario
    ifstream archivo(nombre_Archivo, ios::in | ios::binary);
    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        // Si no se pudo abrir, imprime un mensaje de error
        cout << "El archivo no se abrió correctamente" << endl;
        // Devuelve el objeto cliente inicializado (vacío)
        return C;
    }

    // Lee 20 bytes del archivo para el campo nombre
    if (!archivo.read(C.nombre, 20)) {
        // Si la lectura falla, imprime un mensaje de error
        cout << "Error al leer el nombre" << endl;
        // Cierra el archivo
        archivo.close();
        // Devuelve el objeto cliente (vacío o parcialmente lleno)
        return C;
    }
    // Asegura que el nombre sea una cadena terminada en '\0'
    C.nombre[20] = '\0';

    // Lee 10 bytes del archivo para el campo cuenta
    if (!archivo.read(C.cuenta, 10)) {
        // Si la lectura falla, imprime un mensaje de error
        cout << "Error al leer la cuenta" << endl;
        // Cierra el archivo
        archivo.close();
        // Devuelve el objeto cliente
        return C;
    }
    // Asegura que el número de cuenta sea una cadena terminada en '\0'
    C.cuenta[10] = '\0';

    // Lee 1 byte del archivo para el campo tipo_de_cuenta
    if (!archivo.read(&C.tipo_de_cuenta, 1)) {
        // Si la lectura falla, imprime un mensaje de error
        cout << "Error al leer el tipo de cuenta" << endl;
        // Cierra el archivo
        archivo.close();
        // Devuelve el objeto cliente
        return C;
    }

    // Lee 1 byte del archivo para el campo numero_de_transacciones
    if (!archivo.read(&C.numero_de_transacciones, 1)) {
        // Si la lectura falla, imprime un mensaje de error
        cout << "Error al leer el número de transacciones" << endl;
        // Cierra el archivo
        archivo.close();
        // Devuelve el objeto cliente
        return C;
    }

    // Verifica que el número de transacciones sea positivo
    if (C.numero_de_transacciones <= 0) {
        // Si es inválido, imprime un mensaje de error
        cout << "Número de transacciones inválido" << endl;
        // Cierra el arch   ivo
        archivo.close();
        // Devuelve el objeto cliente
        return C;
    }

    // Asigna memoria dinámica para el array de transacciones según el número leído
    C.transacciones = new transaccion[static_cast<size_t>(C.numero_de_transacciones)];
    // Crea un puntero auxiliar para iterar sobre el array de transacciones
    transaccion* pTransaccion = C.transacciones;

    // Itera tantas veces como transacciones haya
    for (int i = 0; i < C.numero_de_transacciones; i++) {
        // Lee 1 byte para el campo tipo de la transacción actual
        if (!archivo.read(&(pTransaccion->tipo), 1) ||
            // Lee el tamaño de un long para el campo monto de la transacción
            !archivo.read(reinterpret_cast<char*>(&pTransaccion->monto), sizeof(long))) {
            // Si alguna lectura falla, imprime un mensaje de error
            cout << "Error al leer la transacción " << i + 1 << endl;
            // Libera la memoria asignada para las transacciones
            liberarCliente(C);
            // Cierra el archivo
            archivo.close();
            // Devuelve el objeto cliente
            return C;
        }
        // Avanza el puntero a la siguiente transacción
        pTransaccion++;
    }

    // Cierra el archivo después de leer todos losබ

System: los datos
    // Cierra el archivo después de leer todos los datos
    archivo.close();
    // Devuelve el objeto cliente con los datos leídos
    return C;
}

// Función principal del programa
int main() {
    // Llama a la función leer_Archivo para leer un archivo binario llamado "datos.bin"
    cliente C = leer_Archivo("datos.bin");

    // Imprime los datos del cliente para verificar la lectura
    cout << "Nombre: " << C.nombre << endl;
    cout << "Cuenta: " << C.cuenta << endl;
    cout << "Tipo de cuenta: " << C.tipo_de_cuenta << endl;
    cout << "Número de transacciones: " << static_cast<int>(C.numero_de_transacciones) << endl;

    // Itera sobre las transacciones e imprime sus detalles
    for (int i = 0; i < C.numero_de_transacciones; i++) {
        cout << "Transacción " << i + 1 << ": Tipo = " << C.transacciones[i].tipo
             << ", Monto = " << C.transacciones[i].monto << endl;
    }

    // Libera la memoria asignada para las transacciones
    liberarCliente(C);

    // Indica que el programa terminó correctamente
    return 0;
}
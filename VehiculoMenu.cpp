#include <iostream>
#include "VehiculoMenu.h"
using namespace std;

VehiculoMenu::VehiculoMenu(){
    _cantidadOpciones = 4;
}
void VehiculoMenu::mostrar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

void VehiculoMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             MENU VEHICULOS            ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR CLIENTE                ||
||     2 - MOSTRAR TODOS LOS VEHICULOS   ||
||     3 - ELIMINAR VEHICULOS            ||
||     4 - BUSCAR POR D.N.I              ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout <<endl;
    cout << "Seleccione una opcion: ";
}

int VehiculoMenu::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    }
    return opcion;
}


void VehiculoMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1: {
            string dni;
            cout << "Ingrese el DNI del cliente: ";
            cin >> dni;
            int idCliente = _clienteManager.buscarIdClientePorDNI(dni);
            if (idCliente != -1) {
                _vehiculoMenu.cargar(idCliente);
            }
            else {
                cout << "No se encontro ningun cliente con ese DNI." << endl;
            }
            break;
        }
        case 2: {
            _vehiculoMenu.mostrar();
            break;
        }
        case 3: {
            _vehiculoMenu.eliminarPorPatente();
            break;
        }
        case 4: {
            _vehiculoMenu.mostrarVehiculosDeClientePorDNI(_clienteManager);
            break;
        }
    }
}


void VehiculoMenu::mostrarMenuUso(){
    cout << R"(
||||||||||||||||||||||||||||||||||||||||||||
||           MENU USO DEL VEHICULO        ||
||||||||||||||||||||||||||||||||||||||||||||
||     1 - PARTICULAR                     ||
||     2 - COMERCIAL                      ||
||     3 - CARGA                          ||
||     4 - SERVICIO PUBLICO               ||
||     5 - ALQUILER                       ||
||     6 - EMERGENCIA                     ||
||||||||||||||||||||||||||||||||||||||||||||
)";
}

std::string VehiculoMenu::ejecutarOpcionMenuUso(int opcion) {
    switch (opcion) {
        case 1: return "PARTICULAR";
        case 2: return "COMERCIAL";
        case 3: return "CARGA";
        case 4: return "SERVICIO PUBLICO";
        case 5: return "ALQUILER";
        case 6: return "EMERGENCIA";
        default: return "DESCONOCIDO"; // o podrías devolver "", según lo que necesites
    }
}

int VehiculoMenu::seleccionOpcionMenuUso(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones+2){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void VehiculoMenu::mostrarMenuCategoria() {
    cout << R"(
||||||||||||||||||||||||||||||||||||||||||||||
||        MENU CATEGORÍA DE VEHICULO        ||
||||||||||||||||||||||||||||||||||||||||||||||
||     1 - AUTOMOVIL                        ||
||     2 - MOTO                             ||
||     3 - CAMIONETA                        ||
||     4 - COLECTIVO                        ||
||     5 - REMOLQUE                         ||
||||||||||||||||||||||||||||||||||||||||||||||
||     0 - VOLVER                           ||
||||||||||||||||||||||||||||||||||||||||||||||
)";
}

std::string VehiculoMenu::ejecutarOpcionMenuCategoria(int opcion) {
    switch (opcion) {
        case 1: return "AUTOMOVIL";
        case 2: return "MOTO";
        case 3: return "CAMIONETA";
        case 4: return "COLECTIVO";
        case 5: return "REMOLQUE";
        default: return "DESCONOCIDO"; // Maneja opciones no válidas
    }
}

int VehiculoMenu::seleccionOpcionMenuCategoria(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones+1){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    }
    return opcion;
}
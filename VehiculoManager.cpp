#include <iostream>
#include <string>
#include "VehiculoManager.h"
#include "utils.h"
#include "VehiculoMenu.h"
using namespace std;

VehiculoManager::VehiculoManager()
: _vehiculosArchivo("Vehiculos.dat"){
};

void VehiculoManager::cargar(int iDCliente) {
    VehiculoMenu menu;
    int opcionUso, opcionCategoria;
    int id = _vehiculosArchivo.getID();
    int idCliente = iDCliente;
    string chasis, numeroMotor, anio;
    cout << "---------------------" << endl;
    cout << "Cargar Nuevo Vehiculo" << endl;
    cout << "ID: " << id << endl;
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Ingrese marca: ";
    string marca = cargarCadena();
    cout << "Ingrese modelo: ";
    string modelo = cargarCadena();
    cout << "Ingrese patente: ";
    string patente = cargarCadena();
    cout << "Ingrese anio: ";
    cin >> anio;
    menu.mostrarMenuUso();
    cout << "Seleccione una opcion: ";
    cin >> opcionUso;
    string uso = menu.ejecutarOpcionMenuUso( opcionUso);
    menu.mostrarMenuCategoria();
    cout << "Seleccione una opcion: ";
    cin >> opcionCategoria;
    string categoria = menu.ejecutarOpcionMenuCategoria(opcionCategoria);
    cout << "Ingrsar numero de chasis:";
    cin>> chasis;
    cout << "Ingrese numero de motor:";
    cin>> numeroMotor;

    if (_vehiculosArchivo.guardar(Vehiculo(id, idCliente, anio, marca, modelo, patente, categoria, false, chasis, numeroMotor,uso))){
        cout << "Se agrego correctamente" << endl;
    } else {
        cout << "Error!" << endl;
    }
};


void VehiculoManager::mostrar() {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        mostrarLista(vehiculo);
    }
}


void VehiculoManager::eliminar(int id) {
    if (_vehiculosArchivo.eliminar(id)) {
        cout << "Vehículo eliminado correctamente." << endl;
    }
    else {
        cout << "No se pudo eliminar el vehículo." << endl;
    }
}


void VehiculoManager::mostrarLista(Vehiculo vehiculo) {
    if (!vehiculo.getEliminado()) {
        cout << "----------------------------" << endl;
        cout << "ID: " << vehiculo.getId() << endl;
        cout << "ID Cliente: " << vehiculo.getIdCliente() << endl;
        cout << "Marca: " << vehiculo.getMarca() << endl;
        cout << "Modelo: " << vehiculo.getModelo() << endl;
        cout << "Placa: " << vehiculo.getPatente() << endl;
        cout << "Uso: " << vehiculo.getUso() << endl;
        cout << "Categoría: " << vehiculo.getCategoria() << endl;
        cout << "Número de chasis: " << vehiculo.getNumChasis() << endl;
        cout << "Número de motor: " << vehiculo.getNumMotor() << endl;
        cout << "Año: " << vehiculo.getAnio() << endl;
        cout << "----------------------------" << endl;
    }
}

void VehiculoManager::mostrarVehiculosDeCliente(int idClienteBuscado) {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    cout << "Vehículos del cliente " << idClienteBuscado << ":" << endl;

    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        if (vehiculo.getIdCliente() == idClienteBuscado && !vehiculo.getEliminado()) {
            mostrarLista(vehiculo);
        }
    }
}


void VehiculoManager::eliminarPorPatente() {
    string patente;
    cout << "Ingrese la patente del vehículo a eliminar: ";
    cin >> patente;
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        if (vehiculo.getPatente() == patente && !vehiculo.getEliminado()) {
            _vehiculosArchivo.eliminar(vehiculo.getId());
            cout << "Vehículo eliminado correctamente." << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "No se encontró ningún vehículo con esa patente." << endl;
    }
}



void VehiculoManager::mostrarVehiculosDeClientePorDNI(ClienteManager& clienteManager) {
    string dni;
    cout << "Ingrese el DNI del cliente: ";
    cin >> dni;

    int idCliente = clienteManager.buscarIdClientePorDNI(dni);
    if (idCliente == -1) {
        cout << "No se encontró ningún cliente con ese DNI." << endl;
        return;
    }

    int cantidad = _vehiculosArchivo.cantidadRegistros();
    bool encontrado = false;

    cout << "Vehículos asociados al cliente con DNI " << dni << ":" << endl;
    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        if (vehiculo.getIdCliente() == idCliente && !vehiculo.getEliminado()) {
            mostrarLista(vehiculo);
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "El cliente no tiene vehículos registrados." << endl;
    }
}

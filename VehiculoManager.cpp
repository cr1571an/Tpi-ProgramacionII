#include <iostream>
#include <string>
#include "VehiculoManager.h"
#include "ClientesArchivo.h"
#include "utils.h"
using namespace std;

VehiculoManager::VehiculoManager(): _vehiculosArchivo("Vehiculos.dat"){
};

void VehiculoManager::cargar(Cliente c) {
    int anio;
    int id = _vehiculosArchivo.getID();
    int idCliente = c.getIdCliente();
    cout << "---------------------" << endl;
    cout << "Cargar Nuevo Vehiculo" << endl;
    cout << "ID: " << id << endl;
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Ingrese marca: ";
    string marca = cargarCadena();
    cout << "Ingrese modelo: ";
    string modelo = cargarCadena();
    cout << "Ingrese placa: ";
    string placa = cargarCadena();
    cout << "Ingrese anio: ";
    cin >> anio;
    cout << "Ingrese categoria: ";
    string categoria = cargarCadena();

    Vehiculos nuevoVehiculo(id, idCliente, anio, marca, modelo, placa, categoria);

    if (_vehiculosArchivo.guardar(nuevoVehiculo)) {
        cout << "Se agrego correctamente" << endl;
    } else {
        cout << "Error!" << endl;
    }
};

void VehiculoManager::mostrar() {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    Vehiculos *vVehiculo = new Vehiculos[cantidad];
    if(vVehiculo == nullptr) {
        cout << "No se pudo asignar memoria..." << endl;
        exit(0);
    }
    _vehiculosArchivo.leerTodos(vVehiculo, cantidad);
    for(int i=0; i<cantidad; i++) {
        mostrarLista(vVehiculo[i]);
    }
    delete [] vVehiculo;
};


void VehiculoManager::eliminar(int id) {
    if (_vehiculosArchivo.eliminar(id)) {
        cout << "Vehículo eliminado correctamente." << endl;
    } else {
        cout << "No se pudo eliminar el vehículo." << endl;
    }
}


void VehiculoManager::actualizar() {

};

void VehiculoManager::mostrarLista(Vehiculos vehiculo) {
    cout << "----------------------------" <<endl;
    cout << "ID: "<< vehiculo.getIdVehiculos() << endl;
    cout << "ID Cliente: "<< vehiculo.getIdCliente() << endl;
    cout << "Marca: "<< vehiculo.getMarca() << endl;
    cout << "Modelo: "<< vehiculo.getModelo() << endl;
    cout << "Placa: "<< vehiculo.getPatente() << endl;
    cout << "Catehoria: "<< vehiculo.getCatehoria() << endl;
    cout << "Año: "<< vehiculo.getAnio() << endl;
    cout << "----------------------------" <<endl;
};

#include <iostream>
#include <string>
#include "VehiculoManager.h"
#include "utils.h"
using namespace std;

VehiculoManager::VehiculoManager()
: _vehiculosArchivo("Vehiculos.dat"){
};

void VehiculoManager::cargar(int iDCliente) {
    int anio;
    int id = _vehiculosArchivo.getID();
    int idCliente = iDCliente;
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

    if (_vehiculosArchivo.guardar(Vehiculos(id, idCliente, anio, marca, modelo, placa, categoria ))){
        cout << "Se agrego correctamente" << endl;
    } else {
        cout << "Error!" << endl;
    }
};


void VehiculoManager::mostrar() {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Vehiculos vehiculo = _vehiculosArchivo.leer(i);
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


void VehiculoManager::mostrarLista(Vehiculos vehiculo) {
    if (!vehiculo.getEliminado()) {
        cout << "----------------------------" <<endl;
        cout << "ID: " << vehiculo.getIdVehiculos() << endl;
        cout << "ID Cliente: " << vehiculo.getIdCliente() << endl;
        cout << "Marca: " << vehiculo.getMarca() << endl;
        cout << "Modelo: " << vehiculo.getModelo() << endl;
        cout << "Placa: " << vehiculo.getPatente() << endl;
        cout << "Catehoria: " << vehiculo.getCatehoria() << endl;
        cout << "Año: " << vehiculo.getAnio() << endl;
        cout << "----------------------------" <<endl;
    }
}

void VehiculoManager::mostrarVehiculosDeCliente(int idClienteBuscado) {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    cout << "Vehículos del cliente " << idClienteBuscado << ":" << endl;

    for (int i = 0; i < cantidad; i++) {
        Vehiculos vehiculo = _vehiculosArchivo.leer(i);
        if (vehiculo.getIdCliente() == idClienteBuscado && !vehiculo.getEliminado()) {
            mostrarLista(vehiculo);
        }
    }
}
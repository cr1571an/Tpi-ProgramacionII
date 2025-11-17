#include <iostream>
#include <string>
#include "VehiculoManager.h"
#include "utils.h"
#include "VehiculoMenu.h"
using namespace std;

VehiculoManager::VehiculoManager()
    : _vehiculosArchivo() {}

void VehiculoManager::cargar(int iDCliente) {
    VehiculoMenu menu;
    int id = _vehiculosArchivo.getIdVehiculoUltimo();
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout <<"||      CARGAR NUEVO VEHICULO      ||"<<endl;
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "ID: " << id << endl;
    cout << "CLIENTE: " << nombreApellidoClinete(iDCliente) << endl;
    cout << "INGRESE MARCA: ";
    string marca = cargarCadena();
    cout << "INGRESE MODELO: ";
    string modelo = cargarCadena();
    cout << "INGRESE PATENTE: ";
    string patente = cargarCadena();
    if (buscarIdPorPatente(patente) != -1) { mensajeErrorPatente(); return; }
    cout << "INGRESE ANIO: ";
    string anio = cargarCadena();
    string uso = menu.mostrarUso();
    string categoria = menu.mostrarCategoria();
    cout << "INGRESE NUMERO DE CHASIS: ";
    string chasis = cargarCadena();
    if (!buscarNumChasis(chasis)) { mensajeErrorNumeroChasis(); return; }
    cout << "INGRESE NUMERO DEL MOTOR: ";
    string numeroMotor = cargarCadena();
    if (!buscarNumMotor(numeroMotor)) { mensajeErrorNumeroMotor(); return; }
    if (_vehiculosArchivo.guardar(Vehiculo(id, iDCliente, anio, marca, modelo, patente, categoria, false, chasis, numeroMotor, uso))) {
        cout << "SE GUARDO CORRECTAMENTE" << endl;
    } else {
        cout << "ERROR!" << endl;
    }
}

void VehiculoManager::mostrar() {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        mostrarLista(vehiculo);
    }
}

void VehiculoManager::eliminar(int idVehiculo) {
    if (_vehiculosArchivo.eliminarVehiculo(idVehiculo)) {
        cout << "VEHICULO ELIMINADO CORRECTAMENTE." << endl;
    } else {
        cout << "NO SE PUDO ELIMINAR EL VEHICULO." << endl;
    }
}

int VehiculoManager::estadoCliente(int idCliente) {
    int pos = _clientesArchivo.buscarIdCliente(idCliente);
    if (pos != -1) {
        return _clientesArchivo.leer(pos).getEliminado();
    }
    return -1;
}

void VehiculoManager::mostrarLista(Vehiculo vehiculo) {
    cout << endl;
    cout << "ID DEL VEHICULO: " << vehiculo.getIdVehiculo() << endl;
    cout << "CLIENTE: " << nombreApellidoClinete(vehiculo.getIdCliente()) << endl;
    cout << "MODELO: " << vehiculo.getModelo() << endl;
    cout << "MARCA: " << vehiculo.getMarca() << endl;
    cout << "PATENTE: " << vehiculo.getPatente() << endl;
    cout << "USO: " << vehiculo.getUso() << endl;
    cout << "CATEGORIA: " << vehiculo.getCategoria() << endl;
    cout << "NUMERO DE CHASIS: " << vehiculo.getNumChasis() << endl;
    cout << "NUMERO DEL MOTOR: " << vehiculo.getNumMotor() << endl;
    cout << "ANIO: " << vehiculo.getAnio() << endl;
    cout << "ESTADO: " << (vehiculo.getEliminado() ? "ELIMINADO" : "ACTIVO") << endl;
    cout << endl;
}

void VehiculoManager::mostrarVehiculosDeCliente(int idClienteBuscado) {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        if (vehiculo.getIdCliente() == idClienteBuscado && !vehiculo.getEliminado()) {
            mostrarLista(vehiculo);
        }
    }
}

int VehiculoManager::buscarIdPorPatente(string patente) {
    int cant = _vehiculosArchivo.cantidadRegistros();
    Vehiculo *vehiculos = new Vehiculo[cant];
    _vehiculosArchivo.leerTodos(vehiculos, cant);
    for (int i = 0; i < cant; i++) {
        if (vehiculos[i].getPatente() == patente && !vehiculos[i].getEliminado()) {
            int id = vehiculos[i].getIdVehiculo();
            delete[] vehiculos;
            return id;
        }
    }
    delete[] vehiculos;
    return -1;
}

bool VehiculoManager::buscarNumChasis(string numChasis) {
    int cant = _vehiculosArchivo.cantidadRegistros();
    Vehiculo *vehiculos = new Vehiculo[cant];
    _vehiculosArchivo.leerTodos(vehiculos, cant);
    for (int i = 0; i < cant; i++) {
        if (!vehiculos[i].getEliminado() && vehiculos[i].getNumChasis() == numChasis) {
            delete[] vehiculos;
            return false;
        }
    }
    delete[] vehiculos;
    return true;
}

bool VehiculoManager::buscarNumMotor(string numMotor) {
    int cant = _vehiculosArchivo.cantidadRegistros();
    Vehiculo *vehiculos = new Vehiculo[cant];
    _vehiculosArchivo.leerTodos(vehiculos, cant);
    for (int i = 0; i < cant; i++) {
        if (!vehiculos[i].getEliminado() && vehiculos[i].getNumMotor() == numMotor) {
            delete[] vehiculos;
            return false;
        }
    }
    delete[] vehiculos;
    return true;
}

void VehiculoManager::mensajeErrorNumeroChasis() {
    cout << "YA EXISTE UN VEHICULO CON ESE NUMERO DE CHASIS." << endl;
}

void VehiculoManager::mensajeErrorNumeroMotor() {
    cout << "YA EXISTE UN VEHICULO CON ESE NUMERO DE MOTOR." << endl;
}

void VehiculoManager::mensajeErrorPatente() {
    cout << "YA EXISTE UN VEHICULO CON ESA PATENTE." << endl;
}

string VehiculoManager::nombreApellidoClinete(int idCliente) {
    int pos = _clientesArchivo.buscarIdCliente(idCliente);
    if (pos < 0) {
        return "DESCONOCIDO";
    }
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
        return "NO SE PUEDE CLIENTE ELIMINADO.";
    }
    return cliente.getNombre() + " " + cliente.getApellido();
}

void VehiculoManager::modificarPatente(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE LA NUEVA PATENTE: ";
        string nuevaPatente;
        cin >> nuevaPatente;
        if (buscarIdPorPatente(nuevaPatente) != -1) {
            mensajeErrorPatente();
            return;
        }
        vehiculo.setPatente(nuevaPatente);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "PATENTE MODIFICADA CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR LA PATENTE." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarUso(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        VehiculoMenu menu;
        string nuevoUso = menu.mostrarUso();
        vehiculo.setUso(nuevoUso);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "USO MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL USO." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarCategoria(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        VehiculoMenu menu;
        string nuevaCategoria = menu.mostrarCategoria();
        vehiculo.setCategoria(nuevaCategoria);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "CATEGORIA MODIFICADA CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR LA CATEGORIA." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarNumChasis(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE EL NUEVO NUMERO DE CHASIS: ";
        string nuevoChasis;
        cin >> nuevoChasis;
        if (!buscarNumChasis(nuevoChasis)) {
            mensajeErrorNumeroChasis();
            return;
        }
        vehiculo.setNumChasis(nuevoChasis);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "NUMERO DE CHASIS MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL NUMERO DE CHASIS." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarNumMotor(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE EL NUEVO NUMERO DE MOTOR: ";
        string nuevoMotor;
        cin >> nuevoMotor;
        if (!buscarNumMotor(nuevoMotor)) {
            mensajeErrorNumeroMotor();
            return;
        }
        vehiculo.setNumMotor(nuevoMotor);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "NUMERO DE MOTOR MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL NUMERO DE MOTOR." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarAnio(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE EL NUEVO ANIO: ";
        string nuevoAnio;
        cin >> nuevoAnio;
        vehiculo.setAnio(nuevoAnio);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "ANIO MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL ANIO." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::listadoPorMarca() {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    Vehiculo vehiculos[cantidad];
    _vehiculosArchivo.leerTodos(vehiculos, cantidad);
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (vehiculos[j].getMarca() > vehiculos[j + 1].getMarca()) {
                Vehiculo aux = vehiculos[j];
                vehiculos[j] = vehiculos[j + 1];
                vehiculos[j + 1] = aux;
            }
        }
    }
    cout << "LISTADO DE VEHICULOS POR MARCA:" << endl;
    for (int i = 0; i < cantidad; i++) {
        if (!vehiculos[i].getEliminado()) {
            mostrarLista(vehiculos[i]);
        }
    }
}

void VehiculoManager::listadoPorAnio() {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    Vehiculo vehiculos[cantidad];
    _vehiculosArchivo.leerTodos(vehiculos, cantidad);
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (vehiculos[j].getAnio() > vehiculos[j + 1].getAnio()) {
                Vehiculo aux = vehiculos[j];
                vehiculos[j] = vehiculos[j + 1];
                vehiculos[j + 1] = aux;
            }
        }
    }
    cout << "LISTADO DE VEHICULOS POR ANIO:" << endl;
    for (int i = 0; i < cantidad; i++) {
        if (!vehiculos[i].getEliminado()) {
            mostrarLista(vehiculos[i]);
        }
    }
}
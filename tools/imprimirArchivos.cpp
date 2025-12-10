#include <iostream>

#include "../Cliente.h"
#include "../ClientesArchivo.h"
#include "../Fecha.h"
#include "../Pago.h"
#include "../PagoArchivo.h"
#include "../Poliza.h"
#include "../PolizaArchivo.h"
#include "../Siniestro.h"
#include "../SiniestroArchivo.h"
#include "../Vehiculo.h"
#include "../VehiculosArchivo.h"
#include "../TiposSiniestrosArchivo.h"
#include "../TipoSiniestro.h"
#include "../TipoSeguro.h"
#include "../TiposSegurosArchivo.h"
#include "../VencimientosArchivo.h"
#include "../Vencimiento.h"

using namespace std;

void imprimirClientes() {
    ClientesArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY CLIENTES CARGADOS." << endl;
        return;
    }

    Cliente* v = new Cliente[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "-------------- CLIENTES -------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getIdCliente()     << " | "
             << v[i].getNombre()        << " | "
             << v[i].getApellido()      << " | "
             << v[i].getDni()           << " | "
             << v[i].getTelefono()      << " | "
             << v[i].getEmail()         << " | "
             << v[i].getPartido()       << " | "
             << v[i].getLocalidad()     << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "--------------------------------------------" << endl;

    delete[] v;
}

void imprimirVehiculos() {
    VehiculosArchivo archivo;
    int cantidad = archivo.cantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY VEHICULOS CARGADOS." << endl;
        return;
    }

    Vehiculo* v = new Vehiculo[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "-------------- VEHÍCULOS -------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getIdCliente()          << " | "
             << v[i].getIdVehiculo()   << " | "
             << v[i].getMarca()       << " | "
             << v[i].getModelo()      << " | "
             << v[i].getPatente()     << " | "
             << v[i].getCategoria()   << " | "
             << v[i].getNumMotor()    << " | "
             << v[i].getNumChasis()   << " | "
             << v[i].getUso()         << " | "
             << v[i].getAnio()        << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "---------------------------------------------" << endl;

    delete[] v;
}

void imprimirPagos() {
    PagoArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY PAGOS CARGADOS." << endl;
        return;
    }

    Pago* v = new Pago[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "-------------- PAGOS -------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getId()     << " | "
             << v[i].getIdVencimiento()   << " | "
             << v[i].getMetodoDePago()    << " | "
             << v[i].getFechaPago().formatoFecha() << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "-----------------------------------------" << endl;

    delete[] v;
}

void imprimirSiniestros() {
    SiniestroArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY SINIESTROS CARGADOS." << endl;
        return;
    }

    Siniestro* v = new Siniestro[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "-------------- SINIESTROS -------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getId()              << " | "
             << v[i].getIdPoliza()        << " | "
             << v[i].getFechaSiniestro().formatoFecha()<< " | "
             << v[i].getIdTipoSiniestro() << " | "
             << v[i].getCostoEstimado()   << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "----------------------------------------------" << endl;

    delete[] v;
}

void imprimirPolizas() {
    PolizaArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY POLIZAS CARGADAS." << endl;
        return;
    }

    Poliza* v = new Poliza[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "-------------- POLIZAS -------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getId()                 << " | "
             << v[i].getIdVehiculo()         << " | "
             << v[i].getfechaInicio().formatoFecha() << " | "
             << v[i].getfechaFin().formatoFecha()    << " | "
             << v[i].getPrimaMensual()       << " | "
             << v[i].getSumaAsegurada()      << " | "
             << v[i].getIdTipoSeguro()       << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "------------------------------------------" << endl;

    delete[] v;
}

void imprimirTiposSiniestros() {
    TiposSiniestrosArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY TIPOS DE SINIESTROS CARGADOS." << endl;
        return;
    }

    TipoSiniestro* v = new TipoSiniestro[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "--------- TIPOS DE SINIESTROS ------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getId()          << " | "
             << v[i].getDescripcion() << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "------------------------------------------" << endl;

    delete[] v;
}

void imprimirTiposSeguros() {
    TiposSegurosArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY TIPOS DE SEGUROS CARGADOS." << endl;
        return;
    }

    TipoSeguro* v = new TipoSeguro[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "--------- TIPOS DE SEGUROS --------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getId()          << " | "
             << v[i].getDescripcion() << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "-----------------------------------------" << endl;

    delete[] v;
}

void imprimirVencimientos() {
    VencimientosArchivo archivo;
    int cantidad = archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "NO HAY VENCIMIENTOS CARGADOS." << endl;
        return;
    }

    Vencimiento* v = new Vencimiento[cantidad];
    archivo.leerTodos(v, cantidad);

    cout << "-------------- VENCIMIENTOS -------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        cout << v[i].getId()           << " | "
             << v[i].getIdPoliza()     << " | "
             << v[i].getVencimiento().formatoFecha() << " | "
             << v[i].getMonto()        << " | "
             << v[i].getPagado()       << " | "
             << v[i].getEliminado()
             << endl;
    }

    cout << "------------------------------------------------" << endl;

    delete[] v;
}
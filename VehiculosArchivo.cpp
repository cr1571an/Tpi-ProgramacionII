#include "VehiculosArchivo.h"
#include "PolizaArchivo.h"
#include <iostream>

using namespace std;


VehiculosArchivo::VehiculosArchivo(string nombreArchivo)
:_nombreArchivo(nombreArchivo){
}

bool VehiculosArchivo::guardar(Vehiculo registro) {
    FILE *archivo_vehiculo;
    bool guardado = false;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "ab");
    if (archivo_vehiculo == nullptr) {
        return guardado;
    }
    guardado = fwrite(&registro, sizeof(registro), 1, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return guardado;
}

Vehiculo VehiculosArchivo::leer(int pos) {
    FILE *archivo_vehiculo;
    Vehiculo registro;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return Vehiculo();
    }
    fseek(archivo_vehiculo, pos * sizeof(registro), SEEK_SET);
    fread(&registro, sizeof(registro), 1, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return registro;
}

int VehiculosArchivo::leerTodos(Vehiculo vehiculo[], int cantidad) {
    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return 0;
    }
    int result = fread(vehiculo, sizeof(Vehiculo), cantidad, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return result;
}

int VehiculosArchivo::cantidadRegistros() {
    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return 0;
    }
    fseek(archivo_vehiculo, 0, SEEK_END);
    int cantidad = ftell(archivo_vehiculo) / sizeof(Vehiculo);
    fclose(archivo_vehiculo);
    return cantidad;
}

int VehiculosArchivo::getIdVehiculoUltimo() {
    return cantidadRegistros()+1;
}

bool VehiculosArchivo::eliminarVehiculo(int id) {
    int pos = buscarVehiculo(id);
    if (pos == -1) {
        return false;
    }
    Vehiculo registro = leer(pos);
    registro.eliminar();
    return actualizarVehiculo(pos, registro);
}

bool VehiculosArchivo::recuperarVehiculo(int id) {
    int pos = buscarVehiculo(id);
    if (pos == -1) {
        return false;
    }
    Vehiculo registro = leer(pos);
    registro.recuperar();
    return actualizarVehiculo(pos, registro);
}

bool VehiculosArchivo::actualizarVehiculo(int pos, Vehiculo registro) {
    FILE *archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb+");
    if (archivo_vehiculo == nullptr) {
        return false;
    }
    fseek(archivo_vehiculo, pos * sizeof(Vehiculo), SEEK_SET);
    bool actualizacion = fwrite(&registro, sizeof(Vehiculo), 1, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return actualizacion;
}

void VehiculosArchivo::eliminarVehiculosDeCliente(int idCliente) {
    int cantidad = cantidadRegistros();
    Vehiculo *v = new Vehiculo[cantidad];
    leerTodos(v, cantidad);
    PolizaArchivo polizaArchivo;
    for (int i=0; i<cantidad; ++i){
        if (v[i].getIdCliente() == idCliente && !v[i].getEliminado()){
            int idVehiculo = v[i].getIdVehiculo();
            eliminarVehiculo(idVehiculo);
            int cantidadPolizas = polizaArchivo.getCantidadRegistros();
            for (int j = 0; j < cantidadPolizas; ++j){
                Poliza poliza = polizaArchivo.leer(j);
                if (!poliza.getEliminado() && poliza.getIdVehiculo() == idVehiculo){
                    polizaArchivo.eliminar(j);}
             }
         }
     }
    delete[] v;
}

int VehiculosArchivo::buscarVehiculo(int idVehiculo) {
    int cantidad = cantidadRegistros();
    for (int i = 0; i < cantidad; ++i) {
        Vehiculo v = leer(i);
        if (v.getIdVehiculo() == idVehiculo) {
            return i;
        }
    }
    return -1;
}


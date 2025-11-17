#include "VehiculosArchivo.h"
using namespace std;
#include <iostream>


VehiculosArchivo::VehiculosArchivo(string nombreArchivo)
:_nombreArchivo(nombreArchivo){
};

string VehiculosArchivo::getNombreArchivo() {
    return _nombreArchivo;
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
};

int VehiculosArchivo::buscarIdVehiculo(int id) {
    FILE *archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return -1;
    }
    Vehiculo registro;
    int posicion = 0;
    while (fread(&registro, sizeof(Vehiculo), 1, archivo_vehiculo) == 1) {
        if (registro.getIdVehiculo() == id) {
            fclose(archivo_vehiculo);
            return posicion;
        }
        posicion++;
    }
    fclose(archivo_vehiculo);
    return -1;
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
};

int VehiculosArchivo::leerTodos(Vehiculo vehiculo[], int cantidad) {
    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return 0;
    }
    int result = fread(vehiculo, sizeof(Vehiculo), cantidad, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return result;
};

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
};

int VehiculosArchivo::getIdVehiculoUltimo() {
    return cantidadRegistros()+1;
};

bool VehiculosArchivo::eliminarVehiculo(int id) {
    int pos = buscarIdVehiculo(id);
    if (pos == -1) {
        return false;
    }
    Vehiculo registro = leer(pos);
    registro.eliminar();
    return actualizarVehiculo(pos, registro);
}

bool VehiculosArchivo::recuperarVehiculo(int id) {
    int pos = buscarIdVehiculo(id);
    if (pos == -1) {
        return false;
    }
    Vehiculo registro = leer(pos);
    registro.recuperar();
    return actualizarVehiculo(pos, registro);
}

int VehiculosArchivo::buscarIDCliente(int iDCliente) {
    FILE *archivo_vehiculo;
    Vehiculo registro;
    int posicion = 0;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return -1;
    }

    while (fread(&registro, sizeof(Vehiculo), 1, archivo_vehiculo) == 1) {
        if (registro.getIdCliente() == iDCliente) {
            fclose(archivo_vehiculo);
            return posicion;
        }
        posicion++;
    }

    fclose(archivo_vehiculo);
    return -1;
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
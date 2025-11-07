#include "VehiculosArchivo.h"
using namespace std;
#include <iostream>


VehiculosArchivo::VehiculosArchivo(std::string nombreArchivo)
:_nombreArchivo(nombreArchivo){
};

std::string VehiculosArchivo::getNombreArchivo() const {
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


int VehiculosArchivo::buscarID(int id) {
    FILE *archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return -1;
    }

    Vehiculo registro;
    int posicion = 0;
    while (fread(&registro, sizeof(Vehiculo), 1, archivo_vehiculo) == 1) {
        if (registro.getId() == id) {
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


int VehiculosArchivo::getID() {
    return cantidadRegistros()+1;
};


bool VehiculosArchivo::eliminar(int id) {
    int pos = buscarID(id);
    if (pos == -1) {
        return false;
    }
    Vehiculo registro = leer(pos);
    registro.eliminar();

    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb+");
    if (archivo_vehiculo == nullptr) {
        return false;
    }
    fseek(archivo_vehiculo, pos * sizeof(Vehiculo), SEEK_SET);
    fwrite(&registro, sizeof(Vehiculo), 1, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return true;
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


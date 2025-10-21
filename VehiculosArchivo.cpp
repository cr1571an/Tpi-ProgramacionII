
#include "VehiculosArchivo.h"

VehiculosArchivo::VehiculosArchivo() {
};

VehiculosArchivo::VehiculosArchivo(std::string nombreArchivo) {
};
using namespace std;
#include <iostream>
bool VehiculosArchivo::guardar(Vehiculos registro) {
    FILE *archivo_vehiculo = fopen(_nombreArchivo.c_str(), "ab");
    if (archivo_vehiculo == nullptr) {
        cout << "No se pudo abrir el archivo." << endl;
        return false;
    }
    size_t escritos = fwrite(&registro, sizeof(Vehiculos), 1, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return escritos == 1;
}

int VehiculosArchivo::buscarID(int id) {
    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return -1;
    }
    int posicion = 0;
    Vehiculos registro;
    while (fread(&registro, sizeof(Vehiculos), 1, archivo_vehiculo) == 1) {
        if (registro.getIdVehiculos() == id) {
            break;
        }
    }
    fclose(archivo_vehiculo);
    return posicion;
};

Vehiculos VehiculosArchivo::leer(int pos) {
    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return Vehiculos();
    }
    fseek(archivo_vehiculo, pos * sizeof(Vehiculos), SEEK_SET);
    Vehiculos registro;
    fread(&registro, sizeof(Vehiculos), 1, archivo_vehiculo);
    fclose(archivo_vehiculo);
    return registro;
};

int VehiculosArchivo::leerTodos(Vehiculos vehiculo[], int cantidad) {
    FILE *archivo_vehiculo;
    archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return 0;
    }
    int result = fread(vehiculo, sizeof(Vehiculos), cantidad, archivo_vehiculo);
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
    int cantidad = ftell(archivo_vehiculo) / sizeof(Vehiculos);
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
    };
    Vehiculos registro = leer(pos);

    registro.eliminar();

    FILE *archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb+");

    if (archivo_vehiculo == nullptr) {
        return false;
    };

    fseek(archivo_vehiculo, pos * sizeof(Vehiculos), SEEK_SET);

    fwrite(&registro, sizeof(Vehiculos), 1, archivo_vehiculo);

    fclose(archivo_vehiculo);
    return true;
}


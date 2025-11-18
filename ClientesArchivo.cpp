#include "ClientesArchivo.h"
#include <iostream>
using namespace std;

ClientesArchivo::ClientesArchivo(std::string nombreArchivo)
: _nombreArchivo(nombreArchivo) {
}


bool ClientesArchivo::guardar(Cliente registro) {
    FILE *archivo_cliente;
    bool guardado;
    archivo_cliente = fopen(_nombreArchivo.c_str(), "ab");

    if (archivo_cliente == nullptr) {
        return false;
    }
    guardado = fwrite(&registro, sizeof(Cliente), 1, archivo_cliente);
    fclose(archivo_cliente);

    return guardado;
}


int ClientesArchivo::buscarIdCliente(int id) {
    FILE *archivo_vehiculo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_vehiculo == nullptr) {
        return -2;
    }
    Cliente registro;
    int posicion = 0;
    while (fread(&registro, sizeof(Cliente), 1, archivo_vehiculo) == 1) {
        if (registro.getIdCliente() == id) {
            fclose(archivo_vehiculo);
            return posicion;
        }
        posicion++;
    }
    fclose(archivo_vehiculo);
    return -1;
}


Cliente ClientesArchivo::leer(int pos) {
    FILE *archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_cliente == nullptr) {
        return Cliente();
    }

    Cliente registro;
    fseek(archivo_cliente, pos * sizeof(Cliente), SEEK_SET);
    fread(&registro, sizeof(Cliente), 1, archivo_cliente);

    fclose(archivo_cliente);
    return registro;
}


int ClientesArchivo::leerTodos(Cliente cliente[], int cantidad) {
    FILE *archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_cliente == nullptr) {
        return 0;
    }
    int result = fread(cliente, sizeof(Cliente), cantidad, archivo_cliente);

    fclose(archivo_cliente);
    return result;
}


int ClientesArchivo::getCantidadRegistros() {
    int cantidad = 0;
    FILE *archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_cliente == nullptr) {
        return cantidad;
    }
    fseek(archivo_cliente, 0, SEEK_END);
    cantidad = ftell(archivo_cliente) / sizeof(Cliente);

    fclose(archivo_cliente);
    return cantidad;
}


int ClientesArchivo::getIdClienteUltimo() {
    return getCantidadRegistros()+1;
}


bool ClientesArchivo::eliminar(int id) {
    int pos = buscarIdCliente(id);
    if (pos == -1) {
        return false;
    };
    Cliente registro = leer(pos);
    registro.eliminar();

    return actualizarRegistro(pos, registro);
}


bool ClientesArchivo::actualizarRegistro(int pos, Cliente registro) {
    FILE *archivo_cliente = fopen(_nombreArchivo.c_str(), "rb+");
    if (archivo_cliente == nullptr) {
        return false;
    }

    fseek(archivo_cliente, pos * sizeof(Cliente), SEEK_SET);
    bool actualizacion = fwrite(&registro, sizeof(Cliente), 1, archivo_cliente);

    fclose(archivo_cliente);
    return actualizacion;
}

bool ClientesArchivo::recuperar(int id) {
    int pos = buscarIdCliente(id);
    if (pos == -1) {
        return false;
    }
    Cliente registro = leer(pos);
    registro.recuperar();
    return actualizarRegistro(pos, registro);
}


#include "ClientesArchivo.h"

using namespace std;

ClientesArchivo::ClientesArchivo(std::string nombreArchivo)
: _nombreArchivo(nombreArchivo) {
};

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

};
int ClientesArchivo::buscarID(int id) {
    Cliente registro;
    int posicion;
    FILE *archivo_cliente;
    archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_cliente == nullptr) {
        return -1;
    }
    posicion = 0;
    while (fread(&registro, sizeof(Cliente), 1, archivo_cliente) == 1) {
        if (registro.getIdCliente() == id) {
            break;
        }
        posicion++;
    }
    return posicion;
};

Cliente ClientesArchivo::leer(int pos) {
    FILE *archivo_cliente;
    Cliente registro;
    archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");

    if (archivo_cliente == nullptr) {
        return registro;
    }

    fseek(archivo_cliente, pos * sizeof(Cliente), SEEK_SET);

    fread(&registro, sizeof(Cliente), 1, archivo_cliente);

    fclose(archivo_cliente);

    return registro;
};

int ClientesArchivo::leerTodos(Cliente cliente[], int cantidad) {
    int result;
    FILE *archivo_cliente;
    archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_cliente == nullptr) {
        return 0;
    }
    result = fread(cliente, sizeof(Cliente), cantidad, archivo_cliente);

    fclose(archivo_cliente);

    return result;
};

int ClientesArchivo::getCantidadRegistros() {
    int cantidad = 0;
    FILE *archivo_cliente;
    archivo_cliente = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo_cliente == nullptr) {
        return 0;
    }

    fseek(archivo_cliente, 0, SEEK_END);
    cantidad = ftell(archivo_cliente) / sizeof(Cliente);

    fclose(archivo_cliente);

    return cantidad;
};

int ClientesArchivo::getID() {
    return getCantidadRegistros()+1;
};


bool ClientesArchivo::eliminar(int id) {
    int pos = buscarID(id);
    if (pos == -1) {
        return false;
    };
    Cliente registro = leer(pos);
    registro.eliminar();

    FILE *archivo_cliente = fopen(_nombreArchivo.c_str(), "rb+");
    if (archivo_cliente == nullptr) {
        return false;
    }

    fseek(archivo_cliente, pos * sizeof(Cliente), SEEK_SET);

    fwrite(&registro, sizeof(Cliente), 1, archivo_cliente);
    fclose(archivo_cliente);
    return true;
};
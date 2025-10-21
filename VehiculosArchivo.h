#pragma once
#include <string>

#include "Clientes.h"
#include "Vehiculos.h"
#include "VehiculosArchivo.h"

class VehiculosArchivo {
    public:
        VehiculosArchivo();
        VehiculosArchivo(std::string nombreArchivo = "Vehiculos.dat");
        bool guardar(Vehiculos registro);
        int buscarID(int id);
        Vehiculos leer(int pos);
        int leerTodos(Vehiculos vehiculo[], int cantidad);
        int cantidadRegistros();
        int getID();
        bool eliminar(int id);

    private:
        std::string _nombreArchivo;

};

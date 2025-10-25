#pragma once
#include <string>

#include "Clientes.h"
#include "Vehiculos.h"
#include "VehiculosArchivo.h"

class VehiculosArchivo {
        public:
            VehiculosArchivo(std::string nombreArchivo = "Vehiculos.dat");
            bool guardar(Vehiculos registro);
            int buscarID(int id);
            int buscarIDCliente(int id);
            Vehiculos leer(int pos);
            int leerTodos(Vehiculos vehiculo[], int cantidad);
            int cantidadRegistros();
            int getID();
            bool eliminar(int id);
            std::string getNombreArchivo() const;

        private:
            std::string _nombreArchivo;
};

#pragma once
#include <string>

#include "Clientes.h"
#include "Vehiculo.h"
#include "VehiculosArchivo.h"

class VehiculosArchivo {
        public:
            VehiculosArchivo(std::string nombreArchivo = "Vehiculos.dat");
            bool guardar(Vehiculo registro);
            int buscarID(int id);
            int buscarIDCliente(int id);
            Vehiculo leer(int pos);
            int leerTodos(Vehiculo vehiculo[], int cantidad);
            int cantidadRegistros();
            int getID();
            bool eliminar(int id);
            std::string getNombreArchivo() const;

        private:
            std::string _nombreArchivo;
};

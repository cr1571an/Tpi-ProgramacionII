#pragma once
#include <string>

#include "Cliente.h"
#include "Vehiculo.h"
#include "VehiculosArchivo.h"

class VehiculosArchivo {
        public:
            VehiculosArchivo(std::string nombreArchivo = "Vehiculos.dat");

            int buscarIdVehiculo(int id);
            int buscarIDCliente(int id);
            int leerTodos(Vehiculo vehiculo[], int cantidad);
            int cantidadRegistros();
            int getIdVehiculoUltimo();

            bool guardar(Vehiculo registro);
            bool actualizarVehiculo(int pos, Vehiculo registro);
            bool eliminarVehiculo(int idVehiculo);
            bool recuperarVehiculo(int idVehiculo);

            std::string getNombreArchivo();
            Vehiculo leer(int pos);

        private:
            std::string _nombreArchivo;
};

#pragma once
#include <string>

#include "Vehiculo.h"
#include "VehiculosArchivo.h"

class VehiculosArchivo {
        public:
            VehiculosArchivo(std::string nombreArchivo = "Vehiculos.dat");
            int buscarVehiculo(int idVehiculo);
            int buscarVehiculo(std::string patente);
            int buscarVehiculoPorCliente(int idCliente);

            int leerTodos(Vehiculo vehiculo[], int cantidad);
            int cantidadRegistros();
            int getIdVehiculoUltimo();

            bool guardar(Vehiculo registro);
            bool actualizarVehiculo(int pos, Vehiculo registro);
            bool eliminarVehiculo(int idVehiculo);
            bool recuperarVehiculo(int idVehiculo);
            void eliminarVehiculosDeCliente(int idCliente);

            std::string getNombreArchivo();
            Vehiculo leer(int pos);

        private:
            std::string _nombreArchivo;
};

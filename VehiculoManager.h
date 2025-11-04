#pragma once
#include "Vehiculos.h"
#include "VehiculosArchivo.h"

class VehiculoManager {
    public:
        VehiculoManager();
        void cargar(int iDCliente);
        void mostrar();
        void eliminar(int id);
        void actualizar();
        void mostrarVehiculosDeCliente(int idClienteBuscado);

    protected:
        void mostrarLista(Vehiculos vehiculo);

    private:
        VehiculosArchivo _vehiculosArchivo;
};

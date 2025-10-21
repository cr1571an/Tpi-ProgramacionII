#pragma once
#include "Vehiculos.h"
#include "Clientes.h"
#include "VehiculosArchivo.h"

class VehiculoManager {
    public:
        VehiculoManager();
        void cargar(Cliente c);
        void mostrar();
        void eliminar(int id);
        void actualizar();

    protected:
        void mostrarLista(Vehiculos vehiculo);

    private:
        VehiculosArchivo _vehiculosArchivo;
};

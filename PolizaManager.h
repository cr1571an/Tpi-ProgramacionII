#pragma once
#include "PolizaArchivo.h"
#include "Poliza.h"
#include "VehiculoManager.h"
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"

class PolizaManager {
    public:
        PolizaManager();
        void mostrar();
        void cargar();
        void eliminar();
        void recuperar();
        void buscarPorPatente();
    private:
        PolizaArchivo _archivo;
        VehiculoManager _vehiculoManager;
        ClientesArchivo _archivoCliente;
        VehiculosArchivo _archivoVehiculos;

};

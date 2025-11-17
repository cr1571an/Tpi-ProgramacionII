#pragma once
#include "ClienteMenu.h"
#include "PolizaArchivo.h"
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
        void modificarFechaInicio();
        void modificarPrima();
        void modificarTipoSeguro();
    private:
        PolizaArchivo _archivo;
        VehiculoManager _vehiculoManager;
        ClientesArchivo _archivoCliente;
        VehiculosArchivo _archivoVehiculos;
        ClienteMenu _clienteMenu;

        int buscarPorId();
};

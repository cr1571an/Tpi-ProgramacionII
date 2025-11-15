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
        void modificarFechaInicio();
        void modificarPrima();
        void modificarTipoSeguro();
        void listarPolizasActivas();
        void listarPolizasInactivas();
        void modificarActivaInactiva();
        void listarPorFechaVencimiento();
        void buscarPorDniCliente();
        void procesarPolizas();

    private:
        PolizaArchivo _archivo;
        VehiculoManager _vehiculoManager;
        ClientesArchivo _archivoCliente;
        VehiculosArchivo _archivoVehiculos;

        int buscarPorId();
        void mostrarPoliza(Poliza poliza);
};

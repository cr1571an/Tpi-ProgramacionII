#pragma once
#include "ClienteMenu.h"
#include "PolizaArchivo.h"
#include "VehiculoManager.h"
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"
#include "TiposSegurosArchivo.h"

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
        void reportePolizasVigentesYVencidas();

    private:
        PolizaArchivo _archivo;
        VehiculoManager _vehiculoManager;
        ClientesArchivo _archivoCliente;
        VehiculosArchivo _archivoVehiculos;
        TiposSegurosArchivo _archivoTipoSeguros;

        int buscarPorId();
        void mostrarPoliza(Poliza poliza);
        int cantidadPolizasPeriodo(Poliza polizas[],int cantidadPolizas, Fecha FechaConsulta);
        void filtrarPolizasPorFecha(Poliza polizas[], Poliza* polizasFiltradas[], int cantidadPolizas,Fecha FechaConsulta);
};

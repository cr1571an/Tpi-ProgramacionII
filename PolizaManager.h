#pragma once
#include "ClienteMenu.h"
#include "PolizaArchivo.h"
#include "VehiculoManager.h"
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"
#include "TiposSegurosArchivo.h"
#include "VencimientosArchivo.h"
#include "PagoArchivo.h"

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
        void listarPolizasVigentes();
        void listarPolizasNoVigentes();
        void listarPorFechaVencimiento();
        void buscarPorDniCliente();
        void reportePolizasSinCobertura();
        void reportePolizasVigentesYVencidas();
        void mostrarVencimientosDePoliza();

    private:
        PolizaArchivo _archivo;
        VehiculoManager _vehiculoManager;
        ClienteManager _clienteManager;
        ClientesArchivo _archivoCliente;
        VehiculosArchivo _archivoVehiculos;
        TiposSegurosArchivo _archivoTipoSeguros;
        VencimientosArchivo _archivoVencimientos;
        PagoArchivo _archivoPagos;

        int buscarPorId();
        void mostrarPoliza(Poliza poliza);
        int cantidadPolizasPeriodo(Poliza polizas[],int cantidadPolizas, Fecha FechaConsulta);
        void filtrarPolizasPorFecha(Poliza polizas[], Poliza* polizasFiltradas[], int cantidadPolizas,Fecha FechaConsulta);
        void generarVencimientos(Poliza poliza, int cantidadVencimientos);
        float calcularMontoVencimiento(int primaMensual);
        bool tieneCobertura(Poliza poliza);
        bool tienePolizasVigentes(int idVehiculo);
};

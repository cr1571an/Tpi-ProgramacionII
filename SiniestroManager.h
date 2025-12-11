#pragma once

#include "SiniestroArchivo.h"
#include "PolizaArchivo.h"
#include "TiposSiniestrosArchivo.h"
#include "VehiculosArchivo.h"
#include "ClientesArchivo.h"
#include "PagoManager.h"
#include "VencimientosArchivo.h"

class SiniestroManager {
    public:
        SiniestroManager();
        void mostrar();
        void cargar();
        void eliminar();
        void recuperar();
        void buscarPorIdPoliza();
        void modificarFechaSiniestro();
        void modificarTipoSiniestro();
        void modificarCostoEstimado();
        void listadoSiniestrosPorPoliza();
        void reporteCoberturaSiniestros();

    private:
        SiniestroArchivo _archivo;
        PolizaArchivo _polizaArchivo;
        TiposSiniestrosArchivo _tiposSiniestrosArchivo;
        VehiculosArchivo _vehiculoArchivo;
        ClientesArchivo _clienteArchivo;
        PagoManager _pagoManager;
        VencimientosArchivo _vencimientosArchivo;

        void mostrarSiniestro(Siniestro siniestro);
        void ordenarPorFechaSiniestro(Siniestro vect[], int cantidad);
        int cantidadSiniestrosPeriodo(Fecha fechaDesde, Fecha fechaHasta, Siniestro siniestros[], int cantidad);
        void filtrarPorPeriodo(Fecha fechaDesde, Fecha fechaHasta, Siniestro siniestros[],Siniestro* siniestrosFiltrados[], int cantidadSiniestros);
        bool validarCobertura(Fecha fechaSiniestro, int idPoliza);
        
};

#pragma once

#include "SiniestroArchivo.h"
#include "PolizaArchivo.h"
#include "TiposSiniestrosArchivo.h"
#include "VehiculosArchivo.h"
#include "ClientesArchivo.h"

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
        void listadoSiniestrosAprobados();
        void listadoSiniestrosNoAprobados();
        void reporteSiniestrosPorTipo();

    private:
        SiniestroArchivo _archivo;
        PolizaArchivo _polizaArchivo;
        TiposSiniestrosArchivo _tiposSiniestrosArchivo;
        VehiculosArchivo _vehiculoArchivo;
        ClientesArchivo _clienteArchivo;

        void mostrarSiniestro(Siniestro siniestro);
        void ordenarPorFechaSiniestro(Siniestro vect[], int cantidad);
};

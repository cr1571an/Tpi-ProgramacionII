#pragma once

#include "SiniestroArchivo.h"
#include "PolizaArchivo.h"


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
        void modificarEstadoSiniestro();
    private:
        SiniestroArchivo _archivo;
        PolizaArchivo _polizaArchivo;
};

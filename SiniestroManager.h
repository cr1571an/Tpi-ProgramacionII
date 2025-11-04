#pragma once

#include "SiniestroArchivo.h"


class SiniestroManager {
    public:
        SiniestroManager();
        void mostrar();
        void cargar(int idPoliza);
        void eliminar(int id);
    private:
        SiniestroArchivo _archivo;
};

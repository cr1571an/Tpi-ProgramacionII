#pragma once
#include "PolizaArchivo.h"
#include "Poliza.h"

class PolizaManager {
    public:
        PolizaManager();
        void mostrar();
        void cargar(int idCliente, int idVehiculo);
        void eliminar(int id);
    private:
        PolizaArchivo _archivo;
};

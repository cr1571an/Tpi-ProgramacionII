#pragma once
#include "Vehiculo.h"
#include "VehiculosArchivo.h"
#include "ClienteManager.h"

class VehiculoManager {
    public:
        VehiculoManager();
        void cargar(int iDCliente);
        void mostrar();
        void eliminar(int id);
        void eliminarPorPatente();
        void actualizar();
        void mostrarVehiculosDeCliente(int idClienteBuscado);
        void mostrarVehiculosDeClientePorDNI(ClienteManager& clienteManager);



    protected:
        void mostrarLista(Vehiculo vehiculo);

    private:
        VehiculosArchivo _vehiculosArchivo;
};

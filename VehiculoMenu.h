#pragma once
#include "VehiculoManager.h"
#include "ClienteManager.h"

class VehiculoMenu {
    public:
        VehiculoMenu();
        void mostrar();

    protected:
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);

    private:
        int _cantidadOpciones;
        VehiculoManager _vehiculoMenu;
        ClienteManager _clienteManager;
};
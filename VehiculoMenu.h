#pragma once
#include "VehiculoManager.h"
#include "ClienteManager.h"

class VehiculoMenu {
    public:

        VehiculoMenu();
        void mostrar();
        void mostrarOpciones();
        void ejecutarOpcion(int opcion);
        void mostrarMenuUso();
        void mostrarMenuCategoria();
        int seleccionOpcion();
        int seleccionOpcionMenuCategoria();
        int seleccionOpcionMenuUso();
        std::string ejecutarOpcionMenuUso(int opcion);
        std::string ejecutarOpcionMenuCategoria(int opcion);


    private:
        int _cantidadOpciones;
        VehiculoManager _vehiculoMenu;
        ClienteManager _clienteManager;
};
#pragma once
#include "VehiculoManager.h"
#include "ClienteManager.h"
#include "ClienteMenu.h"
#include "ClientesArchivo.h"

class VehiculoMenu {
    public:

        VehiculoMenu();
        void mostrar();
        void mostrarOpciones();
        int seleccionOpcion();
        void ejecutarOpcion(int opcion);
        void cargar();
        void modificarVehiculo();
        void buscarVehiculo();
        bool darAltaVehiculo(int idVehiculo);

        bool darAltaClientePorIdVehiculo(int posVehiculo);

        int seleccionarVehiculo(bool modificar);

        std::string mostrarCategoria();
        std::string mostrarUso();

    private:
        int _cantidadOpciones;
        VehiculoManager _vehiculoManager;
        VehiculosArchivo _vehiculosArchivo;
        ClienteManager _clienteManager;
        ClienteMenu _clienteMenu;
        ClientesArchivo _clientesArchivo;
};

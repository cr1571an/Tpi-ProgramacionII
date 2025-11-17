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
        void ejecutarOpcion(int opcion);
        void mostrarMenuUso();
        void mostrarMenuCategoria();
        void cargar();
        void modificarVehiculo();
        void mostrarMenuModificar();
        void buscarVehiculoPorPatente();
        void buscarVehiculoPorID();
        void buscarVehiculo();
        void mostrarReportes();
        void darAltaVehiculo(int idVehiculo);

        int seleccionOpcion();
        int seleccionarVehiculo(bool modificar);

        std::string mostrarCategoria();
        std::string mostrarUso();
        std::string ejecutarOpcionMenuUso(int opcion);
        std::string ejecutarOpcionMenuCategoria(int opcion);


    private:
        int _cantidadOpciones;
        VehiculoManager _vehiculoManager;
        VehiculosArchivo _vehiculosArchivo;
        ClienteManager _clienteManager;
        ClienteMenu _clienteMenu;
        ClientesArchivo _clientesArchivo;
};

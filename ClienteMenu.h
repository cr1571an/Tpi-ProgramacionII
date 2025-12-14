#pragma once
#include "ClienteManager.h"


class ClienteMenu {
  public:
    ClienteMenu();
    void mostrar();
    int buscarCliente();
    void modificarCliente();
    bool darAltaCliente(int id);
    void buscar();
    void mostrarReportes();

  protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

  private:
    int _cantidadOpciones;
    ClienteManager _clienteManager;
    ClientesArchivo _clientesArchivo;
    VehiculosArchivo _vehiculosArchivo;
};
#pragma once
#include "ClienteManager.h"

class ClienteMenu {
    public:
      ClienteMenu();
      void mostrar();

    protected:
      void mostrarOpciones();
      int seleccionOpcion();
      void ejecutarOpcion(int opcion);
      ClienteManager _clienteMenu;

    private:
      int _cantidadOpciones;
};
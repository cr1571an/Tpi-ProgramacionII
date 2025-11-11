#pragma once
#include "PolizaManager.h"


class PolizaMenu {
    public:
      PolizaMenu();
      void mostrar();

    protected:
      void mostrarOpciones();
      int seleccionOpcion();
      void ejecutarOpcion(int opcion);
      PolizaManager _polizaManager;

    private:
      int _cantidadOpciones;
};
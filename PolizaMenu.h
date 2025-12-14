#pragma once
#include "PolizaManager.h"


class PolizaMenu {
    public:
      PolizaMenu();
      void mostrar();
      int mostrarSeguro();

    private:
      int _cantidadOpciones;
      int _cantidadOpcionesSubMenuModificar;

      void mostrarOpciones();
      int seleccionOpcion();
      void ejecutarOpcion(int opcion);
      void subMenuModificar();
      void mostrarOpcionesSubMenuModificar();
      int seleccionOpcionSubMenuModificar();
      void ejecutarOpcionSubMenuModificar(int opcion);
      PolizaManager _polizaManager;
};
#pragma once
#include "SiniestroManager.h"


class SiniestroMenu {
    public:
      SiniestroMenu();
      void mostrar();

    protected:
      void mostrarOpciones();
      int seleccionOpcion();
      void ejecutarOpcion(int opcion);
      void subMenuModificar();
      void mostrarOpcionesSubMenuModificar();
      int seleccionOpcionSubMenuModificar();
      void ejecutarOpcionSubMenuModificar(int opcion);
      SiniestroManager _siniestroManager;

    private:
      int _cantidadOpciones;
      int _cantidadOpcionesSubMenuModificar;
};
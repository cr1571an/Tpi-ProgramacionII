#pragma once
#include "PagoManager.h"

class PagoMenu {
public:
    PagoMenu();
    void mostrar();
private:
    void mostrarOpciones();
    int  seleccionOpcion();
    void ejecutarOpcion(int opcion);
    void submenuActualizar();
    void submenuListados();
    void submenuConsultas();

    PagoManager _pagoManager;
    int _cantidadOpciones;
};

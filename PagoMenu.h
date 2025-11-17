#pragma once
#include "PagoManager.h"

class PagoMenu {
public:
    PagoMenu();
    void mostrar();

protected:
    void mostrarOpciones();
    int  seleccionOpcion();
    void ejecutarOpcion(int opcion);

    void submenuActualizar();
    void submenuListados();
    void submenuConsultas();
    void submenuReportes();

private:
    int _cantidadOpciones;
    PagoManager _pagoManager;
};


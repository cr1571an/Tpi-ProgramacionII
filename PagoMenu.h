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

private:
    int _cantidadOpciones;
    PagoManager _pagoManager;
};


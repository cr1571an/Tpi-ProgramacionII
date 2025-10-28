#pragma once
#include <string>
#include "Pago.h"

class PagoArchivo
{
public:
    PagoArchivo(std::string nombreArchivo = "pago.dat");
    bool guardar(Pago registro);
    int buscarID(int id);
    Pago leer(int pos);

    int leerTodos(Pago Pagos[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

private:
    std::string _nombreArchivo;
};

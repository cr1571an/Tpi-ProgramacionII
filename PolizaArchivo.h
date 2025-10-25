#pragma once
#include <string>
#include "Poliza.h"

class PolizaArchivo
{
  public:
    PolizaArchivo(std::string nombreArchivo = "poliza.dat");
    bool guardar(Poliza registro);
    int buscarID(int id);
    Poliza leer(int pos);
    
    int leerTodos(Poliza polizas[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

  private:
    std::string _nombreArchivo;
};
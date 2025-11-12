#pragma once
#include <string>

#include "Poliza.h"

class PolizaArchivo {
 public:
  PolizaArchivo(std::string nombreArchivo = "Polizas.dat");
  bool guardar(Poliza registro);
  bool guardar(Poliza registro, int pos);
  int buscarID(int id);
  Poliza leer(int pos);
  bool eliminar(int pos);

  int leerTodos(Poliza polizas[], int cantidad);
  int getCantidadRegistros();
  int getNuevoID();

 private:
  std::string _nombreArchivo;
};

#pragma once
#include <string>

#include "Vencimiento.h"

class VencimientosArchivo {
 public:
  VencimientosArchivo(std::string nombreArchivo = "Vecimientos.dat");
  bool guardar(Vencimiento registro);
  bool guardar(Vencimiento registro, int pos);
  int buscarID(int id);
  Vencimiento leer(int pos);
  bool eliminar(int pos);

  int leerTodos(Vencimiento vencimientos[], int cantidad);
  int getCantidadRegistros();
  int getNuevoID();

 private:
  std::string _nombreArchivo;
};

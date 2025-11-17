#pragma once
#include <string>

#include "TipoSeguro.h"

class TiposSegurosArchivo {
 public:
  TiposSegurosArchivo(std::string nombreArchivo = "TiposSeguros.dat");
  bool guardar(TipoSeguro registro);
  bool guardar(TipoSeguro registro, int pos);
  int buscarID(int id);
  TipoSeguro leer(int pos);
  bool eliminar(int pos);

  int leerTodos(TipoSeguro tiposSeguros[], int cantidad);
  int getCantidadRegistros();
  int getNuevoID();

 private:
  std::string _nombreArchivo;
};

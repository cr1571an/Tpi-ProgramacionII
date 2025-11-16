#pragma once
#include <string>

#include "TipoSiniestro.h"

class TiposSiniestrosArchivo {
 public:
  TiposSiniestrosArchivo(std::string nombreArchivo = "TiposSiniestros.dat");
  bool guardar(TipoSiniestro registro);
  bool guardar(TipoSiniestro registro, int pos);
  int buscarID(int id);
  TipoSiniestro leer(int pos);
  bool eliminar(int pos);

  int leerTodos(TipoSiniestro tiposSiniestros[], int cantidad);
  int getCantidadRegistros();
  int getNuevoID();

 private:
  std::string _nombreArchivo;
};

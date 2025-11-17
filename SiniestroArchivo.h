#pragma once
#include <string>

#include "Siniestro.h"

class SiniestroArchivo {
 public:
  SiniestroArchivo(std::string nombreArchivo = "Siniestros.dat");
  bool guardar(Siniestro registro);
  bool guardar(Siniestro registro, int pos);
  int buscarID(int id);
  Siniestro leer(int pos);
  bool eliminar(int pos);

  int leerTodos(Siniestro siniestros[], int cantidad);
  int getCantidadRegistros();
  int getNuevoID();

 private:
  std::string _nombreArchivo;
};

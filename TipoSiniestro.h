#pragma once
#include <string>
class TipoSiniestro {
 public:
  TipoSiniestro();
  TipoSiniestro(int id, std::string descripcion, bool eliminado);

  int getId();
  std::string getDescripcion();
  bool getEliminado();

  void setId(int id);
  void setDescripcion(std::string descripcion);
  void setEliminado(bool eliminado);

 private:
  int _id;
  char _descripcion[15];
  bool _eliminado;
};

#pragma once
#include <string>
class TipoSeguro {
 public:
  TipoSeguro();
  TipoSeguro(int id, std::string descripcion, bool eliminado);

  int getId();
  std::string getDescripcion();
  bool getEliminado();

  void setId(int id);
  void setDescripcion(std::string descripcion);
  void setEliminado(bool eliminado);

 private:
  int _id;
  char _descripcion[30];
  bool _eliminado;
};

#include "TipoSeguro.h"
#include <cstring>

TipoSeguro::TipoSeguro(): _id(0), _descripcion(""), _eliminado(false){}
TipoSeguro::TipoSeguro(int id, std::string descripcion, bool eliminado) {
    setId(id);
    setDescripcion(descripcion);
    setEliminado(eliminado);
}

int TipoSeguro::getId(){
  return _id;
}
std::string TipoSeguro::getDescripcion() {
  return std::string(_descripcion);
}

void TipoSeguro::setId(int id) {
  _id = id;
}
void TipoSeguro::setDescripcion(std::string descripcion) {
  strncpy(_descripcion, descripcion.c_str(), sizeof(_descripcion) - 1);
  _descripcion[sizeof(_descripcion) - 1] = '\0';
}

bool TipoSeguro::getEliminado() {
  return _eliminado;
}

void TipoSeguro::setEliminado(bool eliminado) {
  _eliminado = eliminado;
}
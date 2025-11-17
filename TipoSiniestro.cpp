#include "TipoSiniestro.h"
#include <cstring>

TipoSiniestro::TipoSiniestro(): _id(0), _descripcion(""), _eliminado(false){}
TipoSiniestro::TipoSiniestro(int id, const std::string descripcion, bool eliminado) {
    setId(id);
    setDescripcion(descripcion);
    setEliminado(eliminado);
}

int TipoSiniestro::getId(){
  return _id;
}
std::string TipoSiniestro::getDescripcion() {
  return std::string(_descripcion);
}

void TipoSiniestro::setId(int id) {
  _id = id;
}
void TipoSiniestro::setDescripcion(std::string descripcion) {
  strncpy(_descripcion, descripcion.c_str(), sizeof(_descripcion) - 1);
  _descripcion[sizeof(_descripcion) - 1] = '\0';
}

bool TipoSiniestro::getEliminado() {
  return _eliminado;
}

void TipoSiniestro::setEliminado(bool eliminado) {
  _eliminado = eliminado;
}
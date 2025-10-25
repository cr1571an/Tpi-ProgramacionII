#include "Siniestro.h"

#include <cstring>

Siniestro::Siniestro()
  : _id(0),
  _idPoliza(0),
  _fechaSiniestro(),
  _tipoSiniestro(""),
  _costoEstimado(0.0),
  _estado(false),
  _eliminado(false) {
}

Siniestro::Siniestro(int id, int idPoliza, Fecha fechaSiniestro, std::string tipoSiniestro,
  float costoEstimado, bool estado, bool eliminado) {
  setId(id);
  setIdPoliza(idPoliza);
  setFechaSiniestro(fechaSiniestro);
  setTipoSiniestro(tipoSiniestro);
  setCostoEstimado(costoEstimado);
  setEstado(estado);
  setEliminado(eliminado);
}

int Siniestro::getId() { return _id; }
int Siniestro::getIdPoliza() { return _idPoliza; }
Fecha Siniestro::getFechaSiniestro() { return _fechaSiniestro; }
std::string Siniestro::getTipoSiniestro() { return std::string(_tipoSiniestro); }
float Siniestro::getCostoEstimado() { return _costoEstimado; }
bool Siniestro::getEstado() { return _estado; }
bool Siniestro::getEliminado() { return _eliminado; }
void Siniestro::setId(int id) { _id = id; }
void Siniestro::setIdPoliza(int idPoliza) { _idPoliza = idPoliza; }
void Siniestro::setFechaSiniestro(Fecha fechaSiniestro) { _fechaSiniestro = fechaSiniestro; }
void Siniestro::setTipoSiniestro(std::string tipoSiniestro) {
  strncpy(_tipoSiniestro, tipoSiniestro.c_str(), sizeof(_tipoSiniestro) - 1);
  _tipoSiniestro[sizeof(_tipoSiniestro) - 1] = '\0';
}
void Siniestro::setCostoEstimado(float costoEstimado) { _costoEstimado = costoEstimado; }
void Siniestro::setEstado(bool estado) { _estado = estado; }
void Siniestro::setEliminado(bool eliminado) { _eliminado = eliminado; }

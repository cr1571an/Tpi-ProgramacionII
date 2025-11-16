#include "Siniestro.h"

#include <cstring>

Siniestro::Siniestro()
  : _id(0),
  _idPoliza(0),
  _fechaSiniestro(),
  _idTipoSiniestro(0),
  _costoEstimado(0.0),
  _estado(false),
  _eliminado(false) {
}

Siniestro::Siniestro(int id, int idPoliza, Fecha fechaSiniestro, int idTipoSiniestro,
  float costoEstimado, bool estado, bool eliminado) {
  setId(id);
  setIdPoliza(idPoliza);
  setFechaSiniestro(fechaSiniestro);
  setIdTipoSiniestro(idTipoSiniestro);
  setCostoEstimado(costoEstimado);
  setEstado(estado);
  setEliminado(eliminado);
}

int Siniestro::getId() { return _id; }
int Siniestro::getIdPoliza() { return _idPoliza; }
Fecha Siniestro::getFechaSiniestro() { return _fechaSiniestro; }
int Siniestro::getIdTipoSiniestro() { return _idTipoSiniestro; }
float Siniestro::getCostoEstimado() { return _costoEstimado; }
bool Siniestro::getEstado() { return _estado; }
bool Siniestro::getEliminado() { return _eliminado; }
void Siniestro::setId(int id) { _id = id; }
void Siniestro::setIdPoliza(int idPoliza) { _idPoliza = idPoliza; }
void Siniestro::setFechaSiniestro(Fecha fechaSiniestro) { _fechaSiniestro = fechaSiniestro; }
void Siniestro::setIdTipoSiniestro(int idTipoSiniestro) { _idTipoSiniestro = idTipoSiniestro; }
void Siniestro::setCostoEstimado(float costoEstimado) { _costoEstimado = costoEstimado; }
void Siniestro::setEstado(bool estado) { _estado = estado; }
void Siniestro::setEliminado(bool eliminado) { _eliminado = eliminado; }

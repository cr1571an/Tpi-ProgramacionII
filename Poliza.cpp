#include "Poliza.h"

#include <cstring>

Poliza::Poliza()
    : _id(0),
      _idVehiculo(0),
      _fechaInicio(),
      _fechaFin(),
      _primaMensual(0.0),
      _tipoSeguro(""),
      _vigente(false),
      _eliminado(false) {}

Poliza::Poliza(int id, int idVehiculo, Fecha fechaInicio, Fecha FechaFin,
               float primaMensual, std::string tipoSeguro, bool vigente,
               bool eliminado) {
  setId(id);
  setIdVehiculo(idVehiculo);
  setFechaInicio(fechaInicio);
  setFechaFin(FechaFin);
  setPrimaMensual(primaMensual);
  setTipoSeguro(tipoSeguro);
  setVigente(vigente);
  setEliminado(eliminado);
}

int Poliza::getId() { return _id; }
int Poliza::getIdVehiculo() { return _idVehiculo; }
Fecha Poliza::getfechaInicio() { return _fechaInicio; }
Fecha Poliza::getfechaFin() { return _fechaFin; }
float Poliza::getPrimaMensual() { return _primaMensual; }
std::string Poliza::getTipoSeguro() { return std::string(_tipoSeguro); }
bool Poliza::getVigente() { return _vigente; }
bool Poliza::getEliminado() { return _eliminado; }
void Poliza::setId(int id) { _id = id; }
void Poliza::setIdVehiculo(int idVehiculo) { _idVehiculo = idVehiculo; }
void Poliza::setFechaInicio(Fecha fechaInicio) { _fechaInicio = fechaInicio; }
void Poliza::setFechaFin(Fecha FechaFin) { _fechaFin = FechaFin; }
void Poliza::setPrimaMensual(float primaMensual) {
  _primaMensual = primaMensual;
}
void Poliza::setTipoSeguro(std::string tipoSeguro) {
  strncpy(_tipoSeguro, tipoSeguro.c_str(), sizeof(_tipoSeguro) - 1);
  _tipoSeguro[sizeof(_tipoSeguro) - 1] = '\0';
}
void Poliza::setVigente(bool vigente) { _vigente = vigente; }
void Poliza::setEliminado(bool eliminado) { _eliminado = eliminado; }

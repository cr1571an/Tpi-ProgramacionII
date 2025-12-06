#include "Poliza.h"

#include <cstring>

Poliza::Poliza()
    : _id(0),
      _idVehiculo(0),
      _fechaInicio(),
      _fechaFin(),
      _primaMensual(0.0),
      _sumaAsegurada(0),
      _idTipoSeguro(0),
      _eliminado(false) {}

Poliza::Poliza(int id, int idVehiculo, Fecha fechaInicio,
               Fecha FechaFin, float primaMensual,int sumaAsegurada, int idTipoSeguro,
               bool eliminado) {
  setId(id);
  setIdVehiculo(idVehiculo);
  setFechaInicio(fechaInicio);
  setFechaFin(FechaFin);
  setPrimaMensual(primaMensual);
  setSumaAsegurada(sumaAsegurada);
  setIdTipoSeguro(idTipoSeguro);  
  setEliminado(eliminado);
}

int Poliza::getId() { return _id; }
int Poliza::getIdVehiculo() { return _idVehiculo; }
Fecha Poliza::getfechaInicio() { return _fechaInicio; }
Fecha Poliza::getfechaFin() { return _fechaFin; }
float Poliza::getPrimaMensual() { return _primaMensual; }
int Poliza::getSumaAsegurada() { return _sumaAsegurada; }
int Poliza::getIdTipoSeguro() { return _idTipoSeguro; }
bool Poliza::getEliminado() { return _eliminado; }
void Poliza::setId(int id) { _id = id; }
void Poliza::setIdVehiculo(int idVehiculo) { _idVehiculo = idVehiculo; }
void Poliza::setFechaInicio(Fecha fechaInicio) { _fechaInicio = fechaInicio; }
void Poliza::setFechaFin(Fecha FechaFin) { _fechaFin = FechaFin; }
void Poliza::setPrimaMensual(float primaMensual) {
  _primaMensual = primaMensual;
}
void Poliza::setSumaAsegurada(int sumaAsegurada) {
  _sumaAsegurada = sumaAsegurada;
}
void Poliza::setIdTipoSeguro(int idTipoSeguro) {
  _idTipoSeguro = idTipoSeguro;
}
void Poliza::setEliminado(bool eliminado) { _eliminado = eliminado; }

bool Poliza::estaVigente() {
    Fecha fechaActual;
    return (_fechaInicio <= fechaActual && fechaActual <= _fechaFin);
}

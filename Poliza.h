#pragma once
#include <string>

#include "Fecha.h"

class Poliza {
 public:
  Poliza();
  Poliza(int id, int idVehiculo, int idCliente, Fecha fechaInicio,
         Fecha FechaFin, float primaMensual, std::string tipoSeguro,
         bool vigente, bool eliminado);

  int getId();
  int getIdVehiculo();
  int getIdCliente();
  Fecha getfechaInicio();
  Fecha getfechaFin();
  float getPrimaMensual();
  std::string getTipoSeguro();
  bool getVigente();
  bool getEliminado();
  void setId(int id);
  void setIdVehiculo(int idVehiculo);
  void setIdCliente(int idCliente);
  void setFechaInicio(Fecha fechaInicio);
  void setFechaFin(Fecha FechaFin);
  void setPrimaMensual(float primaMensual);
  void setTipoSeguro(std::string tipoSeguro);
  void setVigente(bool vigente);
  void setEliminado(bool eliminado);

 private:
  int _id;
  int _idVehiculo;
  int _idCliente;
  Fecha _fechaInicio;
  Fecha _fechaFin;
  float _primaMensual;
  char _tipoSeguro[30];
  bool _vigente;
  bool _eliminado;
};
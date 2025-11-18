#pragma once
#include <string>

#include "Fecha.h"

class Poliza {
 public:
  Poliza();
  Poliza(int id, int idVehiculo, Fecha fechaInicio,
         Fecha FechaFin, float primaMensual, int idTipoSeguro,
         bool vigente, bool eliminado);

  int getId();
  int getIdVehiculo();
  Fecha getfechaInicio();
  Fecha getfechaFin();
  float getPrimaMensual();
  int getIdTipoSeguro();
  bool getVigente();
  bool getEliminado();
  void setId(int id);
  void setIdVehiculo(int idVehiculo);
  void setFechaInicio(Fecha fechaInicio);
  void setFechaFin(Fecha FechaFin);
  void setPrimaMensual(float primaMensual);
  void setIdTipoSeguro(int idTipoSeguro);
  void setVigente(bool vigente);
  void setEliminado(bool eliminado);

 private:
  int _id;
  int _idVehiculo;
  Fecha _fechaInicio;
  Fecha _fechaFin;
  float _primaMensual;
  int _idTipoSeguro;
  bool _vigente;
  bool _eliminado;
};

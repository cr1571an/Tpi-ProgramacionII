#pragma once
#include <string>

#include "Fecha.h"

class Poliza {
 public:
  Poliza();
  Poliza(int id, int idVehiculo, Fecha fechaInicio,
         Fecha FechaFin, float primaMensual,int sumaAsegurada, int idTipoSeguro,
         bool eliminado);

  int getId();
  int getIdVehiculo();
  Fecha getfechaInicio();
  Fecha getfechaFin();
  float getPrimaMensual();
  int getSumaAsegurada();
  int getIdTipoSeguro();
  bool getEliminado();
  void setId(int id);
  void setIdVehiculo(int idVehiculo);
  void setFechaInicio(Fecha fechaInicio);
  void setFechaFin(Fecha FechaFin);
  void setPrimaMensual(float primaMensual);
  void setSumaAsegurada(int sumaAsegurada);
  void setIdTipoSeguro(int idTipoSeguro);
  void setEliminado(bool eliminado);

 private:
  int _id;
  int _idVehiculo;
  Fecha _fechaInicio;
  Fecha _fechaFin;
  float _primaMensual;
  int _sumaAsegurada;
  int _idTipoSeguro;
  bool _eliminado;
};

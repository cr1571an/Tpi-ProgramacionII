#pragma once
#include <string>
#include "Fecha.h"
class Vencimiento {
 public:
  Vencimiento();
  Vencimiento(int id, int idPoliza, Fecha vencimiento,float monto, bool eliminado);

  int getId();
  int getIdPoliza();
  Fecha getVencimiento();
  float getMonto();
  bool getEliminado();
  bool estaVencido();

  void setId(int id);
  void setIdPoliza(int idPoliza);
  void setVencimiento(Fecha vencimiento);
  void setMonto(float monto);
  void setEliminado(bool eliminado);

 private:
  int _id;
  int _idPoliza;
  Fecha _vencimiento;
  float _monto;
  bool _eliminado;
};

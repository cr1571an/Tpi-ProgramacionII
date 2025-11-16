#pragma once
#include <string>

#include "Fecha.h"

class Siniestro {
 public:
  Siniestro();
  Siniestro(int id, int idPoliza, Fecha fechaSiniestro,
            int idTipoSiniestro, float costoEstimado, bool estado,
            bool eliminado);

  int getId();
  int getIdPoliza();
  Fecha getFechaSiniestro();
  int getIdTipoSiniestro();
  float getCostoEstimado();
  bool getEstado();
  bool getEliminado();
  void setId(int id);
  void setIdPoliza(int idPoliza);
  void setFechaSiniestro(Fecha fechaSiniestro);
  void setCostoEstimado(float costoEstimado);
  void setIdTipoSiniestro(int idTipoSiniestro);
  void setEstado(bool estado);
  void setEliminado(bool eliminado);

 private:
  int _id;
  int _idPoliza;
  Fecha _fechaSiniestro;
  int _idTipoSiniestro;
  float _costoEstimado;
  bool _estado;
  bool _eliminado;
};
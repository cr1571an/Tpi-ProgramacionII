#pragma once
#include <string>

#include "Fecha.h"

class Siniestro {
 public:
  Siniestro();
  Siniestro(int id, int idPoliza, Fecha fechaSiniestro,
            std::string tipoSiniestro, float costoEstimado, bool estado,
            bool eliminado);

  int getId();
  int getIdPoliza();
  Fecha getFechaSiniestro();
  std::string getTipoSiniestro();
  float getCostoEstimado();
  bool getEstado();
  bool getEliminado();
  void setId(int id);
  void setIdPoliza(int idPoliza);
  void setFechaSiniestro(Fecha fechaSiniestro);
  void setCostoEstimado(float costoEstimado);
  void setTipoSiniestro(std::string tipoSiniestro);
  void setEstado(bool estado);
  void setEliminado(bool eliminado);

 private:
  int _id;
  int _idPoliza;
  Fecha _fechaSiniestro;
  char _tipoSiniestro[15];
  float _costoEstimado;
  bool _estado;
  bool _eliminado;
};
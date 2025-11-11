#pragma once
#include <string>
#include "Fecha.h"

class Pago{
public:
    Pago();
    Pago(int id, int idPoliza, Fecha fechaPago, float monto, std::string metodoDePago, bool estado, bool eliminado);

    int getId();
    int getIdPoliza();
    Fecha getFechaPago();
    float getMonto();
    std::string getMetodoDePago();
    bool getEstado();
    bool getEliminado();

    void setId(int id);
    void setIdPoliza(int idPoliza);
    void setFechaPago(Fecha fechaPago);
    void setMonto(float monto);
    void setMetodoDePago(std::string metodoDePago);
    void setEstado(bool estado);
    void setEliminado(bool eliminado);

private:
    int   _id;
    int   _idPoliza;
    Fecha _fechaPago;
    float _monto;
    char  _metodoDePago[30];
    bool  _estado;
    bool  _eliminado;
};

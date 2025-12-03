#pragma once
#include <string>
#include "Fecha.h"

class Pago
{
public:
    Pago();
    Pago(int id, int idVencimiento, Fecha fechaPago, std::string metodoDePago, bool eliminado);

    int getId();
    int getIdVencimiento();
    Fecha getFechaPago();
    std::string getMetodoDePago();
    bool getEliminado();
    void setId(int id);
    void setIdVencimiento(int idVencimiento);
    void setFechaPago(Fecha fechaPago);
    void setMetodoDePago(std::string metodoDePago);
    void setEliminado(bool eliminado);

private:
    int _id;
    int _idVencimiento;
    Fecha _fechaPago;
    char _metodoDePago[30];
    bool _eliminado;
};

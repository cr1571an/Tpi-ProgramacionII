#include "Pago.h"
#include <cstring>

Pago::Pago():
    _id(0),
    _idVencimiento(0),
    _fechaPago(),
    _monto(0.0),
    _estado(false),
    _eliminado(false)
{
    _metodoDePago[0] = '\0';
}

Pago::Pago(int id, int idVencimiento, Fecha fechaPago, float monto, std::string metodoDePago, bool estado, bool eliminado)
{
    setId(id);
    setIdVencimiento(idVencimiento);
    setFechaPago(fechaPago);
    setMonto(monto);
    setMetodoDePago(metodoDePago);
    setEstado(estado);
    setEliminado(eliminado);
}

int Pago::getId()
{
    return _id;
}
int Pago::getIdVencimiento()
{
    return _idVencimiento;
}
Fecha Pago::getFechaPago()
{
    return _fechaPago;
}
float Pago::getMonto()
{
    return _monto;
}
std::string Pago::getMetodoDePago()
{
    return std::string(_metodoDePago);
}
bool Pago::getEstado()
{
    return _estado;
}
bool Pago::getEliminado()
{
    return _eliminado;
}
void Pago::setId(int id)
{
    _id = id;
}
void Pago::setIdVencimiento(int idVencimiento)
{
    _idVencimiento = idVencimiento;
}
void Pago::setFechaPago(Fecha fechaPago)
{
    _fechaPago = fechaPago;
}
void Pago::setMonto(float monto)
{
    _monto = monto;
}
void Pago::setMetodoDePago(std::string metodoDePago)
{
    strncpy(_metodoDePago, metodoDePago.c_str(), sizeof(_metodoDePago) - 1);
    _metodoDePago [sizeof(_metodoDePago) - 1] = '\0';
}
void Pago::setEstado(bool estado)
{
    _estado = estado;
}
void Pago::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

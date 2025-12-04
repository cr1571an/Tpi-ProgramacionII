#include "Pago.h"
#include <cstring>

Pago::Pago()
    : _id(0),
      _idVencimiento(0),
      _fechaPago(),
      _metodoDePago(""),
      _eliminado(false)
{}

Pago::Pago(int id, int idVencimiento, Fecha fechaPago, std::string metodoDePago, bool eliminado)
{
    setId(id);
    setIdVencimiento(idVencimiento);
    setFechaPago(fechaPago);
    setMetodoDePago(metodoDePago);
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

std::string Pago::getMetodoDePago()
{
    return std::string(_metodoDePago);
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

void Pago::setMetodoDePago(std::string metodoDePago)
{
    strncpy(_metodoDePago, metodoDePago.c_str(), sizeof(_metodoDePago) - 1);
    _metodoDePago[sizeof(_metodoDePago) - 1] = '\0';
}

void Pago::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

#include "Vencimiento.h"
#include <cstring>

Vencimiento::Vencimiento() : _id(0), _idPoliza(0), _vencimiento(), _monto(0), _eliminado(false) {
}
Vencimiento::Vencimiento(int id, int idPoliza, Fecha vencimiento, float monto, bool eliminado) {
    setId(id);
    setIdPoliza(idPoliza);
    setVencimiento(vencimiento);
    setMonto(monto);
    
    setEliminado(eliminado);
}

int Vencimiento::getId() {
    return _id;
}

int Vencimiento::getIdPoliza() {
    return _idPoliza;
}

Fecha Vencimiento::getVencimiento() {
    return _vencimiento;
}
float Vencimiento::getMonto() {
    return _monto;
}
bool Vencimiento::getEliminado() {
    return _eliminado;
}

void Vencimiento::setId(int id) {
    _id = id;
}
void Vencimiento::setIdPoliza(int idPoliza) {
    _idPoliza = idPoliza;
}

void Vencimiento::setVencimiento(Fecha vencimiento) {
    _vencimiento = vencimiento;
}

void Vencimiento::setMonto(float monto) {
    _monto = monto;
}

void Vencimiento::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

bool Vencimiento::estaVencido() {
    Fecha fechaActual;
    if (fechaActual > _vencimiento)
        return true;

    return false;
}
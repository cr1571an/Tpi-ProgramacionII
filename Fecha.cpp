#include <iostream>
#include <ctime>
#include "Fecha.h"

using namespace std;

Fecha::Fecha()
    : _dia(0), _mes(0), _anio(0)
{
    std::time_t t = std::time(nullptr);
    std::tm* ahora = std::localtime(&t);

    _dia  = ahora->tm_mday;
    _mes  = ahora->tm_mon + 1;
    _anio = ahora->tm_year + 1900;
}

Fecha::Fecha(int dia, int mes, int anio){
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

void Fecha::setDia(int dia) {
    if (dia >= 1 && dia <= 31)
        _dia = dia;
    else
        _dia = 0;
}

void Fecha::setMes(int mes) {
    if (mes >= 1 && mes <= 12)
        _mes = mes;
    else
        _mes = 0;
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

int Fecha::getAnio(){
    return _anio;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::diasDelMes(int mes, int anio) {
    static int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        return esBisiesto ? 29 : 28;
    }
    return diasMes[mes - 1];
}


void Fecha::sumarMes(int cantidadMeses) {

    int totalMeses = _anio * 12 + (_mes - 1);
    totalMeses += cantidadMeses;

    int nuevoAnio = totalMeses / 12;
    int nuevoMes = (totalMeses % 12) + 1;

    int diasEnNuevoMes = diasDelMes(nuevoMes, nuevoAnio);

    
    if (_dia > diasEnNuevoMes) {
        _dia = diasEnNuevoMes;
    }

    _anio = nuevoAnio;
    _mes = nuevoMes;
}

bool Fecha::operator>(Fecha fecha) {
    if (_anio != fecha.getAnio())
        return _anio > fecha.getAnio();

    if (_mes != fecha.getMes())
        return _mes > fecha.getMes();

    return _dia > fecha.getDia();
}

bool Fecha::operator==(Fecha fecha) {
    if (_anio != fecha.getAnio())
        return false;

    if (_mes != fecha.getMes())
        return false;

    if (_dia != fecha.getDia())
        return false;

    return true;    
}

bool Fecha::operator<(Fecha fecha) {
    if (_anio != fecha.getAnio())
        return _anio < fecha.getAnio();

    if (_mes != fecha.getMes())
        return _mes < fecha.getMes();

    return _dia < fecha.getDia();
}

bool Fecha::operator>=(Fecha fecha) {
    return *this > fecha || *this == fecha;
}

bool Fecha::operator<=(Fecha fecha) {
    return *this < fecha || *this == fecha;
}

string Fecha::formatoFecha() {
    return to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);
}

int Fecha::validarEdad( Fecha fechaActual) {
    int edad = fechaActual.getAnio() - _anio;

    if (edad > 105) return -1;
    if (edad < 18) return -2;
    if (edad == 18) {
        if (fechaActual.getMes() < _mes ||
            (fechaActual.getMes() == _mes && fechaActual.getDia() < _dia)) {
            return -2;
            }
    }
    if (edad == 105) {
        if (fechaActual.getMes() > _mes ||
            (fechaActual.getMes() == _mes && fechaActual.getDia() >= _dia)) {
            return -1;
            }
    }
    return edad;
}
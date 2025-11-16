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

void Fecha::sumarDias() {
    int plazoPoliza = 90;

    std::tm fecha_tm = {};
    fecha_tm.tm_mday = _dia;
    fecha_tm.tm_mon  = _mes - 1;
    fecha_tm.tm_year = _anio - 1900;

    std::time_t tiempo = std::mktime(&fecha_tm);

    tiempo += static_cast<time_t>(plazoPoliza) * 24 * 60 * 60;

    std::tm* nueva_fecha = std::localtime(&tiempo);

    _dia  = nueva_fecha->tm_mday;
    _mes  = nueva_fecha->tm_mon + 1;
    _anio = nueva_fecha->tm_year + 1900;
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

    return true;
}

string Fecha::formatoFecha() {
    return to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);
}


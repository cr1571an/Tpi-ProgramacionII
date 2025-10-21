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

string Fecha::formatoFecha() {
    return to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);
}


#pragma once
#include <string>

class Fecha{
public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    void sumarMes(int cantidadMeses);
    int validarEdad(Fecha fechaActual);
    bool operator>(Fecha fecha);
    bool operator==(Fecha fecha);
    bool operator<(Fecha fecha);
    bool operator>=(Fecha fecha);
    bool operator<=(Fecha fecha);
    std::string formatoFecha();

private:
    int _dia, _mes, _anio;
    int diasDelMes(int mes, int anio);
};

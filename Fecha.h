#pragma once
#include <string>

class Fecha {
public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();
    int getAnioVencimiento();
    int getDiaVencimiento();
    int getMesVencimiento();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    void sumarDias();
    bool operator>(Fecha fecha);

    std::string formatoFecha(); // mes/dia/anio

private:
    int _dia, _mes, _anio;
};

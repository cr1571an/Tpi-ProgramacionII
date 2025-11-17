#include "Localidad.h"
#include <cstring>

Localidad::Localidad(): _idLocalidad((0)),_codigoPostal(0), _localidad(""), _partido(""){
    }

Localidad::Localidad(int idLocalidad, int codigoPostal, std::string localidad, std::string partido) {
    _idLocalidad = idLocalidad;
    _codigoPostal = codigoPostal;
    setLocalidad(localidad);
    setPartido(partido);
}

int Localidad::getCodigoPostal() {
    return _codigoPostal;
}

int Localidad::getIDLocalidad() {
    return _idLocalidad;
}

std::string Localidad::getLocalidad() {
    return _localidad;
}

std::string Localidad::getPartido() {
    return _partido;
}

void Localidad::setIDLocalidad(int idLocalidad) {
    _idLocalidad = idLocalidad;
}

void Localidad::setLocalidad(std::string localidad) {
    strncpy(_localidad, localidad.c_str(), sizeof(_localidad) - 1);
    _localidad[sizeof(_localidad) - 1] = '\0';
}

void Localidad::setPartido(std::string partido) {
    strncpy(_partido, partido.c_str(), sizeof(_partido) - 1);
    _partido[sizeof(_partido) - 1] = '\0';
}

void Localidad::setCodigoPostal(int codigoPostal) {
    _codigoPostal = codigoPostal;
}

bool Localidad::operator==( Localidad otra)  {
    return _codigoPostal == otra._codigoPostal &&
           getLocalidad() == otra.getLocalidad() &&
           getPartido() == otra.getPartido();
}
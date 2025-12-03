
#include <string>
#include <cstring>
#include "Seguro.h"

Seguro::Seguro() : _id(0),_sumaAsegurada(0.0), _valorPoliza(0.0), _eliminado(false) {
}

Seguro::Seguro(int id, int sumaAsegurada, std::string nombre, float valorPoliza ,bool eliminado) {
    setId(id);
    setSumaAsegurada(sumaAsegurada);
    setNombre(nombre);
    setValorPoliza(valorPoliza);
    setEliminado(eliminado);
}

int Seguro::getId(){ return _id; }

std::string Seguro::getNombre(){ return _nombre; }

float Seguro::getValorPoliza(){ return _valorPoliza; }

int Seguro::getSumaAsegurada(){ return _sumaAsegurada; }

bool Seguro::getEliminado(){ return _eliminado; }

void Seguro::setId(int id) { _id = id; }

void Seguro::setNombre(std::string nombre){
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Seguro::setValorPoliza(float valor){
    _valorPoliza = (valor > 0) ? valor : 0;
}

void Seguro::setSumaAsegurada(int sumaAsegurada){
    _sumaAsegurada = (sumaAsegurada > 0) ? sumaAsegurada : 0;
}

void Seguro::setEliminado(bool eliminado) {_eliminado = eliminado;}

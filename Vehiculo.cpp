#include <string>
#include <cstring>
#include <iostream>

#include "Vehiculo.h"

using namespace std;

Vehiculo::Vehiculo(): _id(0), _idCliente(0), _anio(0), _marca(""), _modelo(""), _patente(""), _catehoria(""), _eliminado(false) {

};

Vehiculo::Vehiculo(int id, int idCliente, int anio, std::string marca, std::string modelo, std::string patente, std::string catehoria) {
    _id = id;
    _idCliente = idCliente;
    setPatente(patente);
    setModelo(modelo);
    setCatehoria(catehoria);
    setEliminado(false);
    setMarca(marca);
    setAnio(anio);
};

void Vehiculo::setMarca(std::string marca) {
    strncpy(_marca, marca.c_str(), 19);
    _marca[19] = '\0';
};

void Vehiculo::setModelo(std::string modelo) {
    strncpy(_modelo, modelo.c_str(), 19);
    _modelo[19] = '\0';
};

void Vehiculo::setPatente(std::string patente) {
    strncpy(_patente, patente.c_str(), 9);
    _patente[9] = '\0';
};

void Vehiculo::setCatehoria(std::string catehoria) {
    strncpy(_catehoria, catehoria.c_str(), 19);
    _catehoria[19] = '\0';
};

void Vehiculo::setEliminado(bool eliminado) {
    if (eliminado) {
        _eliminado = true;
    }
    else {
        _eliminado = false;
    }
};

void Vehiculo::setAnio(int anio) {
    if (anio >= 1900 && anio <= 2026) {
        _anio = anio;
    }
};

int Vehiculo::getIdVehiculo() {return _id;};

int Vehiculo::getIdCliente() {return _idCliente;};

int Vehiculo::getAnio() {return _anio;};

std::string Vehiculo::getMarca() {return _marca;};

std::string Vehiculo::getModelo() {return _modelo;};

std::string Vehiculo::getPatente() {return _patente;};

std::string Vehiculo::getCatehoria() {return _catehoria;};

bool Vehiculo::getEliminado() {return _eliminado;};

void Vehiculo::eliminar() {_eliminado = true;};

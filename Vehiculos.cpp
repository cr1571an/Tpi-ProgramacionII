#include <string>
#include <cstring>
#include <iostream>

#include "Vehiculos.h"

using namespace std;

Vehiculos::Vehiculos(): _id(0), _idCliente(0), _anio(0), _marca(""), _modelo(""), _patente(""), _catehoria(""), _eliminado(false) {

};

Vehiculos::Vehiculos(int id, int idCliente, int anio, std::string marca, std::string modelo, std::string patente, std::string catehoria) {
    _id = id;
    _idCliente = idCliente;
    setPatente(patente);
    setModelo(modelo);
    setCatehoria(catehoria);
    setEliminado(false);
    setMarca(marca);
    setAnio(anio);
};

void Vehiculos::setMarca(std::string marca) {
    strncpy(_marca, marca.c_str(), 19);
    _marca[19] = '\0';
};

void Vehiculos::setModelo(std::string modelo) {
    strncpy(_modelo, modelo.c_str(), 19);
    _modelo[19] = '\0';
};

void Vehiculos::setPatente(std::string patente) {
    strncpy(_patente, patente.c_str(), 9);
    _patente[9] = '\0';
};

void Vehiculos::setCatehoria(std::string catehoria) {
    strncpy(_catehoria, catehoria.c_str(), 19);
    _catehoria[19] = '\0';
};

void Vehiculos::setEliminado(bool eliminado) {
    if (eliminado) {
        _eliminado = true;
    }
    else {
        _eliminado = false;
    }
};

void Vehiculos::setAnio(int anio) {
    if (anio >= 1900 && anio <= 2026) {
        _anio = anio;
    }
};

int Vehiculos::getIdVehiculos() {return _id;};

int Vehiculos::getIdCliente() {return _idCliente;};

int Vehiculos::getAnio() {return _anio;};

std::string Vehiculos::getMarca() {return _marca;};

std::string Vehiculos::getModelo() {return _modelo;};

std::string Vehiculos::getPatente() {return _patente;};

std::string Vehiculos::getCatehoria() {return _catehoria;};

bool Vehiculos::getEliminado() {return _eliminado;};

void Vehiculos::eliminar() {_eliminado = true;};

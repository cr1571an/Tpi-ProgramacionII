#include <string>
#include <cstring>
#include <iostream>

#include "Vehiculos.h"

using namespace std;

Vehiculos::Vehiculos(): _id(0), _idCliente(0), _anio(0), _marca(""), _modelo(""), _patente(""), _categoria(""),
                        _eliminado(false), _numChasis(""), _numMotor(""), _uso("") {
};

Vehiculos::Vehiculos(int id, int idCliente, int anio, std::string marca, std::string modelo,
        std::string patente, std::string categoria, std::string numChasis, std::string numMotor, std::string uso) {
    _id = id;
    _idCliente = idCliente;
    setPatente(patente);
    setModelo(modelo);
    setCatehoria(categoria);
    setEliminado(false);
    setMarca(marca);
    setAnio(anio);
    setNumChasis(numChasis);
    setNumMotor(numMotor);
    setUso(uso);
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
    strncpy(_categoria, catehoria.c_str(), 19);
    _categoria[19] = '\0';
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

void Vehiculos::setUso(std::string uso) {
    strncpy(_uso, uso.c_str(), 19);
    _uso[19] = '\0';
}

std::string Vehiculos::getUso() {
    return _uso;
}


void Vehiculos::setNumChasis(std::string numChasis) {
    strncpy(_numChasis, numChasis.c_str(), 19);
    _numChasis[19] = '\0';
}

std::string Vehiculos::getNumChasis() {
    return _numChasis;
}

void Vehiculos::setNumMotor(std::string numMotor) {
    strncpy(_numMotor, numMotor.c_str(), 19);
    _numMotor[19] = '\0';
}

std::string Vehiculos::getNumMotor() {
    return _numMotor;
}

int Vehiculos::getIdVehiculos() {return _id;};

int Vehiculos::getIdCliente() {return _idCliente;};

int Vehiculos::getAnio() {return _anio;};

std::string Vehiculos::getMarca() {return _marca;};

std::string Vehiculos::getModelo() {return _modelo;};

std::string Vehiculos::getPatente() {return _patente;};

std::string Vehiculos::getCatehoria() {return _categoria;};

bool Vehiculos::getEliminado() {return _eliminado;};

void Vehiculos::eliminar() {_eliminado = true;};

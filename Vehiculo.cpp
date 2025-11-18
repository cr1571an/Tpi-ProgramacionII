#include <string>
#include <cstring>
#include <iostream>

#include "Vehiculo.h"

using namespace std;

Vehiculo::Vehiculo(): _id(0), _idCliente(0), _anio(""), _marca(""), _modelo(""), _patente(""), _categoria(""),
                        _numMotor(""), _numChasis(""), _uso(""),_eliminado(false) {
}

Vehiculo::Vehiculo(int id, int idCliente, std::string anio, std::string marca, std::string modelo,
        std::string patente, std::string categoria, bool eliminado,std::string numChasis, std::string numMotor, std::string uso) {
    setIdVehiculo(id);
    setIdCliente(idCliente);
    setPatente(patente);
    setModelo(modelo);
    setCategoria(categoria);
    setEliminado(eliminado);
    setMarca(marca);
    setAnio(anio);
    setNumChasis(numChasis);
    setNumMotor(numMotor);
    setUso(uso);
}


void Vehiculo::setIdVehiculo(int id) { _id = id; }

void Vehiculo::setIdCliente(int id) { _idCliente = id; }

void Vehiculo::setMarca(std::string marca) {
    strncpy(_marca, marca.c_str(), 19);
    _marca[19] = '\0';
}

void Vehiculo::setModelo(std::string modelo) {
    strncpy(_modelo, modelo.c_str(), 19);
    _modelo[19] = '\0';
}

void Vehiculo::setPatente(std::string patente) {
    strncpy(_patente, patente.c_str(), 9);
    _patente[9] = '\0';
}

void Vehiculo::setCategoria(std::string catehoria) {
    strncpy(_categoria, catehoria.c_str(), 19);
    _categoria[19] = '\0';
}

void Vehiculo::setEliminado(bool eliminado) {
    if (eliminado) {
        _eliminado = true;
    }
    else {
        _eliminado = false;
    }
}

void Vehiculo::setAnio(std::string anio) {
    int anioInt = atoi(anio.c_str());
    if (anioInt >= 1900 && anioInt <= 2026) {
        strncpy(_anio, anio.c_str(), sizeof(_anio) - 1);
        _anio[sizeof(_anio) - 1] = '\0';
    }
}

void Vehiculo::setUso(std::string uso) {
    strncpy(_uso, uso.c_str(), 19);
    _uso[19] = '\0';
}

std::string Vehiculo::getUso() {
    return _uso;
}


void Vehiculo::setNumChasis(std::string numChasis) {
    strncpy(_numChasis, numChasis.c_str(), 19);
    _numChasis[19] = '\0';
}

std::string Vehiculo::getNumChasis() {
    return _numChasis;
}

void Vehiculo::setNumMotor(std::string numMotor) {
    strncpy(_numMotor, numMotor.c_str(), 19);
    _numMotor[19] = '\0';
}

std::string Vehiculo::getNumMotor() {
    return _numMotor;
}

int Vehiculo::getIdVehiculo() {return _id;}

int Vehiculo::getIdCliente() {return _idCliente;}

std::string Vehiculo::getAnio() {return _anio;}

std::string Vehiculo::getMarca() {return _marca;}

std::string Vehiculo::getModelo() {return _modelo;}

std::string Vehiculo::getPatente() {return _patente;}

std::string Vehiculo::getCategoria() {return _categoria;}

bool Vehiculo::getEliminado() {return _eliminado;}

void Vehiculo::eliminar() {_eliminado = true;}

void Vehiculo::recuperar() {_eliminado = false;}

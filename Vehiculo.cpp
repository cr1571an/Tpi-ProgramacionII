#include <string>
#include <cstring>
#include <iostream>

#include "Vehiculo.h"

using namespace std;

Vehiculo::Vehiculo(): _id(0), _idCliente(0), _anio(0), _marca(""), _modelo(""), _patente(""), _categoria(""),
                        _numMotor(""), _numChasis(""), _uso(""),_eliminado(false) {
}

Vehiculo::Vehiculo(int id, int idCliente, int anio, std::string marca, std::string modelo,
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

void Vehiculo::setMarca(string marca) {
    strncpy(_marca, marca.c_str(),sizeof(_marca) - 1);
    _marca[sizeof(_marca) - 1] = '\0';
}

void Vehiculo::setModelo(string modelo) {
    strncpy(_modelo, modelo.c_str(), sizeof(_modelo) - 1);
    _modelo[sizeof(_modelo) - 1] = '\0';
}

void Vehiculo::setPatente(string patente) {
    strncpy(_patente, patente.c_str(), sizeof(_patente) - 1);
    _patente[sizeof(_patente) - 1] = '\0';
}

void Vehiculo::setCategoria(string catehoria) {
    strncpy(_categoria, catehoria.c_str(), sizeof(_categoria) - 1);
    _categoria[sizeof(_categoria) - 1] = '\0';
}

void Vehiculo::setEliminado(bool eliminado) {
    if (eliminado) {
        _eliminado = true;
    }
    else {
        _eliminado = false;
    }
}

void Vehiculo::setAnio(int anio) {
    if (anio >= 1900 && anio < 2026) {
        _anio=anio;
    }
    else {_anio = 0;}
}

void Vehiculo::setUso(string uso) {
    strncpy(_uso, uso.c_str(), sizeof(_uso) - 1);
    _uso[sizeof(_uso) - 1] = '\0';
}

string Vehiculo::getUso() {
    return _uso;
}


void Vehiculo::setNumChasis(string numChasis) {
    strncpy(_numChasis, numChasis.c_str(), sizeof(_numChasis) - 1);
    _numChasis[sizeof(_numChasis) - 1] = '\0';
}

string Vehiculo::getNumChasis() {
    return _numChasis;
}

void Vehiculo::setNumMotor(string numMotor) {
    strncpy(_numMotor, numMotor.c_str(),sizeof(_numMotor) - 1);
    _numMotor[sizeof(_numMotor) - 1] = '\0';
}

string Vehiculo::getNumMotor() {
    return _numMotor;
}

int Vehiculo::getIdVehiculo() {return _id;}

int Vehiculo::getIdCliente() {return _idCliente;}

int Vehiculo::getAnio() {return _anio;}

string Vehiculo::getMarca() {return _marca;}

string Vehiculo::getModelo() {return _modelo;}

string Vehiculo::getPatente() {return _patente;}

string Vehiculo::getCategoria() {return _categoria;}

bool Vehiculo::getEliminado() {return _eliminado;}

void Vehiculo::eliminar() {_eliminado = true;}

void Vehiculo::recuperar() {_eliminado = false;}

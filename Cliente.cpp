#include <string>
#include <cstring>
#include "Cliente.h"

Cliente::Cliente()
 : _idCliente(0), _codigoPostal(0), _eliminado(false), _localidad(), _fechaNacimiento() {
    _nombre[0] = '\0';
    _apellido[0] = '\0';
    _dni[0] = '\0';
    _telefono[0] = '\0';
    _email[0] = '\0';
}

Cliente::Cliente(int idCliente, std::string nombre, std::string apellido,std::string dni, std::string telefono,
                std::string email, bool eliminado, Localidad localidad, Fecha fechaNacimiento){
    _idCliente = idCliente;
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    setTelefono(telefono);
    setEmail(email);
    _eliminado = eliminado;
    _localidad = localidad;
    _fechaNacimiento = fechaNacimiento;
}

void Cliente::setNombre(std::string nombre) {
    strncpy(_nombre, nombre.c_str(),sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Cliente::setApellido(std::string apellido) {
    strncpy(_apellido, apellido.c_str(), sizeof(_apellido) - 1);
    _apellido[sizeof(_apellido) - 1] = '\0';
}

void Cliente::setDni(std::string dni) {
    strncpy(_dni, dni.c_str(), sizeof(_dni) - 1);
    _dni[sizeof(_dni) - 1] = '\0';
}

void Cliente::setTelefono(std::string telefono) {
    strncpy(_telefono, telefono.c_str(), sizeof(_telefono) - 1);
    _telefono[sizeof(_telefono) - 1] = '\0';
}

void Cliente::setEmail(std::string email) {
    strncpy(_email, email.c_str(), sizeof(_email) - 1);
    _email[sizeof(_email) - 1] = '\0';
}

void Cliente::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

void Cliente::eliminar() {
    _eliminado = true;
}

void Cliente::recuperar() {
    _eliminado = false;
}

void Cliente::setIdCliente(int idCliente) {
    _idCliente = idCliente;
}

void Cliente::setCodigoPostal(int codigoPostal) {
    _codigoPostal = codigoPostal;
}

void Cliente::setLocalidad(Localidad localidad) {
    _localidad = localidad;
}

void Cliente::setFechaNacimiento(Fecha fechaNacimiento) {
    _fechaNacimiento = fechaNacimiento;
}

int Cliente::getIdCliente() { return _idCliente; }

std::string Cliente::getNombre() { return _nombre; }

std::string Cliente::getApellido() { return _apellido; }

std::string Cliente::getDni() { return _dni; }

std::string Cliente::getTelefono() { return _telefono; }

std::string Cliente::getEmail() { return _email; }

bool Cliente::getEliminado() { return _eliminado; }

Localidad Cliente::getLocalidad() { return _localidad; }

Fecha Cliente::getFechaNacimiento() { return _fechaNacimiento; }

bool Cliente::operator==(Cliente otro) {
    return getDni() == otro.getDni();
}


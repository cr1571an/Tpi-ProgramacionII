#include <string>
#include <cstring>
#include "Clientes.h"


    Cliente::Cliente(): _idCliente(0), _nombre("") , _apellido(""), _dni(""), _telefono(""), _email(""), _eliminado(false), _codigoPostal(0) {
        _localidad = Localidad();
    };

    Cliente::Cliente(int idCliente, std::string nombre, std::string apellido, std::string dni, std::string telefono, std::string email, Localidad localidad, Fecha fechaNacimiento) {
        _idCliente = idCliente;
        setNombre(nombre);
        setApellido(apellido);
        setDni(dni);
        setTelefono(telefono);
        setEmail(email);
        setEliminado(false);
        _localidad = localidad;
        _fechaNacimiento = fechaNacimiento;
    };

    void Cliente::setNombre(std::string nombre) {
        strncpy(_nombre, nombre.c_str(), 19);
        _nombre[19] = '\0';
    };

    void Cliente::setApellido(std::string apellido) {
        strncpy(_apellido, apellido.c_str(), 19);
        _apellido[19] = '\0';
    };

    void Cliente::setDni(std::string dni) {
        strncpy(_dni, dni.c_str(), 8);
        _dni[8] = '\0';
    };

    void Cliente::setTelefono(std::string telefono) {
        strncpy(_telefono, telefono.c_str(), 19);
        _telefono[19] = '\0';
    };

    void Cliente::setEmail(std::string email) {
        strncpy(_email, email.c_str(), 49);
        _email[49] = '\0';
    };

    void Cliente::setEliminado(bool eliminado) {
        _eliminado = eliminado;
    };

    void Cliente::eliminar() {
        _eliminado = true;
    };

    void Cliente::recuperar() {
        _eliminado = false;
    };

    void Cliente::setIdCliente(int idCliente) {
        _idCliente = idCliente;
    };

    void Cliente::setCodigoPostal(int codigoPostal) {
        _codigoPostal = codigoPostal;
    };

    void Cliente::setLocalidad(Localidad localidad) {
        _localidad = localidad;
    };

    void Cliente::setFechaNacimiento(Fecha fechaNacimiento) {
        _fechaNacimiento = fechaNacimiento;
    };

    int Cliente::getIdCliente() {return _idCliente;};

    std::string Cliente::getNombre() {return _nombre;}

    std::string Cliente::getApellido() {return _apellido;};

    std::string Cliente::getDni() {return _dni;};

    std::string Cliente::getTelefono() {return _telefono;};

    std::string Cliente::getEmail() {return _email;};

    bool Cliente::getEliminado() {return _eliminado;};

    Localidad Cliente::getLocalidad(){return _localidad;};

    Fecha Cliente::getFechaNacimiento(){return _fechaNacimiento;};

#pragma once
#include "Localidad.h"
#include "Fecha.h"

class Cliente {
    public:
        Cliente();
        Cliente(int idCliente, std::string nombre, std::string apellido,
                std::string dni, std::string telefono, std::string email,
                bool eliminado,Localidad localidad, Fecha fechaNacimiento);

        void setNombre(std::string nombre);
        void setApellido(std::string apellido);
        void setDni(std::string dni);
        void setTelefono(std::string telefono);
        void setEmail(std::string email);
        void setEliminado(bool eliminado);
        void setCodigoPostal(int codigoPostal);
        void recuperar();
        void eliminar();
        void setIdCliente(int idCliente);

        void setLocalidad(Localidad localidad);
        Localidad getLocalidad();
        void setFechaNacimiento(Fecha fechaNacimiento);
        Fecha getFechaNacimiento();

        int getCodigoPostal();
        std::string getNombre();
        std::string getApellido();
        std::string getDni();
        std::string getTelefono();
        std::string getEmail();
        int getIdCliente();
        bool getEliminado();
        bool getRecuperar();

    private:
        int _idCliente, _codigoPostal;
        char _nombre[20], _apellido[20],  _dni[9], _telefono[20], _email[50];
        bool _eliminado;
        Localidad _localidad;
        Fecha _fechaNacimiento;
};


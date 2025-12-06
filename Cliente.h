#pragma once
#include "Fecha.h"

class Cliente {
    public:
        Cliente();
        Cliente(int idCliente, std::string nombre, std::string apellido,
                std::string dni, std::string telefono, std::string email,
                std::string partido, std::string localidad, bool eliminado, Fecha fechaNacimiento);

        void setNombre(std::string nombre);
        void setApellido(std::string apellido);
        void setDni(std::string dni);
        void setTelefono(std::string telefono);
        void setEmail(std::string email);
        void setEliminado(bool eliminado);
        void setCodigoPostal(int codigoPostal);
        void setPartido(std::string partido);
        void setLocalidad(std::string localidad);
        void recuperar();
        void eliminar();
        void setIdCliente(int idCliente);

        void setFechaNacimiento(Fecha fechaNacimiento);
        Fecha getFechaNacimiento();

        std::string getNombre();
        std::string getApellido();
        std::string getDni();
        std::string getTelefono();
        std::string getEmail();
        std::string getPartido();
        std::string getLocalidad();
        int getIdCliente();
        bool getEliminado();
        bool operator==( Cliente otro);

    private:
        int _idCliente, _codigoPostal;
        char _nombre[25], _apellido[20],  _dni[9], _telefono[20], _email[50], _partido[50], _localidad[70];
        bool _eliminado;
        Fecha _fechaNacimiento;
};


#pragma once

class Cliente {
    public:
        Cliente();
        Cliente(int idCliente, std::string nombre, std::string apellido, std::string dni, std::string telefono, std::string email);
        void setIdCliente(int idCliente);
        void setNombre(std::string nombre);
        void setApellido(std::string apellido);
        void setDni(std::string dni);
        void setTelefono(std::string telefono);
        void setEmail(std::string email);
        void setEliminado(bool eliminado);
        void recuperar();
        void eliminar();
        int getIdCliente();
        std::string getNombre();
        std::string getApellido();
        std::string getDni();
        std::string getTelefono();
        std::string getEmail();
        bool getRecuperar();
        bool getEliminado();


    private:
        int _idCliente;
        char _nombre[20], _apellido[20],  _dni[9], _telefono[20], _email[50];
        bool _eliminado;
};


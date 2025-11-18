#pragma once
#include <string>

class Vehiculo {
    public:
        Vehiculo();
        Vehiculo(int id, int idCliente, int anio, std::string marca, std::string modelo,
            std::string patente, std::string categoria, bool eliminado, std::string numChasis, std::string numMotor, std::string uso);

        void setIdVehiculo(int id);
        void setIdCliente(int idCliente);
        void setAnio(int anio);
        void setMarca(std::string marca);
        void setModelo(std::string modelo);
        void setPatente(std::string patente);
        void setCategoria(std::string catehoria);
        void setEliminado(bool eliminado);
        void eliminar();
        void recuperar();
        void setNumMotor(std::string numMotor);
        void setNumChasis(std::string numChasis);
        void setUso(std::string uso);

        bool getEliminado();

        int getIdVehiculo();
        int getIdCliente();
        int getAnio();

        std::string getUso();
        std::string getNumChasis();
        std::string getNumMotor();
        std::string getMarca();
        std::string getModelo();
        std::string getPatente();
        std::string getCategoria();


    private:
        int _id, _idCliente, _anio;
        char _marca[20], _modelo[20], _patente[10], _categoria[20], _numMotor[20], _numChasis[20], _uso[20];
        bool _eliminado;
};



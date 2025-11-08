#pragma once
#include <string>

class Vehiculos {
    public:
    Vehiculos();
    Vehiculos(int id, int idCliente, int anio, std::string marca, std::string modelo,
        std::string patente, std::string categoria, std::string numChasis, std::string numMotor, std::string uso);
    void setMarca(std::string marca);
    void setModelo(std::string modelo);
    void setPatente(std::string patente);
    void setCatehoria(std::string catehoria);
    void setEliminado(bool eliminado);
    void eliminar();
    void setAnio(int anio);
    void setNumMotor(std::string numMotor);
    void setNumChasis(std::string numChasis);
    void setUso(std::string uso);

    std::string getUso();
    std::string getNumChasis();
    std::string getNumMotor();
    bool getEliminado();
    int getIdVehiculos();
    int getIdCliente();
    int getAnio();
    std::string getMarca();
    std::string getModelo();
    std::string getPatente();
    std::string getCatehoria();


    private:
    int _id, _idCliente, _anio;
    char _marca[20], _modelo[20], _patente[10], _categoria[20], _numMotor[20], _numChasis[20], _uso[20];
    bool _eliminado;
};



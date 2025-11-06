#pragma once
#include <string>

class Vehiculo {
    public:
    Vehiculo();
    Vehiculo(int id, int idCliente, int anio, std::string marca, std::string modelo, std::string patente, std::string catehoria);
    void setMarca(std::string marca);
    void setModelo(std::string modelo);
    void setPatente(std::string patente);
    void setCatehoria(std::string catehoria);
    void setEliminado(bool eliminado);
    void eliminar();
    void setAnio(int anio);

    bool getEliminado();
    int getIdVehiculo();
    int getIdCliente();
    int getAnio();
    std::string getMarca();
    std::string getModelo();
    std::string getPatente();
    std::string getCatehoria();


    private:
    int _id, _idCliente, _anio;
    char _marca[20], _modelo[20], _patente[10], _catehoria[20];
    bool _eliminado;
};



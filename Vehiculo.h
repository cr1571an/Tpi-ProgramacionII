#pragma once
#include <string>

class Vehiculo {
    public:
    Vehiculo();
    Vehiculo(int id, int idCliente, std::string anio, std::string marca, std::string modelo, std::string patente, std::string categoria, bool eliminado);
    void setId(int id);
    void setIdCliente(int id);
    void setAnio(std::string anio);
    void setMarca(std::string marca);
    void setModelo(std::string modelo);
    void setPatente(std::string patente);
    void setCategoria(std::string catehoria);
    void setEliminado(bool eliminado);
    void eliminar();
    
    int getId();
    int getIdCliente();
    std::string getAnio();
    std::string getMarca();
    std::string getModelo();
    std::string getPatente();
    std::string getCategoria();
    bool getEliminado();

    private:
    int _id, _idCliente;
    char _anio[4],_marca[20], _modelo[20], _patente[10], _categoria[20];
    bool _eliminado;
};



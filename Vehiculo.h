#pragma once
#include <string>

class Vehiculo {
    public:
    Vehiculo();
    Vehiculo(int id, int idCliente, std::string anio, std::string marca, std::string modelo,
        std::string patente, std::string categoria, std::string numChasis, std::string numMotor, std::string uso);
    void setId(int id);
    void setIdCliente(int idCliente);
    void setMarca(std::string marca);
    void setModelo(std::string modelo);
    void setPatente(std::string patente);
    void setCategoria(std::string catehoria);
    void setEliminado(bool eliminado);
    void eliminar();
    void setAnio(std::string anio);
    void setNumMotor(std::string numMotor);
    void setNumChasis(std::string numChasis);
    void setUso(std::string uso);

    std::string getUso();
    std::string getNumChasis();
    std::string getNumMotor();
    bool getEliminado();
    int getId();
    int getIdCliente();
    std::string getAnio();
    std::string getMarca();
    std::string getModelo();
    std::string getPatente();
    std::string getCategoria();


    private:
    int _id, _idCliente;
    char _anio[5],_marca[20], _modelo[20], _patente[10], _categoria[20], _numMotor[20], _numChasis[20], _uso[20];
    bool _eliminado;
};



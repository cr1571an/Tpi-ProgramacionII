
#pragma once
#include <string>

class Seguro {
public:
    Seguro();
    Seguro(int id, int sumaAsegurada, std::string nombre, float valorPoliza, bool eliminado);

    int getId();
    std::string getNombre();
    float getValorPoliza();
    int getSumaAsegurada();
    bool getEliminado();

    void setId(int id);
    void setNombre(std::string nombre);
    void setValorPoliza(float valor);
    void setSumaAsegurada(int sumaAsegurada);
    void setEliminado(bool eliminado);

private:
    int _id, _sumaAsegurada;
    char _nombre[50];
    float _valorPoliza;
    bool _eliminado;
};

#pragma once
#include "Seguro.h"
#include <string>

#include "Vehiculo.h"

class SeguroArchivo {
public:
    SeguroArchivo(std::string nombreArchivo = "Seguros.dat");
    bool guardar(Seguro registro);
    int buscarIdSeguro(int id);
    Seguro leer(int pos);
    int leerTodos(Seguro seguro[], int cantidad);
    int getCantidadRegistros();
    int getIdSeguroUltimo();
    bool eliminar(int id);
    bool actualizarRegistro(int pos, Seguro registro);
    bool recuperar(int id);

    void cargarSeguro();
    void mostrarMenu();
    void mostrarLista(Seguro seguro, bool mostrar);
    void mostrarSeguros();
    void modificarValorPoliza();
    void modificarNombrePoliza();
    void configurarPorcentajes();
    void modificarSumaAsegurada();
    int seleccionarSeguro();
    float calcularValorPoliza(int idSeguro,Vehiculo vehiculo);
    float calcularSumaAsegurada(int idSeguro, Vehiculo vehiculo);

    void cargarPorcentajes();
    void guardarPorcentajes();

private:
    std::string nombreArchivo;
};

#pragma once
#include "Localidad.h"
#include <string>

class LocalidadArchivo {
    public:
        LocalidadArchivo();
        LocalidadArchivo(std::string nombreArchivo);

        bool guardar(Localidad registro);
        Localidad leer(int pos);
        int leerTodos(Localidad registros[], int cantidad);
        int getCantidadRegistros();
        int buscarPorCodigoPostal(int codigoPostal);
        Localidad pedirLocalidadPorCodigoPostal();
        int listarPorCodigoPostal(int codigoPostal, Localidad coincidencias[], int max);
        Localidad pedirLocalidadPorCodigoPostalInteractivo();
        void mostrarLocalidad(Localidad loc);
        void mostrar();

    private:
        int buscarCoincidenciasPorCodigoPostal(int codigoPostal, Localidad coincidencias[], int maxCoincidencias);
        void mostrarOpcionesLocalidad(Localidad coincidencias[], int cantCoincidencias);

        std::string _nombreArchivo;
};



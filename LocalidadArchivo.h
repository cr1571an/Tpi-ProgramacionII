#pragma once
#include "Localidad.h"
#include <string>

class LocalidadArchivo {
    public:
        LocalidadArchivo();
        LocalidadArchivo(std::string nombreArchivo);

        void mostrarLocalidad(Localidad loc);
        void mostrar();
        void cargarLocalidad();

        bool guardar(Localidad registro);
        bool existeLocalidad( Localidad loc);

        int leerTodos(Localidad registros[], int cantidad);
        int getCantidadRegistros();
        int buscarPorCodigoPostal(int codigoPostal);
        int getUltimoID();
        int listarPorCodigoPostal(int codigoPostal, Localidad coincidencias[], int max);
        int partidosUnicos(std::string partidos[], int maxPartidos);

        Localidad leer(int pos);
        Localidad pedirLocalidadPorCodigoPostal();
        Localidad pedirLocalidadPorCodigoPostalInteractivo();

    private:
        void mostrarOpcionesLocalidad(Localidad coincidencias[], int cantCoincidencias);
        int buscarCoincidenciasPorCodigoPostal(int codigoPostal, Localidad coincidencias[], int maxCoincidencias);

        std::string _nombreArchivo;
};



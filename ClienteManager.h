#pragma once
#include "ClientesArchivo.h"

class ClienteManager {
    public:
        ClienteManager();
        void cargar();
        void mostrar();
        void eliminar(int id);
        void actualizar();
        void mostrarDatosDeClienteDNI(std::string dni);
        int getUltimoId();

    protected:
        void mostrarLista(Cliente cliente);
    private:
        ClientesArchivo _clientesArchivo;
};



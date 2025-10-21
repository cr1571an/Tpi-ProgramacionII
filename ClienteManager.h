#pragma once
#include "ClientesArchivo.h"

class ClienteManager {
    public:
        ClienteManager();
        void cargar();
        void mostrar();
        void eliminar(int id);
        void actualizar();

    protected:
        void mostrarLista(Cliente cliente);
    private:
        ClientesArchivo _clientesArchivo;
};



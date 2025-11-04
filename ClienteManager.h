#pragma once
#include "ClientesArchivo.h"

class ClienteManager {
    public:
        ClienteManager();
        void cargar();
        void mostrar();
        bool eliminar(int id);
        bool recuperar(int id);
        void actualizar();
        void mostrarDatosDeClienteDNI();
        int getUltimoId();
        bool eliminarPorDNI();
        bool recuperarPorDNI();
        int buscarIdClientePorDNI(const std::string& dni);

    protected:
        void mostrarLista(Cliente cliente);

    private:
        ClientesArchivo _clientesArchivo;
};



#pragma once
#include <string>
#include  "ClientesArchivo.h"
#include "Clientes.h"

class ClientesArchivo {
        public:
        ClientesArchivo(std::string nombreArchivo = "Clientes.dat");
        bool guardar(Cliente registro);
        int buscarID(int id);
        Cliente leer(int pos);
        int leerTodos(Cliente cliente[], int cantidad);
        int getCantidadRegistros();
        int getID();
        bool eliminar(int id);

        private:
        std::string _nombreArchivo;
};




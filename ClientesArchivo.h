#pragma once
#include <string>
#include  "ClientesArchivo.h"
#include "Clientes.h"

class ClientesArchivo {
        public:
                ClientesArchivo(std::string nombreArchivo = "Clientes.dat");
                bool guardar(Cliente registro);
                int buscarID(int id);
                int buscarDNI(std::string dni);
                Cliente leer(int pos);
                int leerTodos(Cliente cliente[], int cantidad);
                int getCantidadRegistros();
                int getID();
                bool eliminar(int id);
                bool actualizarRegistro(int pos, Cliente registro);
                bool recuperar(int id);

        private:
                std::string _nombreArchivo;
};




#pragma once
#include <string>
#include  "ClientesArchivo.h"
#include "Cliente.h"

class ClientesArchivo {
        public:
                ClientesArchivo(std::string nombreArchivo = "Clientes.dat");
                bool guardar(Cliente registro);
                int buscarIdCliente(int id);
                Cliente leer(int pos);
                int leerTodos(Cliente cliente[], int cantidad);
                int getCantidadRegistros();
                int getIdClienteUltimo();
                bool eliminar(int id);
                bool actualizarRegistro(int pos, Cliente registro);
                bool recuperar(int id);

        private:
                std::string _nombreArchivo;
};




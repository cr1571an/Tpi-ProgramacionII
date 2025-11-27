#pragma once
#include "Vehiculo.h"
#include "VehiculosArchivo.h"
#include "ClienteManager.h"
#include <string>

class VehiculoManager {
    public:
        VehiculoManager();
        void cargar(int iDCliente);
        void mostrar();
        void eliminar(int idVehiculo);
        void modificarPatente(int id);
        void modificarUso(int id);
        void modificarCategoria(int id);
        void modificarNumChasis(int id);
        void modificarNumMotor(int id);
        void modificarAnio(int id);
        void mostrarPantalla(Cliente cli, int id, std::string marca, std::string modelo, std::string patente, int anio, std::string chasis, std::string motor, std::string uso = "", std::string categoria = "");

        bool estadoCliente(int idCliente);
        int buscarIdPorPatente(std::string patente);
        int posVehiculoPorClienteId(int idCliente);
        int mostrarYContarVehiculosDeCliente(int idClienteBuscado);

        std::string nombreApellidoClinete(int idCliente);
        bool buscarNumMotor(std::string numMotor);
        bool buscarNumChasis(std::string numChasis);
        void mostrarLista(Vehiculo vehiculo);

    private:
        VehiculosArchivo _vehiculosArchivo;
        ClientesArchivo _clientesArchivo;

};

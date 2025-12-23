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
        bool recuperar(int idVehiculo);
        int buscarIdPorPatente(std::string patente);
        int mostrarYContarVehiculosDeCliente(int idClienteBuscado);
        void mostrarLista(Vehiculo vehiculo);
        void modificarPatente(int id);
        void modificarUso(int id);
        void modificarCategoria(int id);
        void modificarNumChasis(int id);
        void modificarNumMotor(int id);
        void modificarAnio(int id);
    private:
    
        void mostrarPantalla(Cliente cli, int id, std::string marca, std::string modelo, std::string patente, int anio, std::string chasis, std::string motor, std::string uso = "", std::string categoria = "");
        bool estadoCliente(int idCliente);
        int posVehiculoPorClienteId(int idCliente);        
        bool buscarNumMotor(std::string numMotor);
        bool buscarNumChasis(std::string numChasis);

        VehiculosArchivo _vehiculosArchivo;
        ClientesArchivo _clientesArchivo;
};

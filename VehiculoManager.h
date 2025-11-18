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
        void mostrarVehiculosDeCliente(int idClienteBuscado);
        void mensajeErrorNumeroChasis();
        void mensajeErrorNumeroMotor();
        void mensajeErrorPatente();
        void modificarPatente(int id);
        void modificarUso(int id);
        void modificarCategoria(int id);
        void modificarNumChasis(int id);
        void modificarNumMotor(int id);
        void modificarAnio(int id);
        void cantidadVehiculosPorEstado();
        void listadoEliminados(bool mostrarTotalVehiculosEliminados);
        void listadoActivos(bool mostrarTotalVehiculosActivos);
        void reporteCantidadPorCategoria();
        void reporteCantidadPorUso();

        bool estadoCliente(int idCliente);
        int buscarIdPorPatente(std::string patente);

        std::string nombreApellidoClinete(int idCliente);
        bool buscarNumMotor(std::string numMotor);
        bool buscarNumChasis(std::string numChasis);
        void mostrarLista(Vehiculo vehiculo);

    private:
        VehiculosArchivo _vehiculosArchivo;
        ClientesArchivo _clientesArchivo;

};

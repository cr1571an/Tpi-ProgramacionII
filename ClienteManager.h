#pragma once
#include "ClientesArchivo.h"

class ClienteManager {
public:
    ClienteManager();
    void cargar();
    void mostrar();
    void mostrarDatosDeClienteDNI();
    void mostrarDatosDeClienteID(int idCliente);
    void modificarTelefono(int idCliente);
    void modificarCorreo(int idCliente);
    void modificarFechaNacimiento(int idCliente);
    void modificarLocalidad(int idCliente);
    void listadoPorApellido();
    void listadoActivos();
    void listadoEliminados();
    //void clientePorRangoEdad();

    int buscarIdClientePorDNI(std::string dni);

    bool validarEdad(Fecha fechaNacimiento);
    bool telefonoDisponible(std::string telefono);
    bool correoDisponible(std::string correo);
    bool eliminarPorDNI();
    bool recuperarPorDNI();
    bool verificarRegistroPorDNI(std::string dni);
    bool eliminar(int idCliente);
    bool recuperar(int idCliente);
    void mostrarLista(Cliente cliente, bool eliminado);

private:
    ClientesArchivo _clientesArchivo;
};
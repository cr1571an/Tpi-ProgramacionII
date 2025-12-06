#pragma once
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"

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
    void modificarPartido(int idCliente);

    int posClientePorDNI(std::string dni);

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

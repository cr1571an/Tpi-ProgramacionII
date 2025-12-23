#pragma once

#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"
#include "PolizaArchivo.h"
#include "SiniestroArchivo.h"
#include "SiniestroManager.h"
#include "TiposSegurosArchivo.h"
#include "VencimientosArchivo.h"

class ClienteManager {
public:
    ClienteManager();
    void cargar();
    void mostrar();
    void mostrarDatosDeClienteID(int idCliente);
    int posClientePorDNI(std::string dni);
    bool eliminar(int idCliente);
    void modificarTelefono(int idCliente);
    void modificarCorreo(int idCliente);
    void modificarFechaNacimiento(int idCliente);
    void modificarLocalidad(int idCliente);
    void modificarPartido(int idCliente);
    bool recuperar(int idCliente);
    void historialPagosPorCliente();

private:

    bool validarEdad(Fecha fechaNacimiento);
    bool telefonoDisponible(std::string telefono);
    bool correoDisponible(std::string correo);
    bool verificarRegistroPorDNI(std::string dni);
    void mostrarLista(Cliente cliente, bool eliminado);
    int hayClientesReg();
    int hayPolizasReg();
    int hayPagosVencReg();
    int hayPagosReg();
    int buscarClienteParaHistorial();
    bool esPagoDeCliente(int idxPago, int idCliente);
    int contarPagosDeCliente(int idCliente);

    ClientesArchivo _clientesArchivo;
    VehiculosArchivo _vehiculosArchivo;
    PolizaArchivo _polizasArchivo;
    SiniestroArchivo _siniestroArchivo;
    SiniestroManager _siniestroManager;
    VencimientosArchivo _vencimientosArchivo;
    TiposSiniestrosArchivo _tiposSiniestrosArchivo;
    TiposSegurosArchivo _tiposSegurosArchivo;
    PagoArchivo _pagoArchivo;
};

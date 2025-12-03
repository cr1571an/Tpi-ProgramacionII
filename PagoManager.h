#pragma once
#include "PagoArchivo.h"
#include "PolizaArchivo.h"
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"
#include "VencimientosArchivo.h"
#include "Pago.h"

class PagoManager
{
public:
    PagoManager();
    void cargar(int idPoliza);
    void mostrar();
    void cambiarFecha(int idPago);
    void cambiarMetodo(int idPago);
    void anularPago(int idPago);
    void recuperar();
    void mostrarLista(Pago pago);
    void listarOrdenadosPorFecha();
    void listarOrdenadosPorMetodoPago();
    void mostrarPagosDePoliza(int idPolizaBuscada);
    void mostrarPagosPorEstado(int estadoIngresado);
    void reportePagosPendientes();

private:
    PagoArchivo _pagoArchivo;
    PolizaArchivo _polizaArchivo;
    ClientesArchivo _clientesArchivo;
    VehiculosArchivo _vehiculosArchivo;
    VencimientosArchivo _vencimientosArchivo;
};

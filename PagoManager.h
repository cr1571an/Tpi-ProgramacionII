#pragma once
#include "PagoArchivo.h"
#include "PolizaArchivo.h"
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"
#include "Pago.h"

class PagoManager
{
public:
    PagoManager();
    void cargar(int idPoliza);
    void mostrar();
    void cambiarFecha(int idPago);
    void cambiarMonto(int idPago);
    void cambiarMetodo(int idPago);
    void cambiarEstado(int idPago);
    void eliminar(int id);
    void recuperar();
    void mostrarLista(Pago pago);
    void listarOrdenadosPorFecha();
    void listarOrdenadosPorMetodoPago();
    void mostrarPagosDePoliza(int idPolizaBuscado);
    void mostrarPagosPorEstado(int estadoIngresado);
    void reportePagosPendientes();

private:
    PagoArchivo _pagoArchivo;
    PolizaArchivo _polizaArchivo;
    ClientesArchivo _clientesArchivo;
    VehiculosArchivo _vehiculosArchivo;
};

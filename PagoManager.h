#pragma once
#include "PagoArchivo.h"
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
    void listarOrdenadosPorFecha();
    void listarOrdenadosPorMetodoPago();
    void mostrarPagosDePoliza(int idPolizaBuscado);
    void mostrarPagosPorEstado(int estadoIngresado);
    void reportePagosPendientes();

protected:
    void mostrarLista(Pago pago);

private:
    PagoArchivo _pagoArchivo;
};

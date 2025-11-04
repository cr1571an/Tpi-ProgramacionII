#pragma once
#include "PagoArchivo.h"
#include "Pago.h"

class PagoManager {
    public:
        PagoManager();
        void cargar(int idPoliza);
        void mostrar();
        void mostrarPagosDePoliza(int idPolizaBuscado);
        void eliminar(int id);
        void actualizar();

    protected:
        void mostrarLista(Pago pago);

    private:
        PagoArchivo _pagoArchivo;
};

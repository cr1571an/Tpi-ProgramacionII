#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "utils.h"
#include "PagoManager.h"

using namespace std;

PagoManager::PagoManager()
    : _pagoArchivo(),
      _polizaArchivo(),
      _clientesArchivo(),
      _vehiculosArchivo(),
      _vencimientosArchivo()
{}

/****** ALTA DE PAGO ******/

void PagoManager::cargar(int idPoliza)
{
    int posicionPolizaArchivo = _polizaArchivo.buscarID(idPoliza);
    if (posicionPolizaArchivo == -1)
    {
        cout << "No existe una poliza con ese ID." << endl;
        return;
    }

    Poliza poliza = _polizaArchivo.leer(posicionPolizaArchivo);
    if (poliza.getEliminado())
    {
        cout << "La poliza esta eliminada. No se pueden registrar pagos." << endl;
        return;
    }

    int cantidadVencimientosEnArchivo = _vencimientosArchivo.getCantidadRegistros();
    if (cantidadVencimientosEnArchivo <= 0)
    {
        cout << "No hay vencimientos registrados." << endl;
        return;
    }

    Vencimiento* vectorVencimientos = new Vencimiento[cantidadVencimientosEnArchivo]{};
    _vencimientosArchivo.leerTodos(vectorVencimientos, cantidadVencimientosEnArchivo);

    int* vectorIndicesVencimientosPendientes = new int[cantidadVencimientosEnArchivo]{};
    int  cantidadVencimientosPendientes = 0;

    for (int i = 0; i < cantidadVencimientosEnArchivo; i++)
    {
        Vencimiento vencimiento = vectorVencimientos[i];

        if (vencimiento.getEliminado()) continue;
        if (vencimiento.getPagado()) continue;
        if (vencimiento.getIdPoliza() != idPoliza) continue;

        vectorIndicesVencimientosPendientes[cantidadVencimientosPendientes] = i;
        cantidadVencimientosPendientes++;
    }

    if (cantidadVencimientosPendientes == 0)
    {
        cout << "La poliza no tiene vencimientos pendientes." << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    cout << "---------------------" << endl;
    cout << "CUOTAS PENDIENTES DE LA POLIZA " << idPoliza << endl;
    for (int i = 0; i < cantidadVencimientosPendientes; i++)
    {
        Vencimiento vencimiento = vectorVencimientos[vectorIndicesVencimientosPendientes[i]];
        cout << i + 1 << ") Fecha de vencimiento: "
             << vencimiento.getVencimiento().formatoFecha()
             << "  Importe: " << vencimiento.getMonto() << endl;
    }

    int opcionVencimiento;
    cout << "Seleccione el numero de vencimiento a pagar (0 para cancelar): ";
    cin >> opcionVencimiento;

    if (opcionVencimiento == 0)
    {
        cout << "Operacion cancelada." << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }
    if (opcionVencimiento < 1 || opcionVencimiento > cantidadVencimientosPendientes)
    {
        cout << "Opcion invalida." << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    int posicionVencimientoArchivo = vectorIndicesVencimientosPendientes[opcionVencimiento - 1];
    Vencimiento vencimientoSeleccionado = vectorVencimientos[posicionVencimientoArchivo];

    cout << "---------------------" << endl;
    cout << "Cargar nuevo pago" << endl;
    int idPagoNuevo = _pagoArchivo.getNuevoID();
    cout << "ID: " << idPagoNuevo << endl;
    cout << "ID Poliza: " << idPoliza << endl;

    Fecha fechaPago = leerFechaValida();

    if (fechaPago.getAnio() == -1) {
        cout << "Carga cancelada." << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    if (fechaPago < poliza.getfechaInicio()) {
        cout << "La fecha de pago no puede ser anterior a la fecha de inicio de la poliza: " << poliza.getfechaInicio().formatoFecha() << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    if (fechaPago > poliza.getfechaFin()) {
        cout << "La fecha de pago no puede ser posterior a la fecha de fin de la poliza: "
             << poliza.getfechaFin().formatoFecha() << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    int opcionMetodoPago;
    string metodoDePago;

    while (true)
    {
        cout << "Metodo de pago:" << endl
             << "  1) Efectivo" << endl
             << "  2) Tarjeta de debito" << endl
             << "  3) Tarjeta de credito" << endl
             << "  4) Transferencia bancaria" << endl
             << "Seleccione (1-4): ";

        if (!(cin >> opcionMetodoPago))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (opcionMetodoPago == 1) { metodoDePago = "Efectivo"; break; }
        if (opcionMetodoPago == 2) { metodoDePago = "Tarjeta de debito"; break; }
        if (opcionMetodoPago == 3) { metodoDePago = "Tarjeta de credito"; break; }
        if (opcionMetodoPago == 4) { metodoDePago = "Transferencia bancaria"; break; }

        cout << "Opcion invalida." << endl;
    }

    Pago pagoNuevo(idPagoNuevo, idPoliza, fechaPago, vencimientoSeleccionado.getMonto(), metodoDePago, false);

    if (_pagoArchivo.guardar(pagoNuevo))
    {
        cout << "Pago registrado correctamente." << endl;

        vencimientoSeleccionado.setPagado(true);
        if (!_vencimientosArchivo.guardar(vencimientoSeleccionado, posicionVencimientoArchivo))
        {
            cout << "No se pudo actualizar el vencimiento como pagado." << endl;
        }
    }
    else
    {
        cout << "Error al registrar el pago." << endl;
    }

    delete[] vectorVencimientos;
    delete[] vectorIndicesVencimientosPendientes;
}


/****** MOSTRAR TODOS LOS PAGOS ******/

void PagoManager::mostrar()
{
    int cantidadPagosEnArchivo = _pagoArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidadPagosEnArchivo; i++)
    {
        Pago pagoLeido = _pagoArchivo.leer(i);
        if (pagoLeido.getId() == -1) continue;
        if (pagoLeido.getEliminado()) continue;

        mostrarLista(pagoLeido);
    }
}


/****** ACTUALIZAR CAMPOS DEL PAGO ******/

void PagoManager::cambiarFecha(int idPago)
{
    int posicionPagoArchivo = _pagoArchivo.buscarID(idPago);
    if (posicionPagoArchivo == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

    Pago pagoLeido = _pagoArchivo.leer(posicionPagoArchivo);
    if (pagoLeido.getId() == -1)
    {
        cout << "Error leyendo el registro." << endl;
        return;
    }

    cout << "Registro actual:" << endl;
    mostrarLista(pagoLeido);

    int idPoliza = pagoLeido.getIdPoliza();
    int posPoliza = _polizaArchivo.buscarID(idPoliza);
    if (posPoliza == -1)
    {
        cout << "No se encontro la poliza asociada al pago." << endl;
        return;
    }
    Poliza poliza = _polizaArchivo.leer(posPoliza);

    Fecha nuevaFechaPago = leerFechaValida();

    if (nuevaFechaPago.getAnio() == -1)
    {
        cout << "Cambio de fecha cancelado." << endl;
        return;
    }

    if (nuevaFechaPago < poliza.getfechaInicio())
    {
        cout << "La fecha de pago no puede ser anterior a la fecha de inicio de la poliza: " << poliza.getfechaInicio().formatoFecha() << endl;
        return;
    }

    if (nuevaFechaPago > poliza.getfechaFin())
    {
        cout << "La fecha de pago no puede ser posterior a la fecha de fin de la poliza: " << poliza.getfechaFin().formatoFecha() << endl;
        return;
    }

    pagoLeido.setFechaPago(nuevaFechaPago);

    if (_pagoArchivo.guardar(pagoLeido, posicionPagoArchivo))
        cout << "Fecha actualizada correctamente." << endl;
    else
        cout << "No se pudo actualizar la fecha." << endl;
}

void PagoManager::cambiarMetodo(int idPago)
{
    int posicionPagoArchivo = _pagoArchivo.buscarID(idPago);
    if (posicionPagoArchivo == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

    Pago pagoLeido = _pagoArchivo.leer(posicionPagoArchivo);
    if (pagoLeido.getId() == -1)
    {
        cout << "Error leyendo el registro." << endl;
        return;
    }

    cout << "Registro actual:" << endl;
    mostrarLista(pagoLeido);

    int opcionMetodoPago;
    string metodoDePago;

    while (true)
    {
        cout << "Metodo de pago:" << endl
             << "  1) Efectivo" << endl
             << "  2) Tarjeta de debito" << endl
             << "  3) Tarjeta de credito" << endl
             << "  4) Transferencia bancaria" << endl
             << "Seleccione (1-4): ";

        if (!(cin >> opcionMetodoPago))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionMetodoPago == 1) { metodoDePago = "Efectivo"; break; }
        if (opcionMetodoPago == 2) { metodoDePago = "Tarjeta de debito"; break; }
        if (opcionMetodoPago == 3) { metodoDePago = "Tarjeta de credito"; break; }
        if (opcionMetodoPago == 4) { metodoDePago = "Transferencia bancaria"; break; }

        cout << "Opcion invalida." << endl;
    }

    pagoLeido.setMetodoDePago(metodoDePago);

    if (_pagoArchivo.guardar(pagoLeido, posicionPagoArchivo))
        cout << "Metodo de pago actualizado correctamente." << endl;
    else
        cout << "No se pudo actualizar el metodo de pago." << endl;
}


/****** ANULAR PAGO ******/

void PagoManager::anularPago(int idPago)
{
    int posicionPagoArchivo = _pagoArchivo.buscarID(idPago);
    if (posicionPagoArchivo == -1)
    {
        cout << "No existe un pago con ese ID." << endl;
        return;
    }

    Pago pagoLeido = _pagoArchivo.leer(posicionPagoArchivo);
    if (pagoLeido.getId() == -1 || pagoLeido.getEliminado())
    {
        cout << "El pago ya esta anulado o no existe." << endl;
        return;
    }

    int idPoliza = pagoLeido.getIdPoliza();
    float monto = pagoLeido.getMonto();

    int cantidadVencimientosEnArchivo = _vencimientosArchivo.getCantidadRegistros();
    if (cantidadVencimientosEnArchivo <= 0)
    {
        cout << "Error: no hay vencimientos almacenados." << endl;
        return;
    }

    Vencimiento* vectorVencimientos = new Vencimiento[cantidadVencimientosEnArchivo]{};
    _vencimientosArchivo.leerTodos(vectorVencimientos, cantidadVencimientosEnArchivo);

    int posicionVencimientoAsociado = -1;

    for (int i = 0; i < cantidadVencimientosEnArchivo; i++)
    {
        Vencimiento vencimiento = vectorVencimientos[i];

        if (vencimiento.getEliminado()) continue;
        if (vencimiento.getIdPoliza() != idPoliza) continue;
        if (!vencimiento.getPagado()) continue;
        if (vencimiento.getMonto() != monto) continue;

        posicionVencimientoAsociado = i;
        break;
    }

    if (posicionVencimientoAsociado == -1)
    {
        cout << "Advertencia: no se encontro el vencimiento asociado al pago." << endl;
    }
    else
    {
        vectorVencimientos[posicionVencimientoAsociado].setPagado(false);
        _vencimientosArchivo.guardar(vectorVencimientos[posicionVencimientoAsociado], posicionVencimientoAsociado);
    }

    delete[] vectorVencimientos;

    pagoLeido.setEliminado(true);

    if (_pagoArchivo.guardar(pagoLeido, posicionPagoArchivo))
        cout << "Pago anulado correctamente." << endl;
    else
        cout << "Error al anular el pago." << endl;
}

/****** SALIDA DE UN PAGO ******/

void PagoManager::mostrarLista(Pago pago)
{
    if (pago.getEliminado()) return;

    cout << "----------------------------" << endl;
    cout << "ID: " << pago.getId() << endl;
    cout << "ID Poliza: " << pago.getIdPoliza() << endl;

    Fecha fechaPago = pago.getFechaPago();
    cout << "Fecha: " << fechaPago.getDia()
         << "/" << fechaPago.getMes()
         << "/" << fechaPago.getAnio() << endl;

    cout << "Monto: " << pago.getMonto() << endl;
    cout << "Metodo: " << pago.getMetodoDePago() << endl;
    cout << "----------------------------" << endl;
}


/****** LISTADOS ******/

/*** Listado ordenado por fecha ***/

void PagoManager::listarOrdenadosPorFecha()
{
    int opcionOrden;

    while (true)
    {
        cout << "Orden por fecha (1 = ASCENDENTE, 2 = DESCENDENTE): ";
        if (!(cin >> opcionOrden))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionOrden == 1 || opcionOrden == 2)
        {
            break;
        }

        cout << "Opcion invalida." << endl;
    }

    bool ordenarAscendente = (opcionOrden == 1);

    int cantidadPagosEnArchivo = _pagoArchivo.getCantidadRegistros();
    if (cantidadPagosEnArchivo <= 0)
    {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    Pago* vectorPagos = new Pago[cantidadPagosEnArchivo];
    int   cantidadPagosValidos = 0;

    for (int i = 0; i < cantidadPagosEnArchivo; i++)
    {
        Pago pagoLeido = _pagoArchivo.leer(i);
        if (pagoLeido.getId() == -1) continue;
        if (pagoLeido.getEliminado()) continue;

        vectorPagos[cantidadPagosValidos] = pagoLeido;
        cantidadPagosValidos++;
    }

    if (cantidadPagosValidos == 0)
    {
        cout << "No hay pagos para mostrar." << endl;
        delete[] vectorPagos;
        return;
    }

    for (int i = 0; i < cantidadPagosValidos - 1; i++)
    {
        for (int j = 0; j < cantidadPagosValidos - 1 - i; j++)
        {
            Fecha fechaPagoActual = vectorPagos[j].getFechaPago();
            Fecha fechaPagoSiguiente = vectorPagos[j + 1].getFechaPago();

            bool intercambiar = false;

            if (ordenarAscendente)
            {
                if (fechaPagoActual > fechaPagoSiguiente)
                {
                    intercambiar = true;
                }
            }
            else
            {
                if (fechaPagoActual < fechaPagoSiguiente)
                {
                    intercambiar = true;
                }
            }

            if (intercambiar)
            {
                Pago pagoAuxiliar   = vectorPagos[j];
                vectorPagos[j]      = vectorPagos[j + 1];
                vectorPagos[j + 1]  = pagoAuxiliar;
            }
        }
    }

    cout << "LISTADO DE PAGOS ORDENADOS POR FECHA" << endl;

    for (int i = 0; i < cantidadPagosValidos; i++)
    {
        mostrarLista(vectorPagos[i]);
    }

    delete[] vectorPagos;
}


/*** Listado ordenado por metodo de pago ***/

void PagoManager::listarOrdenadosPorMetodoPago()
{
    int cantidadPagosEnArchivo = _pagoArchivo.getCantidadRegistros();
    if (cantidadPagosEnArchivo <= 0)
    {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    Pago* vectorPagos = new Pago[cantidadPagosEnArchivo];
    int   cantidadPagosValidos = 0;

    for (int i = 0; i < cantidadPagosEnArchivo; i++)
    {
        Pago pagoLeido = _pagoArchivo.leer(i);
        if (pagoLeido.getId() == -1) continue;
        if (pagoLeido.getEliminado()) continue;

        vectorPagos[cantidadPagosValidos] = pagoLeido;
        cantidadPagosValidos++;
    }

    if (cantidadPagosValidos == 0)
    {
        cout << "No hay pagos para mostrar." << endl;
        delete[] vectorPagos;
        return;
    }

    for (int i = 0; i < cantidadPagosValidos - 1; i++)
    {
        for (int j = 0; j < cantidadPagosValidos - 1 - i; j++)
        {
            string metodoActual = vectorPagos[j].getMetodoDePago();
            string metodoSiguiente = vectorPagos[j + 1].getMetodoDePago();

            if (metodoActual > metodoSiguiente)
            {
                Pago pagoAuxiliar = vectorPagos[j];
                vectorPagos[j] = vectorPagos[j + 1];
                vectorPagos[j + 1] = pagoAuxiliar;
            }
        }
    }

    cout << "LISTADO DE PAGOS ORDENADOS POR METODO DE PAGO" << endl;

    for (int i = 0; i < cantidadPagosValidos; i++)
    {
        mostrarLista(vectorPagos[i]);
    }

    delete[] vectorPagos;
}


/****** CONSULTAS ******/

/*** Consulta por numero de poliza ***/

void PagoManager::mostrarPagosDePoliza(int idPolizaBuscada)
{
    int posicionPolizaArchivo = _polizaArchivo.buscarID(idPolizaBuscada);
    if (posicionPolizaArchivo == -1)
    {
        cout << "No existe una poliza con ese ID." << endl;
        return;
    }

    cout << "Pagos de la poliza " << idPolizaBuscada << ":" << endl;
    int cantidadPagosEnArchivo = _pagoArchivo.getCantidadRegistros();

    bool pagosEncontrados = false;

    for (int i = 0; i < cantidadPagosEnArchivo; i++)
    {
        Pago pagoLeido = _pagoArchivo.leer(i);
        if (pagoLeido.getId() == -1) continue;
        if (pagoLeido.getEliminado()) continue;
        if (pagoLeido.getIdPoliza() != idPolizaBuscada) continue;

        mostrarLista(pagoLeido);
        pagosEncontrados = true;
    }

    if (!pagosEncontrados)
    {
        cout << "No existen pagos para esa poliza." << endl;
    }
}

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "utils.h"
#include "PagoManager.h"
#include "ClienteManager.h"

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

    int indiceVencimientoMasProximo = vectorIndicesVencimientosPendientes[0];
    for (int i = 1; i < cantidadVencimientosPendientes; i++)
    {
        int indiceVencimientoEnEvaluacion = vectorIndicesVencimientosPendientes[i];

        Fecha fechaVencimientoActual = vectorVencimientos[indiceVencimientoMasProximo].getVencimiento();
        Fecha fechaVencimientoCandidato = vectorVencimientos[indiceVencimientoEnEvaluacion].getVencimiento();

        if (fechaVencimientoCandidato < fechaVencimientoActual)
        {
            indiceVencimientoMasProximo = indiceVencimientoEnEvaluacion;
        }
    }

    Vencimiento vencimientoSeleccionado = vectorVencimientos[indiceVencimientoMasProximo];

    cout << endl;
    cout << "---------------------" << endl;
    cout << endl;
    cout << "CUOTA A PAGAR (proximo vencimiento pendiente)" << endl;
    cout << "ID Vencimiento: " << vencimientoSeleccionado.getId() << endl;
    cout << "Fecha de vencimiento: " << vencimientoSeleccionado.getVencimiento().formatoFecha() << endl;
    cout << "Importe: " << vencimientoSeleccionado.getMonto() << endl;
    cout << endl;
    cout << "---------------------" << endl;
    cout << endl;
    cout << "NUEVO PAGO" << endl;
    int idPagoNuevo = _pagoArchivo.getNuevoID();
    cout << "ID de pago: " << idPagoNuevo << endl;
    cout << "ID de poliza: " << idPoliza << endl;

    Fecha fechaPago = leerFechaValida();

    if (fechaPago.getAnio() == -1)
    {
        cout << "CARGA CANDELADA." << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    Fecha hoy;

    if (fechaPago < poliza.getfechaInicio())
    {
        cout << "La fecha de pago no puede ser anterior a la fecha de inicio de la poliza: " << poliza.getfechaInicio().formatoFecha() << endl;
        delete[] vectorVencimientos;
        delete[] vectorIndicesVencimientosPendientes;
        return;
    }

    if (fechaPago > hoy)
    {
        cout << "La fecha ingresada no puede ser posterior a la fecha actual. Hoy es " << hoy.formatoFecha() << endl;
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
             << "  0) Cancelar" << endl
             << "Seleccione (0-4): ";

        if (!(cin >> opcionMetodoPago))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionMetodoPago == 0)
        {
            cout << "Carga cancelada." << endl;
            return;
        }

        if (opcionMetodoPago == 1) { metodoDePago = "Efectivo"; break; }
        if (opcionMetodoPago == 2) { metodoDePago = "Tarjeta de debito"; break; }
        if (opcionMetodoPago == 3) { metodoDePago = "Tarjeta de credito"; break; }
        if (opcionMetodoPago == 4) { metodoDePago = "Transferencia bancaria"; break; }

        cout << "Opcion invalida." << endl;
    }

    Pago pagoNuevo(idPagoNuevo, vencimientoSeleccionado.getId(), fechaPago, metodoDePago, false);

    if (_pagoArchivo.guardar(pagoNuevo))
    {
        cout << "Pago registrado correctamente." << endl;

        vencimientoSeleccionado.setPagado(true);
        if (!_vencimientosArchivo.guardar(vencimientoSeleccionado, indiceVencimientoMasProximo))
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
    if (cantidadPagosEnArchivo <= 0)
    {
        cout << "NO HAY PAGOS REGISTRADOS." << endl;
        return;
    }
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

    int idVencimiento = pagoLeido.getIdVencimiento();
    int posicionVencimientoArchivo = _vencimientosArchivo.buscarID(idVencimiento);
    if (posicionVencimientoArchivo == -1)
    {
        cout << "No se encontro el vencimiento asociado al pago." << endl;
        return;
    }
    Vencimiento vencimiento = _vencimientosArchivo.leer(posicionVencimientoArchivo);

    int idPoliza = vencimiento.getIdPoliza();
    int posicionPolizaArchivo = _polizaArchivo.buscarID(idPoliza);
    if (posicionPolizaArchivo == -1)
    {
        cout << "No se encontro la poliza asociada al vencimiento." << endl;
        return;
    }
    Poliza poliza = _polizaArchivo.leer(posicionPolizaArchivo);

    cout << endl;
    Fecha nuevaFechaPago = leerFechaValida();

    if (nuevaFechaPago.getAnio() == -1)
    {
        cout << "CAMBIO DE FECHA CANCELADO." << endl;
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
        cout << endl;
        cout << "NUEVO metodo de pago:" << endl
             << "  1) Efectivo" << endl
             << "  2) Tarjeta de debito" << endl
             << "  3) Tarjeta de credito" << endl
             << "  4) Transferencia bancaria" << endl
             << "  0) Cancelar" << endl
             << "Seleccione (0-4): ";

        if (!(cin >> opcionMetodoPago))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionMetodoPago == 0)
        {
            cout << "Operacion cancelada." << endl;
            return;
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

    int idVencimiento = pagoLeido.getIdVencimiento();
    int posicionVencimientoArchivo = _vencimientosArchivo.buscarID(idVencimiento);

    if (posicionVencimientoArchivo == -1)
    {
        cout << "No se encontro el vencimiento asociado al pago." << endl;
        return;
    }
    else
    {
        Vencimiento vencimiento = _vencimientosArchivo.leer(posicionVencimientoArchivo);
        if (vencimiento.getPagado())
        {
            vencimiento.setPagado(false);
            _vencimientosArchivo.guardar(vencimiento, posicionVencimientoArchivo);
        }
    }

    pagoLeido.setEliminado(true);

    if (_pagoArchivo.guardar(pagoLeido, posicionPagoArchivo))
        cout << "Pago anulado correctamente." << endl;
    else
        cout << "Error al anular el pago." << endl;
}


/****** SALIDA DE UN PAGO ******/

void PagoManager::mostrarLista(Pago pago)
{
    if (pago.getEliminado()) {
        cout << "EL PAGO HA SIDO ANULADO" << endl;
        return;
    }

    cout << "----------------------------" << endl;
    cout << "ID de pago: " << pago.getId() << endl;
    cout << "ID de vencimiento: " << pago.getIdVencimiento() << endl;

    int idVencimiento = pago.getIdVencimiento();
    int posicionVencimientoArchivo = _vencimientosArchivo.buscarID(idVencimiento);
    if (posicionVencimientoArchivo != -1)
    {
        Vencimiento vencimiento = _vencimientosArchivo.leer(posicionVencimientoArchivo);
        cout << "ID de poliza: " << vencimiento.getIdPoliza() << endl;
        cout << "Fecha de vencimiento: " << vencimiento.getVencimiento().formatoFecha() << endl;
        cout << "Importe de la cuota: " << vencimiento.getMonto() << endl;
    }

    Fecha fechaPago = pago.getFechaPago();
    cout << "Fecha de pago: " << fechaPago.getDia() << "/" << fechaPago.getMes() << "/" << fechaPago.getAnio() << endl;
    cout << "Metodo de pago: " << pago.getMetodoDePago() << endl;
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
                Pago pagoAuxiliar = vectorPagos[j];
                vectorPagos[j] = vectorPagos[j + 1];
                vectorPagos[j + 1] = pagoAuxiliar;
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
        cout << "NO HAY PAGOS REGISTRADOS." << endl;
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

        int idVencimiento = pagoLeido.getIdVencimiento();
        int posicionVencimientoArchivo = _vencimientosArchivo.buscarID(idVencimiento);
        if (posicionVencimientoArchivo == -1) continue;

        Vencimiento vencimiento = _vencimientosArchivo.leer(posicionVencimientoArchivo);
        if (vencimiento.getIdPoliza() != idPolizaBuscada) continue;

        mostrarLista(pagoLeido);
        pagosEncontrados = true;
    }

    if (!pagosEncontrados)
    {
        cout << "No existen pagos para esa poliza." << endl;
    }
}


/****** REPORTES ******/

void PagoManager::reporteDeudaPorCliente()
{
    int cantidadClientes = _clientesArchivo.getCantidadRegistros();
    int cantidadPolizas = _polizaArchivo.getCantidadRegistros();
    int cantidadVehiculos = _vehiculosArchivo.cantidadRegistros();
    int cantidadVencimientos = _vencimientosArchivo.getCantidadRegistros();

    if (cantidadClientes == 0)
    {
        cout << "No hay clientes registrados." << endl;
        return;
    }
    if (cantidadVehiculos == 0)
    {
        cout << "No hay vehiculos registrados." << endl;
        return;
    }
    if (cantidadPolizas == 0)
    {
        cout << "No hay polizas registradas." << endl;
        return;
    }
    if (cantidadVencimientos == 0)
    {
        cout << "No hay vencimientos registrados." << endl;
        return;
    }

    Cliente* vectorClientes = new Cliente[cantidadClientes];
    _clientesArchivo.leerTodos(vectorClientes, cantidadClientes);

    int*   vectorIdClientePorPoliza = new int[cantidadVencimientos];
    int*   vectorIdPolizaPorCliente = new int[cantidadVencimientos];
    float* vectorDeudaPorClienteYPoliza = new float[cantidadVencimientos];

    int cantidadCombinacionesClientePoliza = 0;

    for (int indice = 0; indice < cantidadVencimientos; indice++)
    {
        vectorDeudaPorClienteYPoliza[indice] = 0.0;
    }

    for (int indiceVencimiento = 0; indiceVencimiento < cantidadVencimientos; indiceVencimiento++)
    {
        Vencimiento vencimientoActual = _vencimientosArchivo.leer(indiceVencimiento);

        if (vencimientoActual.getEliminado()) continue;
        if (vencimientoActual.getPagado()) continue;
        if (!vencimientoActual.estaVencido()) continue;

        int idPolizaDelVencimiento = vencimientoActual.getIdPoliza();
        Poliza polizaAsociada;
        bool polizaEncontrada = false;

        for (int indicePoliza = 0; indicePoliza < cantidadPolizas; indicePoliza++)
        {
            Poliza polizaLeida = _polizaArchivo.leer(indicePoliza);
            if (polizaLeida.getEliminado()) continue;
            if (polizaLeida.getId() == idPolizaDelVencimiento)
            {
                polizaAsociada = polizaLeida;
                polizaEncontrada = true;
                break;
            }
        }
        if (!polizaEncontrada) continue;

        int idVehiculoDeLaPoliza = polizaAsociada.getIdVehiculo();
        Vehiculo vehiculoAsociado;
        bool vehiculoEncontrado = false;

        for (int indiceVehiculo = 0; indiceVehiculo < cantidadVehiculos; indiceVehiculo++)
        {
            Vehiculo vehiculoLeido = _vehiculosArchivo.leer(indiceVehiculo);
            if (vehiculoLeido.getEliminado()) continue;
            if (vehiculoLeido.getIdVehiculo() == idVehiculoDeLaPoliza)
            {
                vehiculoAsociado = vehiculoLeido;
                vehiculoEncontrado = true;
                break;
            }
        }
        if (!vehiculoEncontrado) continue;

        int idClienteDelVehiculo = vehiculoAsociado.getIdCliente();
        int posicionCombinacion = -1;

        for (int indiceCombinacion = 0; indiceCombinacion < cantidadCombinacionesClientePoliza; indiceCombinacion++)
        {
            if (vectorIdClientePorPoliza[indiceCombinacion] == idClienteDelVehiculo && vectorIdPolizaPorCliente[indiceCombinacion] == polizaAsociada.getId())
            {
                posicionCombinacion = indiceCombinacion;
                break;
            }
        }

        if (posicionCombinacion == -1)
        {
            posicionCombinacion = cantidadCombinacionesClientePoliza;
            vectorIdClientePorPoliza[posicionCombinacion] = idClienteDelVehiculo;
            vectorIdPolizaPorCliente[posicionCombinacion] = polizaAsociada.getId();
            vectorDeudaPorClienteYPoliza[posicionCombinacion] = 0.0;
            cantidadCombinacionesClientePoliza++;
        }

        vectorDeudaPorClienteYPoliza[posicionCombinacion] += vencimientoActual.getMonto();
    }

    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      DEUDA DE VENCIMIENTOS POR CLIENTE Y POLIZA    ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;

    cout << fixed << setprecision(2);

    bool clienteConDeudaEncontrado = false;

    for (int indiceCliente = 0; indiceCliente < cantidadClientes; indiceCliente++)
    {
        Cliente clienteActual = vectorClientes[indiceCliente];
        if (clienteActual.getEliminado()) continue;

        float deudaTotalDelCliente = 0.0;
        bool clienteConDeuda = false;

        for (int indiceCombinacion = 0; indiceCombinacion < cantidadCombinacionesClientePoliza; indiceCombinacion++)
        {
            if (vectorIdClientePorPoliza[indiceCombinacion] != clienteActual.getIdCliente())
            {
                continue;
            }

            float deudaPoliza = vectorDeudaPorClienteYPoliza[indiceCombinacion];
            if (deudaPoliza <= 0.0)
            {
                continue;
            }

            if (!clienteConDeuda)
            {
                cout << "CLIENTE: " << clienteActual.getNombre() << " " << clienteActual.getApellido() << endl;
                cout << "ID CLIENTE: " << clienteActual.getIdCliente() << endl;
                cout << "DNI: " << clienteActual.getDni() << endl;
                cout << endl;
                clienteConDeuda = true;
                clienteConDeudaEncontrado = true;
            }

            cout << "  POLIZA " << vectorIdPolizaPorCliente[indiceCombinacion] << endl;
            cout << "  DEUDA: $ " << deudaPoliza << endl;
            cout << "  -----------------------------" << endl;

            deudaTotalDelCliente += deudaPoliza;
        }

        if (clienteConDeuda)
        {
            cout << "  DEUDA TOTAL: $ " << deudaTotalDelCliente << endl << endl;
            cout << "=============================================" << endl << endl;
        }
    }

    if (!clienteConDeudaEncontrado)
    {
        cout << "No se registran clientes con deuda de vencimientos vencidos." << endl;
    }

    delete[] vectorClientes;
    delete[] vectorIdClientePorPoliza;
    delete[] vectorIdPolizaPorCliente;
    delete[] vectorDeudaPorClienteYPoliza;
}

bool PagoManager::polizaPagosAlDia(int idPoliza){
    int posicionPolizaArchivo = _vencimientosArchivo.buscarID(idPoliza);
    if (posicionPolizaArchivo == -1){
        cout << "LA POLIZA " << idPoliza << " NO TIENE VENCIMIENTOS ASOCIADOS." << endl;
        return false;
    }

    int cantidadVencimientosEnArchivo = _vencimientosArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidadVencimientosEnArchivo; i++){
        Vencimiento vencimiento = _vencimientosArchivo.leer(i);
        if (vencimiento.getIdPoliza() == idPoliza && !vencimiento.getEliminado()){
            if (!vencimiento.getPagado() && vencimiento.estaVencido())
                return false;
        }
    }
    return true;
}

void PagoManager::pagosPorPolizaId(int idPoliza, Pago pagosPoliza[], int cantidadPagosPoliza){
    int cantidadPagosEnArchivo = _pagoArchivo.getCantidadRegistros();
    Pago* vectorPagos = new Pago[cantidadPagosEnArchivo]{};
    _pagoArchivo.leerTodos(vectorPagos, cantidadPagosEnArchivo);

    int indicePagosPoliza = 0;

    int cantidadVencimientosEnArchivo = _vencimientosArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidadVencimientosEnArchivo; i++){
        Vencimiento vencimiento = _vencimientosArchivo.leer(i);
        if (vencimiento.getIdPoliza() == idPoliza && !vencimiento.getEliminado()){
            if (vencimiento.getPagado()){
                for (int j = 0; j < cantidadPagosEnArchivo; j++){
                    if (vectorPagos[j].getIdVencimiento() == vencimiento.getId() && !vectorPagos[j].getEliminado()){
                        pagosPoliza[indicePagosPoliza] = vectorPagos[j];
                        indicePagosPoliza++;
                        break;
                    }
                }
            }
        }
    }

    delete[] vectorPagos;
}

int PagoManager::cantidadPagosPorPoliza(int idPoliza){
    int cantidadPagos=0;
    int cantidadVencimientosEnArchivo = _vencimientosArchivo.getCantidadRegistros();

    for (int i = 0; i < cantidadVencimientosEnArchivo; i++){
        Vencimiento vencimiento = _vencimientosArchivo.leer(i);
        if (vencimiento.getIdPoliza() == idPoliza && !vencimiento.getEliminado()){
            if (vencimiento.getPagado())
                cantidadPagos++;
        }
    }
    return cantidadPagos;
}

bool PagoManager::eliminarVencimientosDePoliza(int idPoliza){
    int cantidad = _vencimientosArchivo.getCantidadRegistros();
    bool elimino = false;

    for (int i = 0; i < cantidad; i++){
        Vencimiento vencimiento = _vencimientosArchivo.leer(i);

        if (vencimiento.getIdPoliza() == idPoliza && !vencimiento.getEliminado()){
            vencimiento.setEliminado(true);
            if (_vencimientosArchivo.guardar(vencimiento, i)){
                elimino = true;
            }
        }
    }
    return elimino;
}

void PagoManager::recaudacionPorPeriodoYTipoSeguros() {
    int cantPagos = _pagoArchivo.getCantidadRegistros();
    if (cantPagos == 0){
        cout << "NO HAY PAGOS REGISTRADOS, NO ES POSIBLE REALIZAR ESTE REPORTE." << endl;
        return;
    }
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     RECAUDACION POR PERIODO Y POR TIPO DE POLIZA     ||" << endl;
    cout << "||------------------------------------------------------||" << endl;
    cout << "INGRESE LA FECHA INICIAL: ";
    Fecha fechaInicio = leerFechaValida();
    if (fechaInicio.getAnio() == -1){cout << "SE CANCELA LA OPERACION." << endl;return;}
    cout << "INGRESE LA FECHA FINAL: ";
    Fecha fechaFin = leerFechaValida();
    if (fechaFin.getAnio() == -1){cout << "SE CANCELA LA OPERACION." << endl;return;}
    if (fechaFin < fechaInicio){cout << "LA FECHA FINAL NO PUEDE SER MENOR A LA FECHA INICIAL." << endl;return;}
    if (fechaInicio.getAnio()<2023 || fechaFin.getAnio()>2025) {cout << "EL PERIODO DE FECHAS DEBE ESTAR ENTRE 2023 Y 2025." << endl;return;}
    float totalPeriodo=0;
    const int SEGUROS=4;
    float recaudadoPorTipo[SEGUROS]={};
    string nombreSeguro[SEGUROS]={"BASICO RESPONSABILIDAD CIVIL","CONTRA TERCEROS COMPLETO","TODO RIESGO","CONTRA ROBO E INCENDIO"};
    for (int i=0; i<cantPagos; i++){
        Pago pago = _pagoArchivo.leer(i);
        if (pago.getEliminado()) continue;

        Fecha fechaPago = pago.getFechaPago();
        if (fechaPago >=fechaInicio && fechaPago<=fechaFin){
            int idVencimiento = pago.getIdVencimiento();
            int posVencimiento = _vencimientosArchivo.buscarID(idVencimiento);
            if (posVencimiento == -1) continue;

            Vencimiento vencimiento = _vencimientosArchivo.leer(posVencimiento);
            float monto = vencimiento.getMonto();
            int idPoliza = vencimiento.getIdPoliza();
            int posPoliza = _polizaArchivo.buscarID(idPoliza);
            if (posPoliza == -1) continue;

            Poliza poliza = _polizaArchivo.leer(posPoliza);
            int idTipoSeguro = poliza.getIdTipoSeguro();
            if (idTipoSeguro >= 1 && idTipoSeguro <= SEGUROS){
                recaudadoPorTipo[idTipoSeguro-1] += monto;
            }
            totalPeriodo += monto;
        }
    }
    if (totalPeriodo == 0){cout << "NO EXISTEN PAGOS EN EL PERIODO DE FECHAS INGRESADOS." << endl;return;}
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||               RECAUDACION POR PERIODO                  ||" << endl;
    cout << "              DESDE " <<fechaInicio.formatoFecha()<< " HASTA " << fechaFin.formatoFecha() << endl;
    cout << "            TOTAL RECAUDADO EN EL PERIODO: $"<< totalPeriodo << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl<< endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||            RECAUDADO POR TIPO DE POLIZA                ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" <<endl<< endl;
    for (int i = 0; i < SEGUROS; i++){
        if ( recaudadoPorTipo[i]>0){
            cout << "- " << nombreSeguro[i]<< ": $" << recaudadoPorTipo[i] << endl;
        }
    }
}
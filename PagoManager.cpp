#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "utils.h"
#include "PagoManager.h"
using namespace std;

PagoManager::PagoManager()
    : _pagoArchivo() {}

void PagoManager::cargar(int idPoliza)
{
    int id = _pagoArchivo.getNuevoID();
    float monto;
    int e;
    bool estado;
    int opcionMetodo;
    string metodo;

    cout << "---------------------" << endl;
    cout << "Cargar nuevo pago" << endl;
    cout << "ID: " << id << endl;
    cout << "ID Poliza: " << idPoliza << endl;

    Fecha fechaPago = leerFechaValida();

    while (true)
    {
        cout << "Ingrese monto: ";
        if (!(cin >> monto))
        {
            cout << "Entrada invalida.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (monto > 0) break;

        cout << "El monto debe ser mayor a 0." << endl;
    }

    while (true)
    {
        cout << "Metodo de pago:" << endl
             << "  1) Efectivo" << endl
             << "  2) Tarjeta de debito" << endl
             << "  3) Tarjeta de credito" << endl
             << "  4) Transferencia bancaria" << endl
             << "Seleccione (1-4): ";

        if (!(cin >> opcionMetodo))
        {
            cout << "Entrada invalida.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (opcionMetodo==1)
        {
            metodo="Efectivo";
            break;
        }
        if (opcionMetodo==2)
        {
            metodo="Tarjeta de debito";
            break;
        }
        if (opcionMetodo==3)
        {
            metodo="Tarjeta de credito";
            break;
        }
        if (opcionMetodo==4)
        {
            metodo="Transferencia bancaria";
            break;
        }
        cout << "Opcion invalida." << endl;
    }

    while (true)
    {
        cout << "Estado (0 = pendiente, 1 = realizado): ";
        if (!(cin >> e))
        {
            cout << "Entrada invalida.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (e==0 || e==1)
        {
            estado = (e==1);
            break;
        }

        cout << "Valor invalido." << endl;
    }

    Pago reg(id,idPoliza,fechaPago,monto,metodo,estado,false);

    if (_pagoArchivo.guardar(reg))
    {
        cout << "Se agrego correctamente." << endl;
    }
    else
    {
        cout << "Error." << endl;
    }
}

void PagoManager::mostrar()
{
    int cantidad = _pagoArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1) continue;
        if (!p.getEliminado()) mostrarLista(p);
    }
}

void PagoManager::cambiarFecha(int idPago)
{
    int pos = _pagoArchivo.buscarID(idPago);
    if (pos == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

    Pago reg = _pagoArchivo.leer(pos);
    if (reg.getId() == -1)
    {
        cout << "Error leyendo el registro." << endl;
        return;
    }

    cout << "Registro actual:" << endl;
    mostrarLista(reg);

    Fecha nuevaFecha = leerFechaValida();
    reg.setFechaPago(nuevaFecha);

    if (_pagoArchivo.sobrescribir(reg, pos))
        cout << "Fecha actualizada correctamente." << endl;
    else
        cout << "No se pudo actualizar la fecha." << endl;
}

void PagoManager::cambiarMonto(int idPago)
{
    int pos = _pagoArchivo.buscarID(idPago);
    if (pos == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

    Pago reg = _pagoArchivo.leer(pos);
    if (reg.getId() == -1)
    {
        cout << "Error leyendo el registro." << endl;
        return;
    }

    cout << "Registro actual:" << endl;
    mostrarLista(reg);

    float monto;
    while (true)
    {
        cout << "Nuevo monto: ";
        if (cin >> monto && monto > 0) break;
        cout << "Monto invalido." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }

    reg.setMonto(monto);

    if (_pagoArchivo.sobrescribir(reg, pos))
        cout << "Monto actualizado correctamente." << endl;
    else
        cout << "No se pudo actualizar el monto." << endl;
}

void PagoManager::cambiarMetodo(int idPago)
{
    int pos = _pagoArchivo.buscarID(idPago);
    if (pos == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

    Pago reg = _pagoArchivo.leer(pos);
    if (reg.getId() == -1)
    {
        cout << "Error leyendo el registro." << endl;
        return;
    }

    cout << "Registro actual:" << endl;
    mostrarLista(reg);

    int opcionMetodo;
    string metodo;

    while (true)
    {
        cout << "Metodo de pago:" << endl
             << "  1) Efectivo" << endl
             << "  2) Tarjeta de debito" << endl
             << "  3) Tarjeta de credito" << endl
             << "  4) Transferencia bancaria" << endl
             << "Seleccione (1-4): ";

        if (!(cin >> opcionMetodo))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionMetodo == 1)
        {
            metodo = "Efectivo";
            break;
        }
        if (opcionMetodo == 2)
        {
            metodo = "Tarjeta de debito";
            break;
        }
        if (opcionMetodo == 3)
        {
            metodo = "Tarjeta de credito";
            break;
        }
        if (opcionMetodo == 4)
        {
            metodo = "Transferencia bancaria";
            break;
        }

        cout << "Opcion invalida." << endl;
    }

    reg.setMetodoDePago(metodo);

    if (_pagoArchivo.sobrescribir(reg, pos))
        cout << "Metodo de pago actualizado correctamente." << endl;
    else
        cout << "No se pudo actualizar el metodo de pago." << endl;
}

void PagoManager::cambiarEstado(int idPago)
{
    int pos = _pagoArchivo.buscarID(idPago);
    if (pos == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

    Pago reg = _pagoArchivo.leer(pos);
    if (reg.getId() == -1)
    {
        cout << "Error leyendo el registro." << endl;
        return;
    }

    cout << "Registro actual:" << endl;
    mostrarLista(reg);

    int e;
    while (true)
    {
        cout << "Nuevo estado (0 = pendiente, 1 = realizado): ";
        if (cin >> e && (e == 0 || e == 1)) break;
        cout << "Valor invalido." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }

    reg.setEstado(e == 1);

    if (_pagoArchivo.sobrescribir(reg, pos))
        cout << "Estado actualizado correctamente." << endl;
    else
        cout << "No se pudo actualizar el estado." << endl;
}

void PagoManager::eliminar(int id)
{
    int pos = _pagoArchivo.buscarID(id);
    if (pos == -1)
    {
        cout << "El ID ingresado no se encontro." << endl;
        return;
    }

    if (_pagoArchivo.eliminar(id))
        cout << "Pago eliminado." << endl;
    else
        cout << "No se pudo eliminar el pago." << endl;
}

void PagoManager::recuperar()
{
    int id;
    cout << "Ingrese ID de pago a recuperar: ";
    cin >> id;

    if (id <= 0)
    {
        cout << "El ID ingresado es invalido." << endl;
        return;
    }

    int pos = _pagoArchivo.buscarID(id);

    if (pos == -1)
    {
        cout << "El ID ingresado no se encontro." << endl;
        return;
    }

    Pago pago = _pagoArchivo.leer(pos);

    if (!pago.getEliminado())
    {
        cout << "El pago ya esta activo, no es necesario recuperarlo." << endl;
        return;
    }

    pago.setEliminado(false);

    bool ok = _pagoArchivo.sobrescribir(pago, pos);
    cout << (ok ? "Pago recuperado." : "No se pudo recuperar el pago.") << endl;
}

void PagoManager::mostrarLista(Pago p)
{
    if (p.getEliminado()) return;
    cout << "----------------------------" << endl;
    cout << "ID: " << p.getId() << endl;
    cout << "ID Poliza: " << p.getIdPoliza() << endl;
    Fecha f = p.getFechaPago();
    cout << "Fecha: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
    cout << "Monto: " << p.getMonto() << endl;
    cout << "Metodo: " << p.getMetodoDePago() << endl;
    cout << "Estado: " << (p.getEstado() ? "REALIZADO" : "PENDIENTE") << endl;
    cout << "----------------------------" << endl;
}



/****** LISTADOS ******/

/****** Listado ordenado por fecha ******/

void PagoManager::listarOrdenadosPorFecha()
{
    int orden;

    while (true)
    {
        cout << "Orden por fecha (1=ASCENDENTE, 2=DESCENDENTE): ";
        if (!(cin >> orden))
        {
            cout << "Entrada invalida." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (orden == 1 || orden == 2)
        {
            break;
        }

        cout << "Opcion invalida." << endl;
    }

    bool ascendente = (orden == 1);

    int cantidad = _pagoArchivo.getCantidadRegistros();
    if (cantidad <= 0)
    {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    Pago* vec = new Pago[cantidad];
    int validos = 0;

    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1) continue;
        if (p.getEliminado()) continue;

        vec[validos] = p;
        validos++;
    }

    if (validos == 0)
    {
        cout << "No hay pagos para mostrar." << endl;
        delete[] vec;
        return;
    }

    for (int i = 0; i < validos - 1; i++)
    {
        for (int j = 0; j < validos - 1 - i; j++)
        {
            Fecha f1 = vec[j].getFechaPago();
            Fecha f2 = vec[j + 1].getFechaPago();

            bool intercambiar = false;

            if (ascendente)
            {
                if (f1 > f2)
                {
                    intercambiar = true;
                }
            }
            else
            {
                if (f1 < f2)
                {
                    intercambiar = true;
                }
            }

            if (intercambiar)
            {
                Pago aux   = vec[j];
                vec[j]     = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }

    cout << "LISTADO DE PAGOS ORDENADOS POR FECHA" << endl;

    for (int i = 0; i < validos; i++)
    {
        mostrarLista(vec[i]);
    }

    delete[] vec;
}


/****** Listado ordenado por metodo de pago ******/

void PagoManager::listarOrdenadosPorMetodoPago()
{
    int cantidad = _pagoArchivo.getCantidadRegistros();
    if (cantidad <= 0)
    {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    Pago* vec = new Pago[cantidad];
    int validos = 0;

    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1) continue;
        if (p.getEliminado()) continue;

        vec[validos] = p;
        validos++;
    }

    if (validos == 0)
    {
        cout << "No hay pagos para mostrar." << endl;
        delete[] vec;
        return;
    }

    for (int i = 0; i < validos - 1; i++)
    {
        for (int j = 0; j < validos - 1 - i; j++)
        {
            string m1 = vec[j].getMetodoDePago();
            string m2 = vec[j + 1].getMetodoDePago();

            if (m1 > m2)
            {
                Pago aux   = vec[j];
                vec[j]     = vec[j + 1];
                vec[j + 1] = aux;
            }
        }
    }

    cout << "LISTADO DE PAGOS ORDENADOS POR METODO DE PAGO" << endl;

    for (int i = 0; i < validos; i++)
    {
        mostrarLista(vec[i]);
    }

    delete[] vec;
}


/****** CONSULTAS ******/

/****** Consulta por numero de poliza ******/

void PagoManager::mostrarPagosDePoliza(int idPolizaBuscado)
{
    int posPoliza = _polizaArchivo.buscarID(idPolizaBuscado);
    if (posPoliza == -1)
    {
        cout << "No existe una poliza con ese ID." << endl;
        return;
    }

    cout << "Pagos de la poliza " << idPolizaBuscado << ":";
    int cantidad = _pagoArchivo.getCantidadRegistros();

    bool encontrado = false;

    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1) continue;
        if (p.getEliminado()) continue;
        if (p.getIdPoliza() != idPolizaBuscado) continue;

        mostrarLista(p);
        encontrado = true;
    }

    if (!encontrado)
    {
        cout << "No existen pagos para esa poliza.";
    }
}

/****** Consulta por estado del pago ******/

void PagoManager::mostrarPagosPorEstado(int estadoIngresado)
{
    if (estadoIngresado != 0 && estadoIngresado != 1)
    {
        cout << "Opcion invalida. Debe ser 0 (pendiente) o 1 (realizado)." << endl;
        return;
    }

    bool estadoBuscado = (estadoIngresado == 1);

    int cantidad = _pagoArchivo.getCantidadRegistros();
    if (cantidad <= 0)
    {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    bool encontrado = false;

    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1) continue;
        if (p.getEliminado()) continue;
        if (p.getEstado() != estadoBuscado) continue;

        if (!encontrado)
        {
            cout << "Pagos con estado "
                 << (estadoBuscado ? "REALIZADO" : "PENDIENTE")
                 << ":" << endl;
        }

        mostrarLista(p);
        encontrado = true;
    }

    if (!encontrado)
    {
        cout << "No existen pagos con ese estado." << endl;
    }
}


/****** REPORTES ******/

/****** Pagos pendientes por poliza ******/

void PagoManager::reportePagosPendientes()
{
    int cantidad = _pagoArchivo.getCantidadRegistros();
    if (cantidad <= 0)
    {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    Fecha fechaCorte = leerFechaValida();

    int*   polizas  = new int[cantidad];
    int*   meses    = new int[cantidad];
    float* importes = new float[cantidad];
    int    validos  = 0;

    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1)      continue;
        if (p.getEliminado())     continue;
        if (p.getEstado() == true) continue;

        Fecha f = p.getFechaPago();
        if (f > fechaCorte)       continue;

        int idPol = p.getIdPoliza();

        int pos = -1;
        for (int j = 0; j < validos; j++)
        {
            if (polizas[j] == idPol)
            {
                pos = j;
                break;
            }
        }

        if (pos == -1)
        {
            pos = validos;
            polizas[validos]  = idPol;
            meses[validos]    = 0;
            importes[validos] = 0.0;
            validos++;
        }

        meses[pos]++;
        importes[pos] += p.getMonto();
    }

    if (validos == 0)
    {
        cout << "No hay pagos pendientes hasta la fecha indicada." << endl;
        delete[] polizas;
        delete[] meses;
        delete[] importes;
        return;
    }

    cout << endl;
    cout << "PAGOS PENDIENTES AL " << fechaCorte.formatoFecha() << endl;

    cout << left
         << setw(10) << "N POLIZA"
         << setw(30) << "CLIENTE"
         << setw(18) << "MESES ADEUDADOS"
         << setw(15) << "IMPORTE TOTAL" << endl;

    cout << string(73, '-') << endl;

    for (int i = 0; i < validos; i++)
    {
        std::string nombreCliente = "N/D";

        int posPol = _polizaArchivo.buscarID(polizas[i]);
        if (posPol != -1)
        {
            Poliza pol = _polizaArchivo.leer(posPol);
            int idVehiculo = pol.getIdVehiculo();

            int posVeh = _vehiculosArchivo.buscarIdVehiculo(idVehiculo);
            if (posVeh != -1)
            {
                Vehiculo veh = _vehiculosArchivo.leer(posVeh);
                int idCliente = veh.getIdCliente();

                int posCli = _clientesArchivo.buscarIdCliente(idCliente);
                if (posCli != -1)
                {
                    Cliente cli = _clientesArchivo.leer(posCli);
                    nombreCliente = cli.getNombre() + " " + cli.getApellido();
                }
            }
        }

        cout << left
             << setw(10) << polizas[i]
             << setw(30) << nombreCliente
             << setw(18) << meses[i];

        cout << "$ " << importes[i] << endl;
    }

    cout << string(73, '-') << endl;

    delete[] polizas;
    delete[] meses;
    delete[] importes;
}

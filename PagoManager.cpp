#include <iostream>
#include <string>
#include "PagoManager.h"
using namespace std;

PagoManager::PagoManager()
    : _pagoArchivo("pago.dat") {}

void PagoManager::cargar(int idPoliza)
{
    int id = _pagoArchivo.getNuevoID();
    float monto;
    int d,m,a;
    int e;
    string metodo;

    cout << "---------------------" << endl;
    cout << "Cargar nuevo pago" << endl;
    cout << "ID: " << id << endl;
    cout << "ID Poliza: " << idPoliza << endl;

    cout << "Ingrese fecha (DD MM AAAA): ";
    cin >> d >> m >> a;
    Fecha fechaPago;
    fechaPago.setDia(d);
    fechaPago.setMes(m);
    fechaPago.setAnio(a);

    cout << "Ingrese monto: ";
    cin >> monto;

    cout << "Ingrese metodo de pago: ";
    getline(cin >> ws, metodo);

    cout << "Estado (0=pendiente, 1=realizado): ";
    cin >> e;
    bool estado = (e != 0);

    Pago reg;
    reg.setId(id);
    reg.setIdPoliza(idPoliza);
    reg.setFechaPago(fechaPago);
    reg.setMonto(monto);
    reg.setMetodoDePago(metodo);
    reg.setEstado(estado);
    reg.setEliminado(false);

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

void PagoManager::mostrarPagosDePoliza(int idPolizaBuscado)
{
    cout << "Pagos de la poliza " << idPolizaBuscado << ":" << endl;
    int cantidad = _pagoArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++)
    {
        Pago p = _pagoArchivo.leer(i);
        if (p.getId() == -1) continue;
        if (!p.getEliminado() && p.getIdPoliza() == idPolizaBuscado)
        {
            mostrarLista(p);
        }
    }
}

void PagoManager::eliminar(int id)
{
    if (_pagoArchivo.eliminar(id))
        cout << "Pago eliminado." << endl;
    else
        cout << "No se pudo eliminar el pago." << endl;
}

void PagoManager::actualizar()
{
    int id;
    cout << "Ingrese ID de pago a actualizar: ";
    cin >> id;

    int pos = _pagoArchivo.buscarID(id);
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

    int opcion;
    cout << "1) Cambiar monto  2) Cambiar metodo  3) Cambiar estado  0) Cancelar: ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
    {
        float monto;
        cout << "Nuevo monto: ";
        cin >> monto;
        reg.setMonto(monto);
        break;
    }
    case 2:
    {
        string metodo;
        cout << "Nuevo metodo de pago: ";
        getline(cin >> ws, metodo);
        reg.setMetodoDePago(metodo);
        break;
    }
    case 3:
    {
        int e;
        cout << "Nuevo estado (0=pendiente, 1=realizado): ";
        cin >> e;
        reg.setEstado(e != 0);
        break;
    }
    case 0:
        cout << "Actualizacion cancelada." << endl;
        return;
    default:
        cout << "Opcion invalida." << endl;
        return;
    }

    if (_pagoArchivo.sobrescribir(reg, pos))
        cout << "Actualizado." << endl;
    else
        cout << "No se pudo actualizar." << endl;
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


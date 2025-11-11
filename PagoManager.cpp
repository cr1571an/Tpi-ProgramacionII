#include <iostream>
#include <string>
#include <limits>
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
    bool estado;
    int opcionMetodo;
    string metodo;

    cout << "---------------------" << endl;
    cout << "Cargar nuevo pago" << endl;
    cout << "ID: " << id << endl;
    cout << "ID Poliza: " << idPoliza << endl;

    while (true)
    {
        cout << "Ingrese fecha con espacios (DD MM AAAA): ";
        if (!(cin >> d >> m >> a))
        {
            cout << "Entrada invalida.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        int diasMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        bool bisiesto = (a%4==0) && ((a%100!=0) || (a%400==0));
        if (m==2 && bisiesto) diasMes[2] = 29;
        if (a>=2020 && a<=2025 && m>=1 && m<=12 && d>=1 && d<=diasMes[m]) break;

        cout << "Fecha invalida." << endl;
    }

    Fecha fechaPago(d, m, a);

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

void PagoManager::mostrarPagosDePoliza(int idPolizaBuscado)
{
    //int posPoliza = _polizaArchivo.buscarID(idPolizaBuscado);
    //if (posPoliza == -1)
    //{
    //    cout << "No existe una poliza con ese ID." << endl;
    //    return;
    //}

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

void PagoManager::eliminar(int id)
{
    int pos = _pagoArchivo.buscarID(id);
    if (pos == -1)
    {
        cout << "No existe ese ID." << endl;
        return;
    }

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
    while (true)
    {
        cout << "1) Cambiar monto  2) Cambiar metodo  3) Cambiar estado  0) Cancelar: ";
        if (cin >> opcion && opcion >= 0 && opcion <= 3) break;
        cout << "Opcion invalida." << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    switch (opcion)
    {
    case 1:
    {
        float monto;
        while (true)
        {
            cout << "Nuevo monto: ";
            if (cin >> monto && monto > 0) break;
            cout << "Monto invalido." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        reg.setMonto(monto);
        break;
    }
    case 2:
    {
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
            if (cin >> opcionMetodo)
            {
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
            }
            cout << "Opcion invalida." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        reg.setMetodoDePago(metodo);
        break;
    }
    case 3:
    {
        int e;
        while (true)
        {
            cout << "Nuevo estado (0 = pendiente, 1 = realizado): ";
            if (cin >> e && (e == 0 || e == 1)) break;
            cout << "Valor invalido." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        reg.setEstado(e == 1);
        break;
    }
    case 0:
        cout << "Actualizacion cancelada." << endl;
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


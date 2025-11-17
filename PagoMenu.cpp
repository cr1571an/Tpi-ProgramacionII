#include <iostream>
#include <limits>
#include "PagoMenu.h"
using namespace std;

PagoMenu::PagoMenu()
{
    _cantidadOpciones = 8;
}

void PagoMenu::mostrar()
{
    int opcion;
    do
    {
        system("cls");
        mostrarOpciones();
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }
    while (opcion != 0);
}

void PagoMenu::mostrarOpciones()
{
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||               MENU PAGOS              ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR PAGO                   ||
||     2 - MOSTRAR TODOS LOS PAGOS       ||
||     3 - ACTUALIZAR PAGO               ||
||     4 - ELIMINAR PAGO                 ||
||     5 - RECUPERAR PAGO                ||
||     6 - LISTADOS                      ||
||     7 - CONSULTAS                     ||
||     8 - REPORTES                      ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

int PagoMenu::seleccionOpcion()
{
    int opcion;
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones)
    {
        cout << "Opcion incorrecta." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void PagoMenu::ejecutarOpcion(int opcion)
{
    switch (opcion)
    {
        case 1:
        {
            int idPoliza;
            cout << "Ingrese ID de la poliza: ";
            cin >> idPoliza;
            _pagoManager.cargar(idPoliza);
            system("pause");
            break;
        }

        case 2:
            _pagoManager.mostrar();
            system("pause");
            break;

        case 3:
            submenuActualizar();
            break;

        case 4:
        {
            int id;
            cout << "Ingrese ID de pago a eliminar: ";
            cin >> id;
            _pagoManager.eliminar(id);
            system("pause");
            break;
        }

        case 5:
            _pagoManager.recuperar();
            system("pause");
            break;

        case 6:
            submenuListados();
            break;

        case 7:
            submenuConsultas();
            break;

        case 8:
            submenuReportes();
            break;

        case 0:
            break;
    }
}


/****** SUBMENU ACTUALIZAR ******/

void PagoMenu::submenuActualizar()
{
    int opcion;
    do
    {
        system("cls");
        cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             ACTUALIZAR PAGO           ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CAMBIAR FECHA                 ||
||     2 - CAMBIAR MONTO                 ||
||     3 - CAMBIAR METODO DE PAGO        ||
||     4 - CAMBIAR ESTADO                ||
||---------------------------------------||
||     0 - VOLVER AL MENU ANTERIOR       ||
|||||||||||||||||||||||||||||||||||||||||||

)";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                int idPago;
                cout << "Ingrese ID de pago a actualizar: ";
                cin >> idPago;
                _pagoManager.cambiarFecha(idPago);
                system("pause");
                break;
            }

            case 2:
            {
                int idPago;
                cout << "Ingrese ID de pago a actualizar: ";
                cin >> idPago;
                _pagoManager.cambiarMonto(idPago);
                system("pause");
                break;
            }

            case 3:
            {
                int idPago;
                cout << "Ingrese ID de pago a actualizar: ";
                cin >> idPago;
                _pagoManager.cambiarMetodo(idPago);
                system("pause");
                break;
            }

            case 4:
            {
                int idPago;
                cout << "Ingrese ID de pago a actualizar: ";
                cin >> idPago;
                _pagoManager.cambiarEstado(idPago);
                system("pause");
                break;
            }

            case 0:
                // volver al menú anterior
                break;

            default:
                cout << "Opcion incorrecta." << endl;
                system("pause");
                break;
        }
    }
    while (opcion != 0);
}


/****** SUBMENU LISTADOS ******/

void PagoMenu::submenuListados()
{
    int opcion;
    do
    {
        system("cls");
        cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||           LISTADOS DE PAGOS           ||
|||||||||||||||||||||||||||||||||||||||||||
||  1 - ORDENADOS POR FECHA DE PAGO      ||
||  2 - ORDENADOS POR METODO DE PAGO     ||
||---------------------------------------||
||  0 - VOLVER AL MENU ANTERIOR          ||
|||||||||||||||||||||||||||||||||||||||||||

)";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                _pagoManager.listarOrdenadosPorFecha();
                system("pause");
                break;

            case 2:
                _pagoManager.listarOrdenadosPorMetodoPago();
                system("pause");
                break;

            case 0:
                break;

            default:
                cout << "Opcion incorrecta." << endl;
                system("pause");
                break;
        }
    }
    while (opcion != 0);
}


/****** SUBMENU CONSULTAS ******/

void PagoMenu::submenuConsultas()
{
    int opcion;
    do
    {
        system("cls");
        cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||           CONSULTAS DE PAGOS          ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - POR NUMERO DE POLIZA          ||
||     2 - POR ESTADO DEL PAGO           ||
||---------------------------------------||
||     0 - VOLVER AL MENU ANTERIOR       ||
|||||||||||||||||||||||||||||||||||||||||||

)";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                int idPoliza;
                cout << "Ingrese ID de la poliza: ";
                cin >> idPoliza;
                _pagoManager.mostrarPagosDePoliza(idPoliza);
                system("pause");
                break;
            }

            case 2:
            {
                int e;
                cout << "Ingrese estado (0=pendiente, 1=realizado): ";
                cin >> e;
                _pagoManager.mostrarPagosPorEstado(e);
                system("pause");
                break;
            }

            case 0:
                break;

            default:
                cout << "Opcion incorrecta." << endl;
                system("pause");
                break;
        }
    }
    while (opcion != 0);
}


/****** SUBMENU REPORTES ******/

void PagoMenu::submenuReportes()
{
    int opcion;
    do
    {
        system("cls");
        cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             REPORTES DE PAGOS         ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - PAGOS PENDIENTES POR FECHA    ||
||---------------------------------------||
||     0 - VOLVER AL MENU ANTERIOR       ||
|||||||||||||||||||||||||||||||||||||||||||

)";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                _pagoManager.reportePagosPendientes();
                system("pause");
                break;

            case 0:
                break;

            default:
                cout << "Opcion incorrecta." << endl;
                system("pause");
                break;
        }
    }
    while (opcion != 0);
}

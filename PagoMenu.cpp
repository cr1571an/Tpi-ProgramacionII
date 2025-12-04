#include <iostream>
#include <limits>
#include "PagoMenu.h"
using namespace std;

PagoMenu::PagoMenu()
{
    _cantidadOpciones = 6;
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
||     4 - ANULAR PAGO                   ||
||     5 - LISTADOS                      ||
||     6 - CONSULTAS                     ||
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
            system("cls");
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
            cout << "Ingrese ID de pago a anular: ";
            cin >> id;
            _pagoManager.anularPago(id);
            system("pause");
            break;
        }

        case 5:
            submenuListados();
            break;

        case 6:
            submenuConsultas();
            break;

        case 0:
            break;
    }
}


/********* SUBMENU ACTUALIZAR *********/

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
||     2 - CAMBIAR METODO DE PAGO        ||
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
                _pagoManager.cambiarMetodo(idPago);
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


/********* SUBMENU LISTADOS *********/

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


/********* SUBMENU CONSULTAS *********/

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

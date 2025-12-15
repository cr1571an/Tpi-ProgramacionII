#include <iostream>
#include "ReporteMenu.h"
using namespace std;

ReporteMenu::ReporteMenu() : _polizaManager(), _clienteManager(), _pagoManager(), _siniestroManager() {
    _cantidadOpciones = 6;
}

void ReporteMenu::mostrar(){

    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion != 0);
}

void ReporteMenu::mostrarOpciones() {
    cout << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||                      MENU REPORTES                       ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||    1 - HISTORIAL DE PAGOS POR CLIENTE                    ||" << endl;
    cout << "||    2 - POLIZAS POR TIPO DE SEGURO Y FECHA                ||" << endl;
    cout << "||    3 - COBERTURA DE SINIESTROS POR FECHA                 ||" << endl;
    cout << "||    4 - REPORTE DE DEUDA POR CLIENTE                      ||" << endl;
    cout << "||    5 - POLIZAS SIN COBERTURA EN UN PERIODO               ||" << endl;
    cout << "||    6 - RECAUDACION POR PERIODO Y TIPO DE POLIZA          ||" << endl;
    cout << "||----------------------------------------------------------||" << endl;
    cout << "||    0 - VOLVER                                            ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
    cout << "SELECCIONE UNA OPCION: ";
}

int ReporteMenu::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;
    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "OPCION INCORRECTA..."<<endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
    }
    return opcion;
}

void ReporteMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:
            _clienteManager.historialPagosPorCliente();
            break;
        case 2:
            _polizaManager.reportePolizasVigentesYVencidas();
            system("pause");
            break;
        case 3:
            _siniestroManager.reporteCoberturaSiniestros();
            system("pause");
            break;
            case 4:
            _pagoManager.reporteDeudaPorCliente();
            system("pause");
            break;
        case 5:
            _polizaManager.reportePolizasSinCobertura();
            system("pause");
            break;
        case 6:
            _pagoManager.recaudacionPorPeriodoYTipoSeguros();
            system("pause");
            break;
        case 0:
            break;
    }
}

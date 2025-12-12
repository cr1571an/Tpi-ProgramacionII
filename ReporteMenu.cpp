#include <iostream>
#include "ReporteMenu.h"
using namespace std;
ReporteMenu::ReporteMenu(): _polizaManager(), _clienteManager() {
    _cantidadOpciones = 3;
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
    cout << "||    2 - REPORTE DE POLIZAS VIGENTES Y VENCIDAS POR FECHA  ||" << endl;
    cout << "||    3 - REPORTE DE COBERTURA DE SINIESTROS POR FECHA      ||" << endl;
    cout << "||----------------------------------------------------------||" << endl;
    cout << "||    0 - VOLVER                                            ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
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
            system("pause");
            break;
        case 2:
            _polizaManager.reportePolizasVigentesYVencidas();
            system("pause");
            break;
        case 3:
            _siniestroManager.reporteCoberturaSiniestros();
            system("pause");
            break;
        case 0:
            break;
    }
}

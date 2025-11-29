#include <iostream>
#include "ReporteMenu.h"
using namespace std;
ReporteMenu::ReporteMenu(): _polizaManager() {
    _cantidadOpciones = 1;
}
void ReporteMenu::mostrar(){
    
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        if (opcion != 0){
            system("pause");
        }
    }while(opcion != 0);
}

void ReporteMenu::mostrarOpciones(){
    cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||                  MENU REPORTES                           ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||     1 - REPORTE DE POLIZAS VIGENTES Y VENCIDAS POR FECHA ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||     0 - SALIR                                            ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    )";
        cout << "Seleccione una opcion: ";
}

int ReporteMenu::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
    }
    return opcion;

}
void ReporteMenu::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:
            _polizaManager.reportePolizasVigentesYVencidas();
            break;
        case 0:
            cout << "Saliendo del menu de reportes..." << endl;
            break;
    }
    
}
    

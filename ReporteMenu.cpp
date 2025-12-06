#include <iostream>
#include "ReporteMenu.h"

using namespace std;

ReporteMenu::ReporteMenu(){
    _cantidadOpciones = 1;
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
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||                      MENU REPORTES                    ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||    1 - CLIENTES CON SINIESTROS EN DE TERMINADA FECHA  ||" << endl;
    cout << "||-------------------------------------------------------||" << endl;
    cout << "||    0 - VOLVER                                         ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
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
            _reportes.clientesConSiniestrosEntreFecha();
            system("pause");
            break;
        case 0:
            break;
    }
}
#include <iostream>
#include "PolizaMenu.h"
using namespace std;

PolizaMenu::PolizaMenu(){
    _cantidadOpciones = 2;
}
void PolizaMenu::mostrar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

void PolizaMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             MENU POLIZAS              ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR POLIZA                 ||
||     2 - MOSTRAR TODAS LAS POLIZAS     ||
||     3 - ELIMINAR CLIENTE              ||
||     4 - BUSCAR POR D.N.I              ||
||     5 - RECUPERAR CLIENTE             ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

int PolizaMenu::seleccionOpcion(){
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


void PolizaMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:{
            _polizaManager.cargar();
            break;
        }
        case 2:{
            _polizaManager.mostrar();
            break;
        }
            
            
    }
}
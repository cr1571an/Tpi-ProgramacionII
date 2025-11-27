#include <iostream>
#include "App.h"
using namespace std;

App::App(){
    _cantidadOpciones = 5;
}
void App::run(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion != 0);
}

void App::mostrarOpciones() {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||            MENU PRINCIPAL             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - CLIENTES                      ||" << endl;
    cout << "||     2 - VEHICULOS                     ||" << endl;
    cout << "||     3 - POLIZAS                       ||" << endl;
    cout << "||     4 - PAGOS                         ||" << endl;
    cout << "||     5 - SINIESTROS                    ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     0 - CERRAR PROGRAMA               ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
    cout << "SELECCIONE UNA OPCION: ";
}


int App::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;
    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "OPCION INCORRECTA..."<<endl;
        cout << "OPCION: ";
        cin >> opcion;
    }
    return opcion;
}

void App::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1:
            _clienteMenu.mostrar();
            break;
        case 2:
            _vehiculoMenu.mostrar();
            break;
        case 3:
            _polizaMenu.mostrar();
            break;
        case 4:
            _pagoMenu.mostrar();
            break;
        case 5:
            _siniestroMenu.mostrar();
            break;
        case 0:
            cout << "Gracias por utilizar la APP! " << endl;
            break;
    }
}
#include <iostream>
#include "App.h"
using namespace std;

App::App(){
    _cantidadOpciones = 5;
}
void App::run(){
    int opcion;

    do{
      //  system("cls");
        opcion = seleccionOpcion();
       // system("cls");
        ejecutarOpcion(opcion);
    }while(opcion != 0);
}

void App::mostrarOpciones(){
cout << R"(
||||||||||||||||||||||||||||||||||||
||          MENU PRINCIPAL        ||
||||||||||||||||||||||||||||||||||||
||     1 - CLIENTES               ||
||     2 - VEHICULOS              ||
||     3 - POLIZAS                ||
||     4 - PAGOS                  ||
||     5 - SINIESTROS             ||
||||||||||||||||||||||||||||||||||||
||       0 - SALIR                ||
||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}


int App::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Opcion: ";
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
#include <iostream>
#include "ClienteMenu.h"
using namespace std;

ClienteMenu::ClienteMenu(){
    _cantidadOpciones = 5;
}
void ClienteMenu::mostrar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

void ClienteMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             MENU CLIENTES             ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR CLIENTE                ||
||     2 - MOSTRAR TODOS LOS CLIENTES    ||
||     3 - ELIMINAR CLIENTE              ||
||     4 - BUSCAR POR D.N.I              ||
||     5 - RECUPERAR CLIENTE             ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

int ClienteMenu::seleccionOpcion(){
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


void ClienteMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:
            _clienteMenu.cargar();
            break;
        case 2:
            _clienteMenu.mostrar();
            break;
        case 3:
            _clienteMenu.eliminarPorDNI();
            break;
        case 4:
            _clienteMenu.mostrarDatosDeClienteDNI();
            break;
        case 5:
            _clienteMenu.recuperarPorDNI();
            break;
    }
}
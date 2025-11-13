#include <iostream>
#include "PolizaMenu.h"
using namespace std;

PolizaMenu::PolizaMenu(){
    _cantidadOpciones = 6;
    _cantidadOpcionesSubMenuModificar = 3;
}
void PolizaMenu::mostrar(){
    
    int opcion;

    do{
      //  system("cls");
        opcion = seleccionOpcion();
      //  system("cls");
        ejecutarOpcion(opcion);
        //system("pause");
    }while(opcion != 0);
}

void PolizaMenu::subMenuModificar(){
    int opcion;

    do{
       // system("cls");
        opcion = seleccionOpcionSubMenuModificar();
        //system("cls");
        ejecutarOpcionSubMenuModificar(opcion);
      //  system("pause");
    }while(opcion != 0);
}

int PolizaMenu::seleccionOpcionSubMenuModificar(){
    int opcion;
    mostrarOpcionesSubMenuModificar();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpcionesSubMenuModificar){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
    }
    return opcion;
}

void PolizaMenu::mostrarOpcionesSubMenuModificar(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||          MODIFICAR POLIZA             ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - FECHA INICIO                  ||
||     2 - PRIMA MENSUAL                 ||
||     3 - TIPO DE SEGURO                ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

void PolizaMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             MENU POLIZAS              ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR POLIZA                 ||
||     2 - MOSTRAR TODAS LAS POLIZAS     ||
||     3 - ELIMINAR POLIZA               ||
||     4 - BUSCAR POR PATENTE            ||
||     5 - RECUPERAR POLIZA              ||
||     6 - MODIFICAR POLIZA              ||
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
        case 3:{
            _polizaManager.eliminar();
            break;
        }
        case 4:{
            _polizaManager.buscarPorPatente();
            break;
        }
        case 5:{
            _polizaManager.recuperar();
            break;
        }
        case 6:{

            subMenuModificar();
            break;
        }
    }
}

void PolizaMenu::ejecutarOpcionSubMenuModificar(int opcion) {
    switch(opcion) {
        case 1:{
            _polizaManager.modificarFechaInicio();
            break;
        }
        case 2:{
            _polizaManager.modificarPrima();
            break;
        }
        case 3:{
            _polizaManager.modificarTipoSeguro();
            break;
        }
    }
}
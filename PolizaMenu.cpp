#include <iostream>
#include "PolizaMenu.h"
using namespace std;

PolizaMenu::PolizaMenu(){
    _cantidadOpciones = 12;
    _cantidadOpcionesSubMenuModificar = 3;
}
void PolizaMenu::mostrar(){

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

void PolizaMenu::subMenuModificar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcionSubMenuModificar();
        system("cls");
        ejecutarOpcionSubMenuModificar(opcion);
        if (opcion != 0){
            system("pause");
        }
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
||     4 - ACTIVA O INACTIVA             ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - VOLVER AL MENU ANTERIOR       ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

void PolizaMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||||||||||||||
||             MENU POLIZAS                          ||
|||||||||||||||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR POLIZA                             ||
||     2 - MOSTRAR TODAS LAS POLIZAS                 ||
||     3 - ELIMINAR POLIZA                           ||
||     4 - BUSCAR POR DNI CLIENTE                    ||
||     5 - BUSCAR POR PATENTE                        ||
||     6 - RECUPERAR POLIZA                          ||
||     7 - MODIFICAR POLIZA                          ||
||     8 - LISTAR POLIZAS VIGENTES                   ||
||     9 - LISTAR POLIZAS NO VIGENTES                ||
||     10 - LISTAR POLIZAS SIN COBERTURA             ||
||     11 - LISTAR POR FECHA DE VENCIMIENTO          ||
||     12 - LISTAR VENCIMIENTOS POR ID POLIZA        ||
|||||||||||||||||||||||||||||||||||||||||||||||||||||||
||     0 - VOLVER AL MENU ANTERIOR                   ||
|||||||||||||||||||||||||||||||||||||||||||||||||||||||

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
            _polizaManager.buscarPorDniCliente();
            break;
        }
        case 5:{
            _polizaManager.buscarPorPatente();
            break;
        }
        case 6:{
            _polizaManager.recuperar();
            break;
        }
        case 7:{
            subMenuModificar();
            break;
        }
        case 8:{
            _polizaManager.listarPolizasVigentes();
            break;
        }
        case 9:{
            _polizaManager.listarPolizasNoVigentes();
            break;
        }
        case 10:{
            _polizaManager.listarPolizasSinCobertura();
            break;
        }
        case 11:{
            _polizaManager.listarPorFechaVigencia();
            break;
        }
        case 12:{
            _polizaManager.mostrarVencimientosDePoliza();
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

int PolizaMenu::mostrarSeguro() {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||          SELECCIONE UN SEGURO         ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - BASICO RESPONSABILIDAD CIVIL  ||" << endl;
    cout << "||     2 - CONTRA TERCEROS COMPLETO      ||" << endl;
    cout << "||     3 - TODO RIESGO                   ||" << endl;
    cout << "||     4 - CONTRA ROBO E INCENDIO        ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl<< endl;
    int opcion;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        if (opcion < 0 || opcion > 4) {
            cout << "OPCION INCORRECTA..." << endl;
        }
    } while (opcion < 0 || opcion > 4);

    return opcion;
}

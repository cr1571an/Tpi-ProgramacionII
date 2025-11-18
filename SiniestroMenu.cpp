#include <iostream>
#include "SiniestroMenu.h"
using namespace std;

SiniestroMenu::SiniestroMenu(){
    _cantidadOpciones = 8;
    _cantidadOpcionesSubMenuModificar = 4;
}
void SiniestroMenu::mostrar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

void SiniestroMenu::subMenuModificar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcionSubMenuModificar();
        system("cls");
        ejecutarOpcionSubMenuModificar(opcion);
        system("pause");
    }while(opcion != 0);
}

int SiniestroMenu::seleccionOpcionSubMenuModificar(){
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

void SiniestroMenu::mostrarOpcionesSubMenuModificar(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||          MODIFICAR SINIESTRO          ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - FECHA SINIESTRO               ||
||     2 - TIPO SINIESTRO                ||
||     3 - COSTO ESTIMADO                ||
||     4 - ESTADO SINIESTRO              ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

void SiniestroMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||             MENU SINIESTROS           ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR SINIESTRO              ||
||     2 - MOSTRAR TODOS LOS SINIESTROS  ||
||     3 - ELIMINAR SINIESTRO            ||
||     4 - BUSCAR POR ID POLIZA          ||
||     5 - RECUPERAR SINIESTRO           ||
||     6 - MODIFICAR SINIESTRO           ||
||     7 - REPORTE SINIESTROS POR TIPO   ||
||     8 - REPORTE SINIESTROS POR ESTADO ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

int SiniestroMenu::seleccionOpcion(){
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


void SiniestroMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:{
            _siniestroManager.cargar();
            break;
        }
        case 2:{
            _siniestroManager.mostrar();
            break;
        }
        case 3:{
            _siniestroManager.eliminar();
            break;
        }
        case 4:{
            _siniestroManager.buscarPorIdPoliza();
            break;
        }
        case 5:{
            _siniestroManager.recuperar();
            break;
        }
        case 6:{

            subMenuModificar();
            break;
        }
        case 7:{
            _siniestroManager.reporteSiniestrosPorTipo();
            break;
        }
        case 8:{
            _siniestroManager.reporteSiniestrosPorEstado();
            break;
        }
    }
}

void SiniestroMenu::ejecutarOpcionSubMenuModificar(int opcion) {
    switch(opcion) {
        case 1:{
          _siniestroManager.modificarFechaSiniestro();
            break;
        }
        case 2:{
          _siniestroManager.modificarTipoSiniestro();
            break;
        }
        case 3:{
          _siniestroManager.modificarCostoEstimado();
            break;
        }
        case 4:{
          _siniestroManager.modificarEstadoSiniestro();
            break;
        }
    }
}

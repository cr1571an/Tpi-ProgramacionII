#include <iostream>
#include "PagoMenu.h"
using namespace std;


PagoMenu::PagoMenu(){
    _cantidadOpciones = 5;
}

void PagoMenu::mostrar(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

void PagoMenu::mostrarOpciones(){
    cout << R"(
|||||||||||||||||||||||||||||||||||||||||||
||               MENU PAGOS              ||
|||||||||||||||||||||||||||||||||||||||||||
||     1 - CARGAR PAGO                   ||
||     2 - MOSTRAR TODOS LOS PAGOS       ||
||     3 - MOSTRAR PAGOS DE UNA POLIZA   ||
||     4 - ACTUALIZAR PAGO               ||
||     5 - ELIMINAR PAGO                 ||
|||||||||||||||||||||||||||||||||||||||||||
||     0 - SALIR                         ||
|||||||||||||||||||||||||||||||||||||||||||

)";
    cout << "Seleccione una opcion: ";
}

int PagoMenu::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void PagoMenu::ejecutarOpcion(int opcion){
    switch(opcion){
        case 1: {
            int idPoliza;
            cout << "Ingrese ID de la poliza: ";
            cin >> idPoliza;
            _pagoManager.cargar(idPoliza);
            break;
        }
        case 2:
            _pagoManager.mostrar();
            break;
        case 3: {
            int idPoliza;
            cout << "Ingrese ID de la poliza: ";
            cin >> idPoliza;
            _pagoManager.mostrarPagosDePoliza(idPoliza);
            break;
        }
        case 4:
            _pagoManager.actualizar();
            break;
        case 5: {
            int id;
            cout << "Ingrese ID de pago a eliminar: ";
            cin >> id;
            _pagoManager.eliminar(id);
            break;
        }
    }
}

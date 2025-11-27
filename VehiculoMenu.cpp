#include <iostream>
#include "VehiculoMenu.h"
using namespace std;

VehiculoMenu::VehiculoMenu(){
    _cantidadOpciones = 4;
}
void VehiculoMenu::mostrar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
    }while(opcion != 0);
}

void VehiculoMenu::mostrarOpciones() {
    cout << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||             MENU VEHICULOS            ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - CARGAR VEHICULOS              ||" << endl;
    cout << "||     2 - MOSTRAR VEHICULOS             ||" << endl;
    cout << "||     3 - BUSCAR VEHICULO               ||" << endl;
    cout << "||     4 - MODIFICAR                     ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
    cout << "SELECCIONE UNA OPCION: ";
}

int VehiculoMenu::seleccionOpcion(){
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


void VehiculoMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:
            cargar();
            break;
        case 2:
            system("cls");
            _vehiculoManager.mostrar();
            system("pause");
            break;
        case 3:
            buscarVehiculo();
            break;
        case 4:
            modificarVehiculo();
            break;
        case 0:
            break;
    }
}

string VehiculoMenu::mostrarUso() {
    cout << "--------------------------------" << endl;
    cout << "SELECCIONA EL USO DEL VEHICULO:" << endl;
    cout << "1) PARTICULAR" << endl;
    cout << "2) COMERCIAL" << endl;
    cout << "3) CARGA" << endl;
    cout << "4) SERVICIO PUBLICO" << endl;
    cout << "5) ALQUILER" << endl;
    cout << "6) EMERGENCIA" << endl;
    cout << "0) CANCELAR CARGA" << endl;
    cout << "--------------------------------" << endl;
    int opcion;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        if (opcion < 0 || opcion > 6) {
            cout << "OPCION INCORRECTA..." << endl;
        }
    } while (opcion < 0 || opcion > 6);

    if (opcion == 0) {return "";}

    string usos[6] = {"PARTICULAR","COMERCIAL","CARGA","SERVICIO PUBLICO","ALQUILER","EMERGENCIA"};
    return usos[opcion - 1];
}

string VehiculoMenu::mostrarCategoria() {
    cout << "-------------------------------------" << endl;
    cout << "SELECCIONA LA CATEGORIA DEL VEHICULO:" << endl;
    cout << "1) AUTOMOVIL" << endl;
    cout << "2) MOTO" << endl;
    cout << "3) CAMIONETA" << endl;
    cout << "4) COLECTIVO" << endl;
    cout << "5) REMOLQUE" << endl;
    cout << "0) CANCELAR CARGA" << endl;
    cout << "-------------------------------------" << endl;
    int opcion;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        if (opcion < 0 || opcion > 5) {
            cout << "OPCION INCORRECTA..." << endl;
        }
    } while (opcion < 0 || opcion > 5);

    if (opcion == 0) {return "";}

    string categorias[6] = {"AUTOMOVIL","MOTO","CAMIONETA","COLECTIVO","REMOLQUE"};
    return categorias[opcion - 1];
}

void VehiculoMenu::cargar() {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      BUSCAR AL CLIENTE QUE SE         ||" << endl;
    cout << "||    LE QUIERA ASOCIAR EL VEHICULO      ||" << endl;

    int idCliente = _clienteMenu.buscarCliente();
    int pos = _clientesArchivo.buscarIdCliente(idCliente);
    if (idCliente == -3) return;
    if (pos == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        system("pause");
        return;}
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
        cout << "ERROR!. EL CLIENTE ESTA ELIMINADO." << endl;
        _clienteMenu.darAltaCliente(idCliente);
        return;}
    _vehiculoManager.cargar(idCliente);
    system("pause");
}


void VehiculoMenu::buscarVehiculoPorID() {
    cout << "INGRESE EL ID DEL VEHICULO: ";
    int id;
    cin >> id;
    int pos = _vehiculosArchivo.buscarVehiculo(id);
    if (pos == -1) {
        cout << "NO SE ENCONTRO NINGUN VEHICULO CON ESE ID." << endl;
        system("pause");
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
    _vehiculoManager.mostrarLista(vehiculo);
    system("pause");
}

void VehiculoMenu::buscarVehiculoPorPatente() {
    cout << "INGRESE LA PATENTE DEL VEHICULO: ";
    string patente;
    cin >> patente;
    int id = _vehiculoManager.buscarIdPorPatente(patente);
    if (id == -1) {
        cout << "NO SE ENCONTRO NINGUN VEHICULO CON ESA PATENTE." << endl;
        system("pause");
        return;
    }
    int pos = _vehiculosArchivo.buscarVehiculo(id);
    if (pos == -1) {
        cout << "ERROR! AL BUSCAR EL VEHICULO EN EL ARCHIVO." << endl;
        system("pause");
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
    _vehiculoManager.mostrarLista(vehiculo);
}

int VehiculoMenu::seleccionarVehiculo(bool modificar) {
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - POR CLIENTE                    ||" << endl;
    cout << "||     2 - POR PATENTE                    ||" << endl;
    cout << "||     3 - POR ID VEHICULO                ||" << endl;
    cout << "||----------------------------------------||" << endl;
    cout << "||     0 - VOLVER                         ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    int idVehiculo = -1;
    int idCliente;
    switch(opcion) {
        case 1: {
            system("cls");
            idCliente = _clienteMenu.buscarCliente();
            int posCliente = _clientesArchivo.buscarIdCliente(idCliente);
            if (idCliente == -3) return -3;
            if (posCliente < 0) {
                cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
                system("pause");
                return -1;}
            Cliente cliente = _clientesArchivo.leer(posCliente);
            if (cliente.getEliminado()) {
                cout << "EL CLIENTE FUE ELIMINADO." << endl;
                _clienteMenu.darAltaCliente(idCliente);
                return -1;
            }
            int c = _vehiculoManager.mostrarYContarVehiculosDeCliente(idCliente);
            if (!modificar) {
                system("pause");
            }
            if (c == 0) {
                cout << "EL CLIENTE NO TIENE VEHICULOS ASOCIADOS." << endl;
                system("pause");
                return -1;
            }


            if (modificar && c > 0) {
                cout << "INGRESE EL ID DEL VEHICULO QUE DESEA MODIFICAR: ";
                cin >> idVehiculo;
                cin.ignore();
                int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
                if (posVehiculo < 0) {
                    cout << "ERROR. NO EXISTE." << endl;
                    system("pause");
                    return -1;}
                Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
                if (vehiculo.getIdCliente() != idCliente) {
                    cout << "ERROR! NO TIENES NINGUN VEHICULO CON ESE ID." << endl;
                    system("pause");
                    return -1;}
                system("cls");
            }
            break;
        }
        case 2: {
            system("cls");
            cout << "INGRESE LA PATENTE DEL VEHICULO: ";
            string patente;
            cin >> patente;
            idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
            if (idVehiculo == -1) {
                cout << "NO SE ENCONTRO NINGUN VEHICULO CON ESA PATENTE." << endl;
                system("pause");
                return -1;
            }
            return idVehiculo;
        }
        case 3: {
            system("cls");
            cout << "INGRESE EL ID DEL VEHICULO: ";
            cin >> idVehiculo;
            cin.ignore();
            return idVehiculo;
        }
        case 0:
            return -1;
        default: cout << "OPCION INVALIDA." << endl;
            return -1;
    }
    return idVehiculo;
}

void VehiculoMenu::modificarVehiculo() {
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      BUSCAR VEHICULO A MODIFICAR       ||" << endl;
    int idVehiculo = seleccionarVehiculo(true);
    if (idVehiculo < 0) return;

    int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (posVehiculo < 0) {
        cout << "ERROR! EL VEHICULO NO EXISTE." << endl;
        system("pause");
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);

    if (_vehiculoManager.estadoCliente(vehiculo.getIdCliente())) {
        cout << "ERROR! EL CLIENTE ESTA ELIMINADO." << endl;
        system("pause");
        return;
    }
    if (!darAltaClientePorIdVehiculo(posVehiculo)) return;


    if (vehiculo.getEliminado()) {
        cout << "EL VEHICULO ESTA ELIMINADO." << endl;
        darAltaVehiculo(idVehiculo);
        return;
    }
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||          DATOS DEL VEHICULO            ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    _vehiculoManager.mostrarLista(vehiculo);

    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE BAJA                    ||" << endl;
    cout << "||     2 - MODIFICAR PATENTE              ||" << endl;
    cout << "||     3 - MODIFICAR USO                  ||" << endl;
    cout << "||     4 - MODIFICAR CATEGORIA            ||" << endl;
    cout << "||     5 - MODIFICAR NUMERO DE CHASIS     ||" << endl;
    cout << "||     6 - MODIFICAR NUMERO DE MOTOR      ||" << endl;
    cout << "||     7 - MODIFICAR ANIO                 ||" << endl;
    cout << "||----------------------------------------||" << endl;
    cout << "||     0 - VOLVER                         ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    switch (opcion) {
        case 1:
            _vehiculoManager.eliminar(idVehiculo);system("pause"); break;
        case 2:system("cls");
            _vehiculoManager.modificarPatente(idVehiculo); system("pause");break;
        case 3:system("cls");
            _vehiculoManager.modificarUso(idVehiculo); system("pause");break;
        case 4:system("cls");
            _vehiculoManager.modificarCategoria(idVehiculo); system("pause");break;
        case 5:system("cls");
            _vehiculoManager.modificarNumChasis(idVehiculo); system("pause");break;
        case 6:system("cls");
            _vehiculoManager.modificarNumMotor(idVehiculo); system("pause");break;
        case 7:system("cls");
            _vehiculoManager.modificarAnio(idVehiculo); system("pause");break;
        case 0: return;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
}



void VehiculoMenu::darAltaVehiculo(int idVehiculo) {
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE ALTA VEHICULO           ||" << endl;
    cout << "||----------------------------------------||" << endl;
    cout << "||     0 - SALIR                          ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    int opcion;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            if(_vehiculosArchivo.recuperarVehiculo(idVehiculo)) {
                cout << "EL VEHICULO FUE DADO DE ALTA." << endl;
                system("pause");
            }
            break;
        case 0:
            break;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
}

void VehiculoMenu::buscarVehiculo() {
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||            BUSCAR VEHICULO             ||" << endl;
    int idVehiculo = seleccionarVehiculo(false);
    if (idVehiculo < 0) return;
    int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (posVehiculo < 0) {
        cout << "ERROR!. EL VEHICULO NO EXISTE." << endl;
        system("pause");
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
    _vehiculoManager.mostrarLista(vehiculo);
    system("pause");
}

bool VehiculoMenu::darAltaClientePorIdVehiculo(int posVehiculo) {
    Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
    int posCliente = _clientesArchivo.buscarIdCliente(vehiculo.getIdCliente());
    if (posCliente < 0) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        system("pause");
        return false;}
    Cliente cliente = _clientesArchivo.leer(posCliente);
    if (cliente.getEliminado()) {
        cout << "EL CLIENTE FUE ELIMINADO." << endl;
        _clienteMenu.darAltaCliente(vehiculo.getIdCliente());
        system("pause");
        return false;
    }
    return true;
}

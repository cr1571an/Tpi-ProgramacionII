#include <iostream>
#include "VehiculoMenu.h"
using namespace std;

VehiculoMenu::VehiculoMenu(){
    _cantidadOpciones = 5;
}
void VehiculoMenu::mostrar(){
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
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
    cout << "||     5 - REPORTES/LISTADOS             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
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
        case 2: {
            _vehiculoManager.mostrar();
            break;
        }
        case 3: {
            buscarVehiculo();
            break;
        }
        case 4: {
            modificarVehiculo();
            break;
        }
        case 5: {
            mostrarReportes();
            break;
        }
    }
}

string VehiculoMenu::mostrarUso() {
    cout << "|||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||         MENU USO DEL VEHICULO       ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - PARTICULAR                  ||" << endl;
    cout << "||     2 - COMERCIAL                   ||" << endl;
    cout << "||     3 - CARGA                       ||" << endl;
    cout << "||     4 - SERVICIO PUBLICO            ||" << endl;
    cout << "||     5 - ALQUILER                    ||" << endl;
    cout << "||     6 - EMERGENCIA                  ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
    int opcion;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        if (opcion < 1 || opcion > 6) {
            cout << "OPCION INCORRECTA..." << endl;
        }
    } while (opcion < 1 || opcion > 6);

    string usos[6] = {"PARTICULAR", "COMERCIAL", "CARGA",
        "SERVICIO PUBLICO", "ALQUILER", "EMERGENCIA"};
    return usos[opcion-1];
}

string VehiculoMenu::mostrarCategoria() {
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||       MENU CATEGORIA DE VEHICULO       ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - AUTOMOVIL                      ||" << endl;
    cout << "||     2 - MOTO                           ||" << endl;
    cout << "||     3 - CAMIONETA                      ||" << endl;
    cout << "||     4 - COLECTIVO                      ||" << endl;
    cout << "||     5 - REMOLQUE                       ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
    int opcion;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        if (opcion < 1 || opcion > 5) {
            cout << "OPCION INCORRECTA..." << endl;
        }
    } while (opcion < 1 || opcion > 5);
    string categorias[] = {"AUTOMOVIL", "MOTO", "CAMIONETA", "COLECTIVO", "REMOLQUE"};
    return categorias[opcion-1];
}

void VehiculoMenu::cargar() {
    int idCliente = _clienteMenu.buscarCliente();
    int pos = _clientesArchivo.buscarIdCliente(idCliente);
    if (pos == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        return;}
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
        cout << "ERROR!. EL CLIENTE ESTA ELIMINADO." << endl;
        _clienteMenu.darAltaCliente(idCliente);
        return;}
    _vehiculoManager.cargar(idCliente);
}


void VehiculoMenu::mostrarMenuModificar() {
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE BAJA                    ||" << endl;
    cout << "||     2 - PATENTE                        ||" << endl;
    cout << "||     3 - USO                            ||" << endl;
    cout << "||     4 - CATEGORIA                      ||" << endl;
    cout << "||     5 - CHASIS                         ||" << endl;
    cout << "||     6 - MOTOR                          ||" << endl;
    cout << "||     7 - ANIO                           ||" << endl;
    cout << "||     0 - VOLVER                         ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
}

void VehiculoMenu::buscarVehiculoPorID() {
    cout << "INGRESE EL ID DEL VEHICULO: ";
    int id;
    cin >> id;
    int pos = _vehiculosArchivo.buscarVehiculo(id);
    if (pos == -1) {
        cout << "NO SE ENCONTRO NINGUN VEHICULO CON ESE ID." << endl;
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
    _vehiculoManager.mostrarLista(vehiculo);
}

void VehiculoMenu::buscarVehiculoPorPatente() {
    cout << "INGRESE LA PATENTE DEL VEHICULO: ";
    string patente;
    cin >> patente;
    int id = _vehiculoManager.buscarIdPorPatente(patente);
    if (id == -1) {
        cout << "NO SE ENCONTRO NINGUN VEHICULO CON ESA PATENTE." << endl;
        return;
    }
    int pos = _vehiculosArchivo.buscarVehiculo(id);
    if (pos == -1) {
        cout << "ERROR AL BUSCAR EL VEHICULO EN EL ARCHIVO." << endl;
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
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
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
            idCliente = _clienteMenu.buscarCliente();
            int posCliente = _clientesArchivo.buscarIdCliente(idCliente);
            if (posCliente < 0) {
                cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
                return -1;}
            Cliente cliente = _clientesArchivo.leer(posCliente);
            if (cliente.getEliminado()) {
                cout << "EL CLIENTE FUE ELIMINADO." << endl;
                _clienteMenu.darAltaCliente(idCliente);
                return -1;
            }
            _vehiculoManager.mostrarVehiculosDeCliente(idCliente);
            if (modificar) {
                cout << "INGRESE EL ID DEL VEHICULO: ";
                cin >> idVehiculo;
                cin.ignore();
                int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
                if (posVehiculo < 0) {
                    cout << "ERROR. NO EXISTE." << endl;
                    return -1;}
                Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
                if (vehiculo.getIdCliente() != idCliente) {
                    cout << "ERROR: EL VEHICULO NO LE PERTENECE." << endl;
                    return -1;}
            }
            break;
        }
        case 2: {
            cout << "INGRESE LA PATENTE DEL VEHICULO: ";
            string patente;
            cin >> patente;
            idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
            break;
        }
        case 3: {
            cout << "INGRESE EL ID DEL VEHICULO: ";
            cin >> idVehiculo;
            cin.ignore();
            break;
        }
        case 0: cout << "VOLVER AL MENU ANTERIOR..." << endl;
            return -1;
        default: cout << "OPCION INVALIDA." << endl;
            return -1;
    }
    return idVehiculo;
}

void VehiculoMenu::modificarVehiculo() {
    int idVehiculo = seleccionarVehiculo(true);
    if (idVehiculo < 0) return;
    int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (posVehiculo < 0) {
        cout << "ERROR!. EL VEHICULO NO EXISTE." << endl;
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
    if (_vehiculoManager.estadoCliente(vehiculo.getIdCliente())) {
        cout << "ERROR!. EL CLIENTE ELIMINADOsss." << endl;
        return;}
    if (!darAltaClientePorIdVehiculo(posVehiculo)) {
        return;};
    if (vehiculo.getEliminado()) {
        cout << "EL VEHICULO CON ESE ID ESTA ELIMINADO." << endl;
        darAltaVehiculo(idVehiculo);
        return;
    }
    _vehiculoManager.mostrarLista(vehiculo);
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE BAJA                    ||" << endl;
    cout << "||     2 - PATENTE                        ||" << endl;
    cout << "||     3 - USO                            ||" << endl;
    cout << "||     4 - CATEGORIA                      ||" << endl;
    cout << "||     5 - CHASIS                         ||" << endl;
    cout << "||     6 - MOTOR                          ||" << endl;
    cout << "||     7 - ANIO                           ||" << endl;
    cout << "||     0 - VOLVER                         ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
        case 1: _vehiculoManager.eliminar(idVehiculo); break;
        case 2: _vehiculoManager.modificarPatente(idVehiculo); break;
        case 3: _vehiculoManager.modificarUso(idVehiculo); break;
        case 4: _vehiculoManager.modificarCategoria(idVehiculo); break;
        case 5: _vehiculoManager.modificarNumChasis(idVehiculo); break;
        case 6: _vehiculoManager.modificarNumMotor(idVehiculo); break;
        case 7: _vehiculoManager.modificarAnio(idVehiculo); break;
        case 0: cout << "VOLVER AL MENU ANTERIOR..." << endl; break;
        default: cout << "OPCION INVALIDA." << endl; break;
    }
}

void VehiculoMenu::darAltaVehiculo(int idVehiculo) {
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|| 1 - DAR DE ALTA VEHICULO               ||" << endl;
    cout << "|| 0 - VOLVER                             ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    int opcion;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            if(_vehiculosArchivo.recuperarVehiculo(idVehiculo)) {
                cout << "EL VEHICULO FUE DADO DE ALTA." << endl;
            }else cout << "ERROR AL DAR DE ALTA EL VEHICULO." << endl;
            break;
        case 0:
            cout << "VOLVER AL MENU ANTERIOR..." << endl;
            break;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
}

void VehiculoMenu::buscarVehiculo() {
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||            BUSCAR VEHICULO             ||" << endl;
    int idVehiculo = seleccionarVehiculo(false);
    if (idVehiculo < 0) return;
    int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (posVehiculo < 0) {
        cout << "ERROR!. EL VEHICULO NO EXISTE." << endl;
        return;
    }
    Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
    _vehiculoManager.mostrarLista(vehiculo);
}

void VehiculoMenu::mostrarReportes() {
    int opcion;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||        MENU CATEGORIA DE VEHICULO          ||" << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||     1 - LISTADO VEHICULOS ACTIVOS          ||" << endl;
        cout << "||     2 - LISTADO VEHICULOS INACTIVAS        ||" << endl;
        cout << "||     3 - CANTIDAD DE VEHICULO POR ESTADO    ||"<<endl;
        cout << "||     4 - CANTIDAD DE VEHICULO POR USO       ||"<<endl;
        cout << "||     5 - CANTIDAD DE VEHICULO POR CATEGORIA ||"<<endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||     0 - VOLVER                             ||" << endl;
        cout << "||||||||||||||||||||||||||||||||||||||||||||||||" << endl<<endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        switch (opcion) {
            case 1: _vehiculoManager.listadoActivos(false); break;
            case 2: _vehiculoManager.listadoEliminados(false); break;
            case 3: _vehiculoManager.cantidadVehiculosPorEstado(); break;
            case 4: _vehiculoManager.reporteCantidadPorUso();break;
            case 5: _vehiculoManager.reporteCantidadPorCategoria();break;
            case 0: cout << "VOLVER AL MENU ANTERIOR..." << endl; break;
            default: cout << "OPCION INVALIDA." << endl; break;
        }
}

bool VehiculoMenu::darAltaClientePorIdVehiculo(int posVehiculo) {
    Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
    int posCliente = _clientesArchivo.buscarIdCliente(vehiculo.getIdCliente());
    if (posCliente < 0) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        return false;}
    Cliente cliente = _clientesArchivo.leer(posCliente);
    if (cliente.getEliminado()) {
        cout << "EL CLIENTE FUE ELIMINADO." << endl;
        _clienteMenu.darAltaCliente(vehiculo.getIdCliente());
        return false;
    }
    return true;
}
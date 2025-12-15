#include <iostream>
#include "ClienteMenu.h"
#include "utils.h"
using namespace std;

ClienteMenu::ClienteMenu(){
    _cantidadOpciones = 4;
}
void ClienteMenu::mostrar(){
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        ejecutarOpcion(opcion);
        system("cls");
    }while(opcion != 0);
}

void ClienteMenu::mostrarOpciones(){
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||             MENU CLIENTES             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - CARGAR CLIENTE                ||" << endl;
    cout << "||     2 - MOSTRAR TODOS LOS CLIENTES    ||" << endl;
    cout << "||     3 - BUSCAR CLIENTE                ||" << endl;
    cout << "||     4 - MODIFICAR CLIENTE             ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl<< endl;
    cout << "SELECCIONE UNA OPCION: ";
}

int ClienteMenu::seleccionOpcion(){
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


void ClienteMenu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 1:
            _clienteManager.cargar();
            system("pause");
            break;
        case 2:
            _clienteManager.mostrar();
            system("pause");
            break;
        case 3:
            buscar();
            break;
        case 4:
            modificarCliente();
            break;
        case 0:
            break;
    }
}

void ClienteMenu::buscar() {
    system("cls");
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||            BUSCAR CLIENTE             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    int idCliente = buscarCliente();
    if (idCliente == -3) return;
    if (idCliente == -1 || idCliente == -2) return;
    int pos = _clientesArchivo.buscarIdCliente(idCliente);
    if (pos == -1) {
        cout << "ERROR! EL CLIENTE NO EXISTE." << endl;
        system("pause");
        return;
    }
    if (pos == -2) {
        cout << "NO HAY REGISTRO / NO SE PUDO ABRIR." << endl;
        system("pause");
        return;
    }
    _clienteManager.mostrarDatosDeClienteID(idCliente);
    system("pause");
}


int ClienteMenu::buscarCliente() {
    int tipoBusqueda;
    int id;
    cout << "||     1 - POR NUMERO DE CLIENTE (ID)    ||" << endl;
    cout << "||     2 - POR D.N.I                     ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    while (true) {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> tipoBusqueda;
        cin.ignore();
        switch (tipoBusqueda){
            case 0:return -3;
            case 1:
                system("cls");
                cout << "INGRESE EL NUMERO DEL CLIENTE: ";
                cin >> id;
                cin.ignore();
                if (id <= 0){cout << "ID INVALIDO. DEBE SER MAYOR QUE CERO." << endl;
                    continue;}
                return id;
            case 2:
                system("cls");
                cout << "INGRESE EL DNI DEL CLIENTE: ";
                string dni = cargarCadena();
                int pos = _clienteManager.posClientePorDNI(dni);
                if (pos < 0) {
                    cout << "ERROR! EL CLIENTE NO EXISTE." << endl;
                    system("pause");
                    return -1;
                }
                Cliente cliente = _clientesArchivo.leer(pos);
                if (cliente.getEliminado()) {
                    cout << "EL CLIENTE FUE ELIMINADO." << endl;
                    darAltaCliente(cliente.getIdCliente());
                    Cliente clienteRecuperado = _clientesArchivo.leer(pos);
                    if (!clienteRecuperado.getEliminado()) {
                        return clienteRecuperado.getIdCliente();
                    } else {
                        cout << "ERROR! EL CLIENTE NO EXISTE." << endl;
                        system("pause");
                        return -1;
                    }
                }
                return cliente.getIdCliente();
        }
    }
}

void ClienteMenu::modificarCliente() {
    system("cls");
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      BUSCAR CLIENTE A MODIFICAR       ||" << endl;
    int id = buscarCliente();
    if (id == -3 || id == -1) return;
    int pos = _clientesArchivo.buscarIdCliente(id);
    if (pos == -1 || pos == -2) {
        cout << "ERROR! EL CLIENTE NO EXISTE." << endl;
        system("pause");
        return;
    }
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
        cout << "EL CLIENTE ESTA ELIMINADO." << endl;
        if (!darAltaCliente(id)) return;
    }
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||          DATOS DEL CLIENTE             ||" << endl;
    cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
    _clienteManager.mostrarDatosDeClienteID(id);
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE BAJA                   ||" << endl;
    cout << "||     2 - MODIFICAR TELEFONO            ||" << endl;
    cout << "||     3 - MODIFICAR CORREO              ||" << endl;
    cout << "||     4 - MODIFICAR FECHA DE NACIMIENTO ||" << endl;
    cout << "||     5 - MODIFICAR PARTIDO             ||" << endl;
    cout << "||     6 - MODIFICAR LOCALIDAD           ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
        case 1:
            _clienteManager.eliminar(id);
            _vehiculosArchivo.eliminarVehiculosDeCliente(id);
            system("pause");
            break;
        case 2:
            system("cls");
            _clienteManager.modificarTelefono(id);
            system("pause");
            break;
        case 3:
            system("cls");
            _clienteManager.modificarCorreo(id);
            system("pause");
            break;
        case 4:
            system("cls");
            _clienteManager.modificarFechaNacimiento(id);
            system("pause");
            break;
        case 5:
            system("cls");
            _clienteManager.modificarPartido(id);
            system("pause");
            break;
        case 6:
            system("cls");
            _clienteManager.modificarLocalidad(id);
            system("pause");
            break;
        case 0:
            system("cls");
            break;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
}

bool ClienteMenu::darAltaCliente(int id) {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE ALTA                   ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - CANCELAR                      ||" <<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    bool alta = false;
    switch (opcion) {
        case 1: alta = _clienteManager.recuperar(id);
               system("pause");
                system("cls");
            break;
        case 0: break;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
    return alta;
}
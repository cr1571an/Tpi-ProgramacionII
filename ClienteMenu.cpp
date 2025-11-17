#include <iostream>
#include "ClienteMenu.h"
#include "utils.h"
using namespace std;

ClienteMenu::ClienteMenu(){
    _cantidadOpciones = 6;
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
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||             MENU CLIENTES             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - CARGAR CLIENTE                ||" << endl;
    cout << "||     2 - MOSTRAR TODOS LOS CLIENTES    ||" << endl;
    cout << "||     3 - BUSCAR CLIENTE                ||" << endl;
    cout << "||     4 - MODIFICAR CLIENTE             ||" << endl;
    cout << "||     5 - REPORTES/LISTADO              ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
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
            break;
        case 2:
            _clienteManager.mostrar();
            break;
        case 3:
            buscar();
            break;
        case 4:
            modificarCliente();
            break;
        case 5:
            mostrarReportes();
            break;
    }
}

void ClienteMenu::buscar() {
    int id = buscarCliente();
    if (id > 0) {
        _clienteManager.mostrarDatosDeClienteID(id);
    }
    else if (id == -3) {
        cout << "EL CLIENTE ESTA ELIMINADO." << endl;
    }
    else if (id == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
    }
}


int ClienteMenu::buscarCliente() {
    int tipoBusqueda;
    int id = -3;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||            BUSCAR CLIENTE             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - POR NUMERO DE CLIENTE (ID)    ||" << endl;
    cout << "||     2 - POR D.N.I                     ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> tipoBusqueda;
        cin.ignore();
        if (tipoBusqueda == 1) {
            cout << "INGRESE EL NUMERO DEL CLIENTE: ";
            cin >> id;
            cin.ignore();
            int pos = _clientesArchivo.buscarIdCliente(id);
            if (pos == -3) return -3;
            if (pos == -1) return -1;
            return id;
        } else if (tipoBusqueda == 2) {
            cout << "INGRESE EL D.N.I DEL CLIENTE: ";
            string dni = cargarCadena();
            int pos = _clientesArchivo.buscarDNI(dni);
            if (pos == -3) return -3;
            if (pos == -1) return -1;
            Cliente cliente = _clientesArchivo.leer(pos);
            return cliente.getIdCliente();
        } else {
            cout << "OPCION INVALIDA." << endl;
        }
    } while (true);
}

void ClienteMenu::modificarCliente() {
    int id = buscarCliente();
    if (id == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        return;
    }
    int pos = _clientesArchivo.buscarIdCliente(id);
    if (pos == -1) {
        cout << "NO SE PUDO ENCONTRAR EL CLIENTE." << endl;
        return;
    }
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
        cout << "EL CLIENTE CON ESE ID YA FUE ELIMINADO." << endl;
        darAltaCliente(id);
        return;
    }
    _clienteManager.mostrarDatosDeClienteID(id);

    cout << "||         MODIFICAR CLIENTE             ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "|| 1 - DAR DE BAJA                       ||"<<endl;
    cout << "|| 2 - MODIFICAR TELEFONO                ||"<<endl;
    cout << "|| 3 - MODIFICAR CORREO                  ||"<<endl;
    cout << "|| 4 - MODIFICAR FECHA DE NACIMIENTO     ||"<<endl;
    cout << "|| 5 - MODIFICAR PARTIDO/LOCALIDAD       ||"<<endl;
    cout << "|| 0 - VOLVER                            ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl<<endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
        case 1: _clienteManager.eliminar(id); break;
        case 2: _clienteManager.modificarTelefono(id); break;
        case 3: _clienteManager.modificarCorreo(id); break;
        case 4: _clienteManager.modificarFechaNacimiento(id); break;
        case 5: _clienteManager.modificarLocalidad(id); break;
        case 0: cout << "VOLVER AL MENU ANTERIOR..." << endl; break;
        default: cout << "OPCION INVALIDA." << endl; break;
    }
}

void ClienteMenu::darAltaCliente(int id) {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|| 1 - DAR DE ALTA                       ||" << endl;
    cout << "|| 0 - VOLVER                            ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;

    int opcion;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            _clienteManager.recuperar(id);
            break;
        case 0:
            cout << "VOLVER AL MENU ANTERIOR..." << endl;
            break;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
}

void ClienteMenu::mostrarReportes() {
    int opcion;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "||           REPORTES CLIENTES           ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "||     1 - LISTADO POR APELLIDO          ||"<<endl;
    cout << "||     2 - LISTADO ACTIVOS               ||"<<endl;
    cout << "||     3 - LISTADO ELIMINADOS            ||"<<endl;
    cout << "||     4 - CLIENTE POR RANGO DE EDAD     ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "||     0 - VOLVER                        ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl<< endl;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;
    switch (opcion) {
        case 1: _clienteManager.listadoPorApellido(); break;
        case 2: _clienteManager.listadoActivos(); break;
        case 3: _clienteManager.listadoEliminados(); break;
        case 4: //_clienteManager.clientePorRangoEdad(); break;
        case 0: cout << "VOLVER AL MENU ANTERIOR..."<<endl; break;
        default: cout << "OPCION INVALIDA."<<endl; break;
    }
}
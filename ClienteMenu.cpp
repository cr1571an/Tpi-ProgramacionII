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
    int pos = buscarCliente();
    if (pos > 0) {
        _clienteManager.mostrarDatosDeClienteID(pos);
        system("pause");
    }
    else if (pos == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        system("pause");
    }
    else if (pos == -2) {
        cout << "NO HAY REGISTRO / NO SE PUDO ABRIR." << endl;
        system("pause");
    }
    else if (pos == -3) {}
}


int ClienteMenu::buscarCliente() {
    int tipoBusqueda;
    int id;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - POR NUMERO DE CLIENTE (ID)    ||" << endl;
    cout << "||     2 - POR D.N.I                     ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;

    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> tipoBusqueda;
        cin.ignore();
        if (tipoBusqueda == 0) {
            return -3;
        }
        if (tipoBusqueda == 1) {
            system("cls");
            cout << "INGRESE EL NUMERO DEL CLIENTE: ";
            cin >> id;
            cin.ignore();
            return id;
        } else if (tipoBusqueda == 2) {
            system("cls");
            cout << "INGRESE EL D.N.I DEL CLIENTE: ";
            string dni = cargarCadena();
            int pos = _clienteManager.posClientePorDNI(dni);
            if (pos == -1) return -1;
            if (pos == -2)return -2;
            Cliente cliente = _clientesArchivo.leer(pos);
            return cliente.getIdCliente();
        } else {
            cout << "OPCION INVALIDA." << endl;
        }
    } while (true);
}

void ClienteMenu::modificarCliente() {
    system("cls");
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      BUSCAR CLIENTE A MODIFICAR       ||" << endl;
    int id = buscarCliente();
    if (id == -3) return;
    if (id == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        system("pause");
        return;
    }
    int pos = _clientesArchivo.buscarIdCliente(id);
    if (pos == -1) {
        cout << "NO SE PUDO ENCONTRAR EL CLIENTE." << endl;
        system("pause");
        return;
    }
    if (pos == -2) {
        cout << "NO HAY REGISTRO / NO SE PUDO ABRIR." << endl;
        system("pause");
        return;
    }

    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
        cout << "EL CLIENTE ESTA ELIMINADO." << endl;
        darAltaCliente(id);
        return;
    }
    _clienteManager.mostrarDatosDeClienteID(id);
    cout<<endl<< "|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "||            MODIFICAR CLIENTE          ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "||     1 - DAR DE BAJA                   ||"<<endl;
    cout << "||     2 - MODIFICAR TELEFONO            ||"<<endl;
    cout << "||     3 - MODIFICAR CORREO              ||"<<endl;
    cout << "||     4 - MODIFICAR FECHA DE NACIMIENTO ||"<<endl;
    cout << "||     5 - MODIFICAR PARTIDO             ||"<<endl;
    cout << "||     6 - MODIFICAR LOCALIDAD           ||"<<endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||"<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||"<<endl<<endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
        case 1:_clienteManager.eliminar(id);
            _vehiculosArchivo.eliminarVehiculosDeCliente(id);system("pause");break;
        case 2:system("cls");
            _clienteManager.modificarTelefono(id);system("pause");break;
        case 3:system("cls");
            _clienteManager.modificarCorreo(id);system("pause");break;
        case 4:system("cls");
            _clienteManager.modificarFechaNacimiento(id);system("pause");break;
        case 5:system("cls");
            _clienteManager.modificarPartido(id);system("pause");break;
        case 6:system("cls");
            _clienteManager.modificarLocalidad(id);system("pause");break;
        case 0: system("cls");break;
        default: cout << "OPCION INVALIDA." << endl; break;
    }
}

void ClienteMenu::darAltaCliente(int id) {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - DAR DE ALTA                   ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;

    int opcion;
    cout << "SELECCIONE UNA OPCION: ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            _clienteManager.recuperar(id);
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "OPCION INVALIDA." << endl;
            break;
    }
}


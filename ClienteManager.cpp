#include <string>
#include "ClientesArchivo.h"
#include "ClienteManager.h"
#include "LocalidadArchivo.h"

#include <iostream>
#include <bits/ostream.tcc>

#include "utils.h"
using namespace std;


ClienteManager::ClienteManager()
: _clientesArchivo("Clientes.dat") {
};

void ClienteManager::cargar() {
  int id = _clientesArchivo.getID();
  cout << "Cargar Nuevo Cliente " << endl;
  cout << "ID: " << id << endl;
  cout << "Ingrese nombre: ";
  string nombre = cargarCadena();
  cout << "Ingrese apellido: ";
  string apellido = cargarCadena();

  cout << "Ingrese DNI: ";
  string dni = cargarCadena();
  if (!verificarYRegistrarPorDNI(dni)) {
    return;
  }

  cout << "Ingrese telefono: ";
  string telefono = cargarCadena();
  cout << "Ingrese email: ";
  string email = cargarCadena();

  LocalidadArchivo archivo;
  Localidad localidad = archivo.pedirLocalidadPorCodigoPostalInteractivo();
  if (localidad.getCodigoPostal() == 0) {
    return;
  }


  cout << "Partido: " << localidad.getPartido() << endl;
  cout << "Localidad: " << localidad.getLocalidad() << endl;
  cout << "Ingrese fecha de nacimiento." << endl;
  cout << "Ingrese dia: ";
  int dia; cin >> dia;
  cout << "Ingrese mes: ";
  int mes; cin >> mes;
  cout << "Ingrese anio: ";
  int anio; cin >> anio;
  cin.ignore();

  Fecha fechaNacimiento(dia, mes, anio);

  Cliente nuevoCliente(id, nombre, apellido, dni, telefono, email, localidad, fechaNacimiento);

  if (_clientesArchivo.guardar(nuevoCliente)) {
    cout << "Se agrego correctamente." << endl;
  } else {
    cout << "Error! Usuario ya existente." << endl;
  }
}


void ClienteManager::mostrar() {
  int cantidad = _clientesArchivo.getCantidadRegistros();
  Cliente *vCliente = new Cliente[cantidad];

  if(vCliente == nullptr){
    cout << "No se pudo asignar memoria..." << endl;
    exit(0);
  }
  _clientesArchivo.leerTodos(vCliente, cantidad);

  for(int i=0; i<cantidad; i++){
    mostrarLista(vCliente[i]);
  }
  delete [] vCliente;
};


bool ClienteManager::eliminar(int id) {
  if (_clientesArchivo.eliminar(id)) {
    cout << "El usuario fue eliminado correctamente." << endl;
    return true;
  } else {
    cout << "No se pudo eliminar el usuario." << endl;
    return false;
  }
}


bool ClienteManager::recuperar(int id) {
  if (_clientesArchivo.recuperar(id)) {
    cout << "El usuario fue recuperado correctamente." << std::endl;
    return true;
  } else {
    cout << "No se pudo recuperar el usuario." << std::endl;
    return false;
  }
}

void ClienteManager::mostrarLista(Cliente cliente) {
  if (!cliente.getEliminado()) {
    cout << "----------------------------" << endl;
    cout << "ID: " << cliente.getIdCliente() << endl;
    cout << "Nombre: " << cliente.getNombre() << endl;
    cout << "Apellido: " << cliente.getApellido() << endl;
    cout << "DNI: " << cliente.getDni() << endl;
    cout << "Telefono: " << cliente.getTelefono() << endl;
    cout << "Email: " << cliente.getEmail() << endl;
    cout << "Codigo Postal: " << cliente.getLocalidad().getCodigoPostal() << endl;
    cout << "Localidad: " << cliente.getLocalidad().getLocalidad() << endl;
    cout << "Partido: " << cliente.getLocalidad().getPartido() << endl;
    cout << "Fecha de nacimiento: " << cliente.getFechaNacimiento().formatoFecha() << endl;
    cout << "----------------------------" << endl;
  }
}

int ClienteManager::getUltimoId() {
  return _clientesArchivo.getID() - 1;
}

void ClienteManager::mostrarDatosDeClienteDNI() {
    string dni;
    cout << "Ingrese el DNI del cliente: ";
    cin >> dni;
    int p=_clientesArchivo.buscarDNI(dni);
    if(p != -1) {
      Cliente registro = _clientesArchivo.leer(p);
      if (registro.getEliminado()) {
        cout << "El cliente con ese DNI ya fue eliminado."<< endl;
        return;
      }
      mostrarLista(registro);
    }
    else {
      cout << "No se encontro a ningun cliente con ese DNI."<< endl;
    }
}

bool ClienteManager::eliminarPorDNI() {
  string dni;
  cout << "Ingrese el DNI del cliente a eliminar: ";
  cin >> dni;
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
      int id = cliente.getIdCliente();
      return eliminar(id);
    } else {
      cout << "El cliente con ese DNI ya esta eliminado." << endl;
      return false;
    }
  }
  cout << "No se encontro ningun cliente con ese DNI." << endl;
  return false;
}

bool ClienteManager::recuperarPorDNI() {
  string dni;
  cout << "Ingrese el DNI del cliente quiere recuperar: ";
  cin >> dni;
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
      int id = cliente.getIdCliente();
      return recuperar(id);
    } else {
      cout << "El cliente con ese DNI no esta eliminado." << endl;
      return false;
    }
  }
  cout << "No se encontro ningun cliente con ese DNI." << endl;
  return false;
}

int ClienteManager::buscarIdClientePorDNI(std::string& dni) {
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos!=-1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
      return cliente.getIdCliente();
    }
  }
  return -1;
}

bool ClienteManager::verificarYRegistrarPorDNI(std::string dni) {
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
      cout << "El DNI ya esta registrado. No puede volver a registrar." << endl;
      return false;
    } else {
      if (_clientesArchivo.recuperar(cliente.getIdCliente())) {
        cout << "El cliente estaba eliminado y fue habilitado nuevamente." << endl;
        return false;
      } else {
        cout << "No se pudo recuperar el cliente." << endl;
        return false;
      }
    }
  }
  return true;
}
#include <string>
#include "ClientesArchivo.h"
#include "ClienteManager.h"

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

  int p = _clientesArchivo.buscarDNI(dni);
  if (p != -1) {
    Cliente registro = _clientesArchivo.leer(p);
    if (!registro.getEliminado()) {
      cout << "Ya estás registrado." <<endl;
      return;
    }
    else {
      int opcion;
      cout << "Ya tienes una cuenta registrada. ¿Quieres volver a habilitarla?" <<endl;
      cout << "1. Sí" << endl;
      cout << "2. No" << endl;
      cout << "Opción: ";
      cin >> opcion;
      if (opcion == 1) {
        registro.recuperar();
        _clientesArchivo.eliminar(registro.getIdCliente());
        _clientesArchivo.guardar(registro);
        cout << "Se habilitó correctamente." << endl;
      }
      return;
    }
  }

  cout << "Ingrese teléfono: ";
  string telefono = cargarCadena();
  cout << "Ingrese email: ";
  string email = cargarCadena();

  if (_clientesArchivo.guardar(Cliente(id, nombre, apellido, dni, telefono, email))) {
    cout << "Se agregó correctamente." << endl;
  } else {
    cout << "¡Error! Usuario ya existente." << endl;
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
    std::cout << "El usuario fue recuperado correctamente." << std::endl;
    return true;
  } else {
    std::cout << "No se pudo recuperar el usuario." << std::endl;
    return false;
  }
}

void ClienteManager::mostrarLista(Cliente cliente) {
  if (!cliente.getEliminado()) {
    cout << "----------------------------" <<endl;
    cout << "ID: "<< cliente.getIdCliente() << endl;
    cout << "Nombre: "<< cliente.getNombre() << endl;
    cout << "Apellido: "<< cliente.getApellido() << endl;
    cout << "DNI: "<< cliente.getDni() << endl;
    cout << "Telefono: "<< cliente.getTelefono() << endl;
    cout << "Email: "<< cliente.getEmail() << endl;
    cout << "----------------------------" <<endl;
  }
};

int ClienteManager::getUltimoId() {
  return _clientesArchivo.getID() - 1;
}


void ClienteManager::mostrarDatosDeClienteDNI() {
    std::string dni;
    std::cout << "Ingrese el DNI del cliente: ";
    std::cin >> dni;
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
      cout << "No se encontró a ningún cliente con ese DNI."<< endl;
    }
}



bool ClienteManager::eliminarPorDNI() {
  std::string dni;
  std::cout << "Ingrese el DNI del cliente a eliminar: ";
  std::cin >> dni;
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()){
      int id = cliente.getIdCliente();
      return eliminar(id);
    }
    else {
      std::cout << "El cliente con ese DNI ya está eliminado." << std::endl;
      return false;
    }
  }
  std::cout << "No se encontró ningún cliente con ese DNI." << std::endl;
  return false;
}


bool ClienteManager::recuperarPorDNI() {
  std::string dni;
  std::cout << "Ingrese el DNI del cliente quiere recuperar: ";
  std::cin >> dni;
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()){
      int id = cliente.getIdCliente();
      return recuperar(id);
    }
    else {
      std::cout << "El cliente con ese DNI no está eliminado." << std::endl;
      return false;
    }
  }
  std::cout << "No se encontró ningún cliente con ese DNI." << std::endl;
  return false;
}


int ClienteManager::buscarIdClientePorDNI(const std::string& dni) {
  int pos = _clientesArchivo.buscarDNI(dni);
  if (pos!=-1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
      return cliente.getIdCliente();
    }
  }
  return -1;
}
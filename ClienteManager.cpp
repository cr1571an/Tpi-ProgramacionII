#include <string>
#include "ClientesArchivo.h"
#include "ClienteManager.h"

#include <iostream>
#include <bits/ostream.tcc>

#include "utils.h"
using namespace std;


ClienteManager::ClienteManager() {

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
  cout << "Ingrese telefono: ";
  string telefono = cargarCadena();
  cout << "Ingrese email: ";
  string email = cargarCadena();

  if(_clientesArchivo.guardar(Cliente(id, nombre, apellido, dni, telefono, email))){
    cout << "Se agrego correctamente" << endl;
  }
  else {
    cout << "Error! Usuario ya existente." << endl;
  }
};

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



void ClienteManager::eliminar(int id) {
  if (_clientesArchivo.eliminar(id)) {
    cout << "Cliente eliminado correctamente." << endl;
  } else {
    cout << "No se pudo eliminar el cliente." << endl;
  }
}


void ClienteManager::actualizar() {

};


void ClienteManager::mostrarLista(Cliente cliente) {
  cout << "----------------------------" <<endl;
  cout << "ID: "<< cliente.getIdCliente() << endl;
  cout << "Nombre: "<< cliente.getNombre() << endl;
  cout << "Apellido: "<< cliente.getApellido() << endl;
  cout << "DNI: "<< cliente.getDni() << endl;
  cout << "Telefono: "<< cliente.getTelefono() << endl;
  cout << "Email: "<< cliente.getEmail() << endl;
  cout << "----------------------------" <<endl;
};



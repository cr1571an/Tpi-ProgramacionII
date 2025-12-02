#include <string>
#include "ClientesArchivo.h"
#include "ClienteManager.h"
#include "LocalidadArchivo.h"

#include <iostream>
#include <bits/ostream.tcc>

#include "utils.h"
using namespace std;


ClienteManager::ClienteManager()
: _clientesArchivo() {
}

void ClienteManager::cargar() {
  system("cls");
  cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
  cout <<"||            ACLARACION!          ||"<<endl;
  cout <<"||  SI INGRESAS '0' EN CUALQUIER   ||"<<endl;
  cout <<"||  CAMPO, LA CARGA SE CANCELARA   ||"<<endl;
  cout <<"||  AUTOMATICAMENTE.               ||"<<endl;
  cout <<"|||||||||||||||||||||||||||||||||||||" << endl;
  system("pause");
  system("cls");
  int idVehiculo = _clientesArchivo.getIdClienteUltimo();
  cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
  cout <<"||       CARGAR NUEVO CLIENTE      ||"<<endl;
  cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
  cout << "NUMERO DEL CLIENTE: " << idVehiculo<<endl;
  cout << "INGRESA EL NOMBRE: ";
  string nombre = cargarCadena(); if (cortarSiCero(nombre)) return;
  cout << "INGRESA APELLLIDO: ";
  string apellido = cargarCadena(); if (cortarSiCero(apellido)) return;
  cout << "INGRESA D.N.I: ";
  string dni = cargarCadena(); if (cortarSiCero(dni)) return;
  if (!verificarRegistroPorDNI(dni)){cout << "EL D.N.I YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<<endl;return;}
  cout << "INGRESA TELEFONO: ";
  string telefono = cargarCadena(); if (cortarSiCero(telefono)) return;
  if (!telefonoDisponible(telefono)) {cout <<"EL TELEFONO YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<< endl;return;}
  cout << "INGRESAR CORREO: ";
  string correo = cargarCadena(); if (cortarSiCero(correo)) return;
  if (!correoDisponible(correo)) {cout <<"EL CORREO YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<< endl;return;}
  cout << "INGRESAR FECHA DE NACIMIENTO."<<endl;
  Fecha fechaNacimiento = leerFechaValida();
  if (!validarEdad(fechaNacimiento)) return;

  LocalidadArchivo archivo;
  Localidad localidad = archivo.pedirLocalidadPorCodigoPostalInteractivo();
  if (localidad.getCodigoPostal() == 0) {return;}

  Cliente nuevoCliente(idVehiculo, nombre, apellido, dni, telefono, correo, false,localidad, fechaNacimiento);

  if (_clientesArchivo.guardar(nuevoCliente)) {
    cout << "SE AGREGO CORRECTAMENTE." <<endl;
  } else {
    cout << "ERROR! NO SE PUDO GUARDAR." <<endl;
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
    mostrarLista(vCliente[i], false);
  }
  delete [] vCliente;
}

bool ClienteManager::eliminar(int idCliente) {
  if (_clientesArchivo.eliminar(idCliente)) {
    cout << "EL CLIENTE FUE ELIMINADO CORRECTAMENTE."<<endl;
    return true;
  } else {
    cout << "NO SE PUDO ELIMINAR AL CLIENTE."<<endl;
    return false;
  }
}

bool ClienteManager::recuperar(int idCliente) {
  if (_clientesArchivo.recuperar(idCliente)) {
    cout << "EL CLIENTE FUE RECUPERADO CORRECTAMENTE."<<endl;
    return true;
  } else {
    cout << "NO SE PUDO RECUPERAR EL CLIENTE."<<endl;
    return false;
  }
}

void ClienteManager::mostrarLista(Cliente cliente, bool mostrarDatosDeCliente) {
  if (cliente.getEliminado() == mostrarDatosDeCliente) {
    cout <<endl;
    cout << "NUMERO DEL CLIENTE: " << cliente.getIdCliente()<<endl;
    cout << "NOMBRE: " << cliente.getNombre()<<endl;
    cout << "APELLIDO: " << cliente.getApellido()<<endl;
    cout << "D.N.I: " << cliente.getDni()<<endl;
    cout << "TELEFONO: " << cliente.getTelefono()<<endl;
    cout << "CORREO: " << cliente.getEmail()<<endl;
    cout << "FECHA DE NACIMIENTO: " << cliente.getFechaNacimiento().formatoFecha()<<endl;
    cout << "PARTIDO: " << cliente.getLocalidad().getPartido()<<endl;
    cout << "LOCALIDAD: " << cliente.getLocalidad().getLocalidad()<<endl;
    cout << "CODIGO POSTAL: " << cliente.getLocalidad().getCodigoPostal()<<endl<<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" <<endl;
  }
}

void ClienteManager::mostrarDatosDeClienteDNI() {
    string dni;
    cout << "INGRESE EL D.N.I DEL CLIENTE: ";
    cin >> dni;
    int p=posClientePorDNI(dni);
    if(p != -1) {
      Cliente registro = _clientesArchivo.leer(p);
      if (registro.getEliminado()) {
        cout << "EL CLIENTE CON ESE D.N.I YA FUE ELIMINADO."<<endl;
        return;
      }
      mostrarLista(registro,false);
    }
    else {
      cout << "NO SE ENCONTRO A NINGUN CLIENTE CON ESE D.N.I."<<endl;
    }
}

bool ClienteManager::eliminarPorDNI() {
  string dni;
  cout << "INGRESE EL D.N.I DEL CLIENTE A ELIMINAR: ";
  cin >> dni;
  int pos = posClientePorDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
      int id = cliente.getIdCliente();
      return eliminar(id);
    } else {
      cout << "EL CLIENTE CON ESE D.N.I YA ESTA ELIMINADO." << endl;
      return false;
    }
  }
  cout << "NO SE ENCONTRO NINGUN CLIENTE CON ESE D.N.I." << endl;
  return false;
}

bool ClienteManager::recuperarPorDNI() {
  string dni;
  cout << "INGRESE EL D.N.I DEL CLIENTE QUIERES RECUPERAR: ";
  cin >> dni;
  int pos = posClientePorDNI(dni);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (cliente.getEliminado()) {
      int id = cliente.getIdCliente();
      return recuperar(id);
    } else {
      cout << "EL CLIENTE CON ESE D.N.I NO ESTA ELIMINADO."<<endl;
      return false;
    }
  }
  cout << "NO SE ENCONTRO NINGUN CLIENTE CON ESE D.N.I."<<endl;
  return false;
}

int ClienteManager::posClientePorDNI( string dni) {
  int total = _clientesArchivo.getCantidadRegistros();
  Cliente reg;

  for (int i = 0; i < total; i++) {
    reg = _clientesArchivo.leer(i);
    if (reg.getDni() == dni) {
      return i;
    }
  }
  return -1;
}

bool ClienteManager::verificarRegistroPorDNI(string dni) {
  int pos = posClientePorDNI(dni);
  if (pos != -1 && pos != -2 ) {
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
      return false;
    } else {
      return false;
    }
  }
  return true;
}

bool ClienteManager::telefonoDisponible(string telefono) {
  int cant = _clientesArchivo.getCantidadRegistros();
  Cliente *clientes = new Cliente[cant];
  _clientesArchivo.leerTodos(clientes, cant);
  for (int i = 0; i < cant; ++i) {
    if (!clientes[i].getEliminado() && clientes[i].getTelefono() == telefono) {
      delete[] clientes;
      return false;
    }
  }
  delete[] clientes;
  return true;
}

bool ClienteManager::correoDisponible(string correo) {
  int cant = _clientesArchivo.getCantidadRegistros();
  Cliente *clientes = new Cliente[cant];
  _clientesArchivo.leerTodos(clientes, cant);
  for (int i = 0; i < cant; ++i) {
    if (!clientes[i].getEliminado() && clientes[i].getEmail() == correo) {
      delete[] clientes;
      return false;
    }
  }
  delete[] clientes;
  return true;
}

void ClienteManager::mostrarDatosDeClienteID(int idCliente) {
  int pos = _clientesArchivo.buscarIdCliente(idCliente);
  if (pos != -1) {
    Cliente registro = _clientesArchivo.leer(pos);
    if (registro.getEliminado()) {
      cout << "EL CLIENTE CON ESE ID YA FUE ELIMINADO."<<endl;
      return;
    }
    mostrarLista(registro, false);
  } else {
    cout << "NO SE ENCONTRO NINGUN CLIENTE CON ESE ID."<<endl;
  }
}

void ClienteManager::modificarTelefono(int idCliente) {
  int pos = _clientesArchivo.buscarIdCliente(idCliente);
  if (pos != -1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    cout << "INGRESE EL NUEVO TELEFONO: ";
    string nuevoTelefono = cargarCadena();
    if (!telefonoDisponible(nuevoTelefono)) {
      cout << "ERROR!. TELEFONO YA UTILIZADO."<<endl;
      return;
    }
    cliente.setTelefono(nuevoTelefono);
    if (_clientesArchivo.actualizarRegistro(pos, cliente)) {
      cout << "TELEFONO MODIFICADO CORRECTAMENTE."<<endl;
    } else {
      cout << "NO SE PUDO MODIFICAR EL TELEFONO."<<endl;
    }
  } else {
    cout << "CLIENTE NO ENCONTRADO."<<endl;
  }
}

void ClienteManager::modificarCorreo(int idCliente) {
  int pos = _clientesArchivo.buscarIdCliente(idCliente);
  if (pos!=-1){
    Cliente cliente = _clientesArchivo.leer(pos);
    cout << "INGRESE EL NUEVO CORREO: ";
    string nuevoCorreo = cargarCadena();
    if (!correoDisponible(nuevoCorreo)) {
      cout << "ERROR!. CORREO YA UTILIZADO."<<endl;
      return;
    }
    cliente.setEmail(nuevoCorreo);
    if (_clientesArchivo.actualizarRegistro(pos, cliente)) {
      cout << "CORREO MODIFICADO CORRECTAMENTE."<<endl;
    } else {
      cout << "NO SE PUDO MODIFICAR EL CORREO."<<endl;
    }
  } else {
    cout << "CLIENTE NO ENCONTRADO."<<endl;
  }
}

void ClienteManager::modificarFechaNacimiento(int idCliente) {
  int pos = _clientesArchivo.buscarIdCliente(idCliente);
  if (pos!=-1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    cout << "INGRESAR FECHA DE NACIMIENTO."<<endl;
    Fecha fechaNacimiento = leerFechaValida();

    if (!validarEdad(fechaNacimiento)) return;

    cliente.setFechaNacimiento(fechaNacimiento);
    if (_clientesArchivo.actualizarRegistro(pos, cliente)){
      cout << "FECHA DE NACIMIENTO MODIFICADA CORRECTAMENTE."<<endl;
    } else {
      cout << "NO SE PUDO MODIFICAR LA FECHA DE NACIMIENTO."<<endl;
    }
  } else {
    cout << "CLIENTE NO ENCONTRADO."<< endl;
  }
}

void ClienteManager::modificarLocalidad(int idCliente) {
  int pos = _clientesArchivo.buscarIdCliente(idCliente);
  if (pos!=-1){
    Cliente cliente = _clientesArchivo.leer(pos);
    LocalidadArchivo archivoLocalidad;
    Localidad nuevaLocalidad = archivoLocalidad.pedirLocalidadPorCodigoPostalInteractivo();
    if (nuevaLocalidad.getCodigoPostal() == 0){
      cout << "NO SE SELECCIONO UNA LOCALIDAD VALIDA."<<endl;
      return;
    }
    cliente.setLocalidad(nuevaLocalidad);
    if (_clientesArchivo.actualizarRegistro(pos, cliente)) {
      cout << "LOCALIDAD MODIFICADA CORRECTAMENTE."<<endl;
    } else {
      cout << "NO SE PUDO MODIFICAR LA LOCALIDAD."<<endl;
    }
  } else {
    cout << "CLIENTE NO ENCONTRADO." <<endl;
  }
}

bool ClienteManager::validarEdad(Fecha fechaNacimiento) {
  Fecha fechaActual;
  int resultado = fechaNacimiento.validarEdad(fechaActual);
  if (resultado ==-2) {
    cout << "ERROR! DEBE SER MAYOR DE EDAD."<<endl;
    return false;
  }
  if (resultado==-1) {
    cout << "ERROR! NO PUEDE TENER MAS DE 105 ANIOS."<<endl;
    return false;
  }
  return true;
}

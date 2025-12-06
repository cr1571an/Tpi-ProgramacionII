#include <string>
#include "ClientesArchivo.h"
#include "ClienteManager.h"
#include <iostream>
#include <bits/ostream.tcc>

#include "utils.h"
using namespace std;


ClienteManager::ClienteManager()
: _clientesArchivo(), _vehiculosArchivo(), _polizasArchivo(), _siniestroArchivo(), _siniestroManager(), _tiposSiniestrosArchivo() {
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
  int idCliente = _clientesArchivo.getIdClienteUltimo();
  cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
  cout <<"||       CARGAR NUEVO CLIENTE      ||"<<endl;
  cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
  cout << "NUMERO DEL CLIENTE: " << idCliente<<endl;
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
  cout << "INGRESAR PARTIDO: ";
  string partido = cargarCadena(); if (cortarSiCero(correo)) return;
  cout << "INGRESAR LOCALIDAD: ";
  string localidad = cargarCadena(); if (cortarSiCero(correo)) return;

  Cliente nuevoCliente(idCliente, nombre, apellido, dni, telefono, correo, partido, localidad, false, fechaNacimiento);

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
    cout << "PARTIDO: " << cliente.getPartido()<<endl;
    cout << "LOCALIDAD: " << cliente.getLocalidad()<<endl;
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
      cout << "EL CLIENTE ESTA ELIMINADO."<<endl;
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
  if (pos!=-1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    cout << "INGRESAR LOCALIDAD: ";
    string localidad = cargarCadena();
    cliente.setLocalidad(localidad);
    if (_clientesArchivo.actualizarRegistro(pos, cliente)){
      cout << "LOCALIDAD MODIFICADA CORRECTAMENTE."<<endl;
    } else {
      cout << "NO SE PUDO MODIFICAR LA LOCALIDAD."<<endl;
    }
  } else {
    cout << "CLIENTE NO ENCONTRADO."<< endl;
  }
}

void ClienteManager::modificarPartido(int idCliente) {
  int pos = _clientesArchivo.buscarIdCliente(idCliente);
  if (pos!=-1) {
    Cliente cliente = _clientesArchivo.leer(pos);
    cout << "INGRESAR EL NUEVO PARTIDO: ";
    string partido = cargarCadena();
    cliente.setLocalidad(partido);
    if (_clientesArchivo.actualizarRegistro(pos, cliente)){
      cout << "PARTIDO MODIFICADO CORRECTAMENTE."<<endl;
    } else {
      cout << "NO SE PUDO MODIFICAR EL PARTIDO."<<endl;
    }
  } else {
    cout << "CLIENTE NO ENCONTRADO."<< endl;
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

void ClienteManager::clientesConSiniestrosEntreFecha() {
  int cantClientes = _clientesArchivo.getCantidadRegistros();
  if ( cantClientes== 0) {cout << "NO HAY CLIENTES REGISTRADOS."<< endl;return;}
  int cantVehiculos = _vehiculosArchivo.cantidadRegistros();
  if (cantVehiculos == 0) {cout << "NO HAY VEHICULOS REGISTRADOS." <<endl;return;}
  int cantSiniestros = _siniestroArchivo.getCantidadRegistros();
  if (cantSiniestros == 0) {cout << "NO HAY SINIESTROS REGISTRADOS." <<endl;return;}
  int cantPolizas = _polizasArchivo.getCantidadRegistros();
  if (cantPolizas == 0) {cout << "NO HAY POLIZAS REGISTRADOS." << endl;return;}
  cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
  cout << "| CONSULTA DE CLIENTES CON SINIESTROS EN DETERMINADA FECHAS  |"<<endl;
  cout << "--------------------------------------------------------------"<<endl<< endl;
  cout << "INGRESE LA FECHA DE INICIO DEL PERIODO"<<endl;
  Fecha fechaInicio = leerFechaValida();
  if (fechaInicio.getAnio() == -1){return;}
  Fecha hoy;
  cout << "INGRESE LA FECHA DE FIN DEL PERIODO"<< endl;
  Fecha fechaFin = leerFechaValida();
  if ( fechaFin > hoy){cout << "ERROR! LA FECHA DE FIN NO PUEDE MAYOR A LA FECHA DE HOY." <<endl;return;}
  if (fechaInicio.getAnio() == -1){return;}
  if (fechaFin < fechaInicio){cout << "ERROR! LA FECHA DE FIN NO PUEDE SER MENOR A LA FECHA DE INICIO." <<endl;
      return;
  }
  bool seEncontroAlMenosUno = false;
  bool titilo = true;
  system("cls");
  // RECORRE TODOS LOS SINIESTROS
  for (int i = 0; i < cantSiniestros; ++i){
      Siniestro s = _siniestroArchivo.leer(i);
      if (s.getEliminado())continue;
      Fecha f = s.getFechaSiniestro();
      if (f >= fechaInicio && f <= fechaFin){
          // BUSCA LA POLIZA RELACIONADA AL SINIESTRO EN CUESTION
          int idPoliza = s.getIdPoliza();
          Poliza poliza;
          bool polizaEncontrada= false;
          for (int j = 0; j < cantPolizas; ++j) {
              Poliza p = _polizasArchivo.leer(j);
              if (!p.getEliminado() && p.getId() == idPoliza){
                  poliza = p;
                  polizaEncontrada = true;
                  break;
              }
          }
          if (!polizaEncontrada)continue;
          // BUSCA EL VEHICULO DE LA POLIZA
          int idVehiculo = poliza.getIdVehiculo();
          Vehiculo vehiculo;
          bool vehiculoEncontrado=false;
          for (int k = 0; k < cantVehiculos; ++k){
              Vehiculo v = _vehiculosArchivo.leer(k);
              if (!v.getEliminado() && v.getIdVehiculo() == idVehiculo){
                  vehiculo = v;
                  vehiculoEncontrado =true;
                  break;
              }
          }
          if (!vehiculoEncontrado)continue;
          // BUSCA EL CLIENTE QUE ESTA ASOCIADO EL VEHICULO
          int idCliente = vehiculo.getIdCliente();
          Cliente cliente;
          bool clienteEncontrado= false;
          for(int l = 0; l < cantClientes; ++l){
              Cliente c = _clientesArchivo.leer(l);
              if (!c.getEliminado() && c.getIdCliente() == idCliente){
                  cliente = c;
                  clienteEncontrado =true;
                  break;
              }
          }
          // SI NO SE ENCONTRO EL CLIENTE (SIGUE)
          if(!clienteEncontrado)continue;
          seEncontroAlMenosUno = true;
          if (seEncontroAlMenosUno && titilo) {
              titilo = false;
              cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
              cout << "  CLIENTES QUE REGISTRARON SINIESTROS ENTRE LAS FECHAS "<<fechaInicio.formatoFecha()<< " Y " <<fechaFin.formatoFecha()<<endl;
              cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<< endl;
          }
          cout <<"CLIENTE: " <<cliente.getNombre()<< " " << cliente.getApellido()<< " | DNI: " <<cliente.getDni()<<endl;
          cout <<"TIPO DE SINIESTRO : " <<_tiposSiniestrosArchivo.leer(_tiposSiniestrosArchivo.buscarID(s.getId())).getDescripcion()<<endl;
          cout <<"FECHA: " <<f.formatoFecha()<< " | PRESUPUESTO: $" <<s.getCostoEstimado()<<endl;
          cout << "---------------------------------------------" << endl;
      }
  }
  if (!seEncontroAlMenosUno) {
      cout << "NO SE REGISTRARON SINIESTROS EN ESE PERIODO."<<endl;
  }
}

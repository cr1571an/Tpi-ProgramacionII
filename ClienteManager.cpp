#include <string>
#include "ClientesArchivo.h"
#include "ClienteManager.h"
#include <iostream>
#include <bits/ostream.tcc>
#include "ClienteMenu.h"
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
  if (!verificarRegistroPorDNI(dni)){cout << "EL D.N.I YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<<endl;mensajeCargaCancelada();return;};
  cout << "INGRESA TELEFONO: ";
  string telefono = cargarCadena(); if (cortarSiCero(telefono)) {mensajeCargaCancelada();return;};
  if (!telefonoDisponible(telefono)) {cout <<"EL NUMERO DE TELEFONO YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<< endl;mensajeCargaCancelada();return;};
  cout << "INGRESAR CORREO: ";
  string correo = cargarCadena(); if (cortarSiCero(correo)) {mensajeCargaCancelada();return;};
  if (!correoDisponible(correo)) {cout <<"EL CORREO YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<< endl;mensajeCargaCancelada();return;};
  cout << "INGRESAR FECHA DE NACIMIENTO."<<endl;
  Fecha fechaNacimiento = leerFechaValida();
  if (fechaNacimiento.getAnio() == -1) {mensajeCargaCancelada();return;};
  if (!validarEdad(fechaNacimiento)) return;
  cout << "INGRESAR PARTIDO: ";
  string partido = cargarCadena(); if (cortarSiCero(correo)){mensajeCargaCancelada();return;};
  cout << "INGRESAR LOCALIDAD: ";
  string localidad = cargarCadena(); if (cortarSiCero(correo)) {mensajeCargaCancelada();return;};

  Cliente nuevoCliente(idCliente, nombre, apellido, dni, telefono, correo, partido, localidad, false, fechaNacimiento);

  if (_clientesArchivo.guardar(nuevoCliente)) {
    cout << "SE AGREGO CORRECTAMENTE." <<endl;
  } else {
    cout << "ERROR! NO SE PUDO GUARDAR." <<endl;
  }
}

void ClienteManager::mostrar() {
  cout << "============================================" << endl;
  cout << "          LISTADO DE LOS CLIENTES           " << endl;
  cout << "============================================" << endl;
  int cantidad = _clientesArchivo.getCantidadRegistros();
  if (cantidad == 0) {cout << "NO HAY CLIENTES REGISTRADOS."<<endl;return;}

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
    cout << "=============================================" <<endl;
    cout <<centrar("NUMERO DEL CLIENTE: " + to_string(cliente.getIdCliente()),45)<<endl;
    cout << "============================================="<<endl;
    cout << "NOMBRE: " << cliente.getNombre()<<endl;
    cout << "APELLIDO: " << cliente.getApellido()<<endl;
    cout << "D.N.I: " << cliente.getDni()<<endl;
    cout << "TELEFONO: " << cliente.getTelefono()<<endl;
    cout << "CORREO: " << cliente.getEmail()<<endl;
    cout << "FECHA DE NACIMIENTO: " << cliente.getFechaNacimiento().formatoFecha()<<endl;
    cout << "PARTIDO: " << cliente.getPartido()<<endl;
    cout << "LOCALIDAD: " << cliente.getLocalidad()<<endl<<endl;
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


int ClienteManager::posClientePorDNI(string dni) {
  int total = _clientesArchivo.getCantidadRegistros();
  for (int i = 0; i < total; i++) {
    Cliente reg = _clientesArchivo.leer(i);
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
  if (pos != -1 || pos != -2) {
    Cliente registro = _clientesArchivo.leer(pos);
    if (registro.getEliminado()) {
      cout << "EL CLIENTE ESTA ELIMINADO."<<endl;
      return;
    }
    mostrarLista(registro, false);
  }
  else {
    cout << "NO SE ENCONTRO A NINGUN CLIENTE CON ESE ID."<<endl;
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
    cliente.setPartido(partido);
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
    cout << "FECHA DE NACIMIENTO INVALIDAD!.."<<endl;
    mensajeCargaCancelada();
    return false;
  }
  if (resultado==-1) {
    cout << "FECHA DE NACIMIENTO INVALIDAD!.."<<endl;
    mensajeCargaCancelada();
    return false;
  }
  return true;
}

int ClienteManager::hayClientesReg(){
  int cantClientes = _clientesArchivo.getCantidadRegistros();
  if (cantClientes == 0) {
    cout << "NO HAY CLIENTES REGISTRADOS." << endl;
    return 0;
  }
  return cantClientes;
}

int ClienteManager::hayPolizasReg(){
  int cantPolizas = _polizasArchivo.getCantidadRegistros();
  if (cantPolizas == 0) {
    cout << "NO HAY POLIZAS REGISTRADAS." << endl;
    return 0;
  }
  return cantPolizas;
}

int ClienteManager::hayPagosVencReg(){
  int cantVencimientos = _vencimientosArchivo.getCantidadRegistros();
  if (cantVencimientos == 0) {
    cout << "NO HAY PAGOS REGISTRADOS." << endl;
    return 0;
  }
  return cantVencimientos;
}

int ClienteManager::hayPagosReg(){
  int cantPagos = _pagoArchivo.getCantidadRegistros();
  if (cantPagos == 0){
    cout << "NO HAY PAGOS REGISTRADOS." << endl;
    return cantPagos;
  }
  return cantPagos;
}

void ClienteManager::clientesConAtrasoEnLosPagos() {
  int cantClientes = hayClientesReg();
  int cantPolizas = hayPolizasReg();
  int cantPagos = hayPagosVencReg();
  if (cantClientes==0 || cantPolizas==0 || cantPagos==0) return;
  bool titulo = true;
  bool hayImpagos = false;

  for (int i=0; i<cantClientes; i++){
    Cliente cliente = _clientesArchivo.leer(i);
    if (cliente.getEliminado()) continue;

    for (int j=0; j<cantPolizas; j++){
      Poliza poliza = _polizasArchivo.leer(j);
      if (poliza.getEliminado()) continue;

      int idVehiculo = poliza.getIdVehiculo();
      Vehiculo vehiculo = _vehiculosArchivo.leer(_vehiculosArchivo.buscarVehiculo(idVehiculo));
      if (vehiculo.getIdCliente() != cliente.getIdCliente()) continue;

      for (int k=0; k<cantPagos; k++){
        Vencimiento vencimiento = _vencimientosArchivo.leer(k);
        if (!vencimiento.getEliminado() && vencimiento.getIdPoliza() == poliza.getId() && vencimiento.estaVencido() &&
         !vencimiento.getPagado()) continue;
        if (titulo){
          cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
          cout << "|       CLIENTES CON PAGOS ATRASADAS       |" << endl;
          cout << "||||||||||||||||||||||||||||||||||||||||||||" << endl;
          titulo = false;
        }
        hayImpagos = true;
        cout << "CLIENTE: " <<cliente.getApellido()<< ", " <<cliente.getNombre()<< endl;
        cout << "DNI: " <<cliente.getDni()<<endl;
        cout << "NUMERO DE POLIZA: " <<poliza.getId()<<endl;
        cout << "FECHA DE VENCIMIENTO: " <<vencimiento.getVencimiento().formatoFecha()<<endl;
        cout << "MONTO: $" << vencimiento.getMonto()<<endl;
        cout << "--------------------------------------------" <<endl;
      }
    }
  }
  if (!hayImpagos) {
    cout << "NO HAY CLIENTES CON PAGOS ATRASADAS."<<endl;
  }
}

int ClienteManager::buscarClienteParaHistorial() {
    ClienteMenu _clienteMenu;
    int idCliente = _clienteMenu.buscarCliente();
    if (idCliente == -3) return -3;
    if (idCliente == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE2."<<endl;
        return -1;
    }
    return idCliente;
}

bool ClienteManager::esPagoDeCliente(int idxPago, int idCliente) {
  Pago pago = _pagoArchivo.leer(idxPago);
  if (pago.getEliminado()) return false;
  int idVencimiento = pago.getIdVencimiento();
  int posVencimiento = _vencimientosArchivo.buscarID(idVencimiento);
  if (posVencimiento == -1) return false;

  Vencimiento vencimiento = _vencimientosArchivo.leer(posVencimiento);
  int idPoliza = vencimiento.getIdPoliza();
  int posPoliza = _polizasArchivo.buscarID(idPoliza);
  if (posPoliza == -1) return false;

  Poliza poliza = _polizasArchivo.leer(posPoliza);
  int idVehiculo = poliza.getIdVehiculo();
  int posVehiculo = _vehiculosArchivo.buscarVehiculo(idVehiculo);
  if (posVehiculo == -1) return false;

  Vehiculo vehiculo = _vehiculosArchivo.leer(posVehiculo);
  return vehiculo.getIdCliente() == idCliente;
}

int ClienteManager::contarPagosDeCliente(int idCliente){
    int cantPagos = hayPagosVencReg();
    int contador=0;
    for (int i=0; i<cantPagos; i++){
        if (esPagoDeCliente(i, idCliente)) contador++;
    }
    return contador;
}


void ClienteManager::historialPagosPorCliente(){
  int cantClientes = hayClientesReg();
  int cantPagos = hayPagosReg();
  if (cantClientes==0 || cantPagos==0) return;
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||    BUSCAR CLIENTE PARA VER SU HISTORIAL DE PAGOS     ||" << endl;
    cout << "||------------------------------------------------------||" << endl;

    int idCliente = buscarClienteParaHistorial();
    if (idCliente<0) return;

    Cliente cliente = _clientesArchivo.leer(_clientesArchivo.buscarIdCliente(idCliente));
    int contador = contarPagosDeCliente(idCliente);
    if (contador ==0){cout <<"NO SE REGISTRARON PAGOS PARA ESTE CLIENTE."<<endl;return;}

    int *idsPago = new int[ contador];
    string *fechasPago = new string[contador];
    int *idsPoliza = new int[contador];
    int *idsVencimiento = new int[contador];
    int *idsVehiculo = new int[contador];

    int idx=0;
    for (int i=0; i<cantPagos && idx<contador; i++){
      if (!esPagoDeCliente(i, idCliente)) continue;

      Pago pago = _pagoArchivo.leer(i);
      int idVencimiento = pago.getIdVencimiento();
      int posVencimiento = _vencimientosArchivo.buscarID(idVencimiento);
      if (posVencimiento == -1) continue;

      Vencimiento vencimiento = _vencimientosArchivo.leer(posVencimiento);
      int idPoliza = vencimiento.getIdPoliza();
      int posPoliza = _polizasArchivo.buscarID(idPoliza);
      if (posPoliza == -1) continue;
      int idVehiculo = _polizasArchivo.leer(posPoliza).getIdVehiculo();
      idsPago[idx] = pago.getId();
      fechasPago[idx] = pago.getFechaPago().formatoFecha();
      idsPoliza[idx] = idPoliza;
      idsVencimiento[idx] = idVencimiento;
      idsVehiculo[idx] = idVehiculo;
      idx++;
    }
    system("cls");
    cout << "||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      HISTORIAL DE PAGOS DEL CLIENTE      ||" << endl;
    cout << "||------------------------------------------||" << endl;
    cout << "CLIENTE: "<<cliente.getApellido()<<", "<<cliente.getNombre()<<endl;
    cout << "DNI: " <<cliente.getDni()<<endl;
    cout << "----------------------------------------------" << endl;
    for (int i=0; i<contador; i++){
      cout <<i+1<< ") FECHA: " <<fechasPago[i]<< " | POLIZA: " <<idsPoliza[i] <<endl;
    }
    int opcion;
    cout << "INGRESE EL NUMERO DEL HISTORIAL PARA VER FACTURA (0 PARA SALIR): " ;
    cin >> opcion;

    if (opcion<=0 || opcion>contador){cout <<"OPERACION CANCELADA."<<endl;
    } else {
        int sel = opcion-1;
        Poliza poliza = _polizasArchivo.leer(_polizasArchivo.buscarID(idsPoliza[sel]));
        Vehiculo vehiculo = _vehiculosArchivo.leer(_vehiculosArchivo.buscarVehiculo(idsVehiculo[sel]));
        system("cls");
        cout << "|||||||||||||||||||||||||||||||||||||||||||||" <<endl;
        cout << "||             FACTURA DE SEGURO           ||  " <<endl;
        cout << "||-----------------------------------------||" <<endl;
        cout << "FECHA DE EMISION: "<<Fecha().formatoFecha()<<endl;
        cout << "--------------------------------------------" <<endl;
        cout << "CLIENTE: " <<cliente.getApellido()<< ", " <<cliente.getNombre()<<endl;
        cout << "DNI: " << cliente.getDni()<<endl;
        cout << "VEHICULO: " <<vehiculo.getPatente()<<endl;
        cout << "--------------------------------------------" << endl;
        cout << "NUMERO DE POLIZA: " <<poliza.getId()<<endl;
        cout << "TIPO SEGURO: " <<_tiposSegurosArchivo.leer(_tiposSegurosArchivo.buscarID(poliza.getIdTipoSeguro())).getDescripcion()<<endl;
        cout << "FECHA INICIO: " <<poliza.getfechaInicio().formatoFecha()<<endl;
        cout << "VENCIMIENTO: " <<poliza.getfechaFin().formatoFecha()<<endl;
        cout << "PRIMA MENSUAL: $" << poliza.getPrimaMensual()<<endl;
        cout << "SUMA ASEGURADA: " <<poliza.getSumaAsegurada()<<endl;
        cout << "--------------------------------------------"<<endl;
    }
    delete[] idsPago;
    delete[] fechasPago;
    delete[] idsPoliza;
    delete[] idsVencimiento;
    delete[] idsVehiculo;
}


#include <iostream>

#include "../Cliente.h"
#include "../ClientesArchivo.h"
#include "../Fecha.h"
#include "../Pago.h"
#include "../PagoArchivo.h"
#include "../Poliza.h"
#include "../PolizaArchivo.h"
#include "../Siniestro.h"
#include "../SiniestroArchivo.h"
#include "../Vehiculo.h"
#include "../VehiculosArchivo.h"
#include "../Localidad.h"
#include "../LocalidadArchivo.h"
#include "../TiposSiniestrosArchivo.h"
#include "../TipoSiniestro.h"

using namespace std;

void imprimirArchivos() {
  ClientesArchivo archivoClientes;
  VehiculosArchivo archivoVehiculos;
  PagoArchivo archivoPagos;
  SiniestroArchivo archivoSiniestros;
  PolizaArchivo archivoPolizas;
  LocalidadArchivo archivoLocalidad;
  TiposSiniestrosArchivo archivoTiposSiniestros;
  

  int cantidadClientes = archivoClientes.getCantidadRegistros();
  int cantidadVehiculos = archivoVehiculos.cantidadRegistros();
  int cantidadPagos = archivoPagos.getCantidadRegistros();
  int cantidadSiniestros = archivoSiniestros.getCantidadRegistros();
  int cantidadPolizas = archivoPolizas.getCantidadRegistros();
  int cantidadLocalidades = archivoLocalidad.getCantidadRegistros();
  int cantidadTiposSiniestros = archivoTiposSiniestros.getCantidadRegistros();

  Cliente* vClientes = new Cliente[cantidadClientes];
  Vehiculo* vVehiculos = new Vehiculo[cantidadVehiculos];
  Pago* vPagos = new Pago[cantidadPagos];
  Siniestro* vSiniestros = new Siniestro[cantidadSiniestros];
  Poliza* vPolizas = new Poliza[cantidadPolizas];
  Localidad*  vLocalidad = new Localidad[cantidadLocalidades];
  TipoSiniestro* vTiposSiniestros = new TipoSiniestro[cantidadTiposSiniestros];

  archivoClientes.leerTodos(vClientes, cantidadClientes);
  archivoVehiculos.leerTodos(vVehiculos, cantidadVehiculos);
  archivoPagos.leerTodos(vPagos, cantidadPagos);
  archivoSiniestros.leerTodos(vSiniestros, cantidadSiniestros);
  archivoPolizas.leerTodos(vPolizas, cantidadPolizas);
  archivoLocalidad.leerTodos(vLocalidad,cantidadLocalidades);
  archivoTiposSiniestros.leerTodos(vTiposSiniestros,cantidadTiposSiniestros);

  cout << "--------------CLIENTES-------------------" << endl;
  for (int i = 0; i < cantidadClientes; i++) {
    cout << vClientes[i].getIdCliente() << " | " << vClientes[i].getNombre()
         << " | " << vClientes[i].getApellido() << "|" << vClientes[i].getDni()
         << " | " << vClientes[i].getTelefono() << " | "
         << vClientes[i].getEmail() << " | " << vClientes[i].getEliminado()
         << endl;
  }
  cout << "-------------------------------------" << endl
       << "-------------------------------------" << endl;

  cout << "-------------VEHICULOS-------------------" << endl;
  for (int i = 0; i < cantidadVehiculos; i++) {
    cout << vVehiculos[i].getId() << " | " << vVehiculos[i].getIdCliente()
         << " | " << vVehiculos[i].getAnio() << " | "
         << vVehiculos[i].getMarca() << " | " << vVehiculos[i].getModelo()
         << " | " << vVehiculos[i].getPatente() << " | "
         << vVehiculos[i].getCategoria() << " | "
         << vVehiculos[i].getEliminado() << endl;
  }

  cout << "-------------------------------------" << endl
       << "-------------------------------------" << endl;
  cout << "----------------PAGOS-----------------" << endl;
  for (int i = 0; i < cantidadPagos; i++) {
    cout << vPagos[i].getId() << " | " << vPagos[i].getIdPoliza() << " | "
         << vPagos[i].getFechaPago().formatoFecha() << " | "
         << vPagos[i].getMonto() << " | " << vPagos[i].getMetodoDePago()
         << " | " << vPagos[i].getEstado() << " | " << vPagos[i].getEliminado()
         << endl;
  }

  cout << "-------------------------------------" << endl
       << "-------------------------------------" << endl;
  cout << "--------------SINIESTROS--------------" << endl;
  for (int i = 0; i < cantidadSiniestros; i++) {
    cout << vSiniestros[i].getId() << " | " << vSiniestros[i].getIdPoliza()
         << " | " << vSiniestros[i].getFechaSiniestro().formatoFecha() << " | "
         << vSiniestros[i].getIdTipoSiniestro() << " | "
         << vSiniestros[i].getCostoEstimado() << " | "
         << vSiniestros[i].getEstado() << " | " << vSiniestros[i].getEliminado()
         << endl;
  }

  cout << "-------------------------------------" << endl
       << "-------------------------------------" << endl;
  cout << "---------------POLIZAS----------------" << endl;
  for (int i = 0; i < cantidadPolizas; i++) {
    cout << vPolizas[i].getId() << " | " << vPolizas[i].getIdVehiculo() << " | "
         << vPolizas[i].getfechaInicio().formatoFecha() << " | "
         << vPolizas[i].getfechaFin().formatoFecha() << " | "
         << vPolizas[i].getPrimaMensual() << " | "
         << vPolizas[i].getIdTipoSeguro() << " | " << vPolizas[i].getVigente()
         << " | " << vPolizas[i].getEliminado() << endl;
  }

  cout << "-------------------------------------" << endl
       << "-------------------------------------" << endl;

  cout << "-------------LOCALIDADES--------------" << endl;
  for (int i = 0; i < cantidadLocalidades; i++) {
    cout << vLocalidad[i].getCodigoPostal() << " | " << vLocalidad[i].getLocalidad() << " | "
         << vLocalidad[i].getPartido()<< endl;
  }
  cout << "-------------------------------------" << endl
       << "-------------------------------------" << endl;

  cout << "----------TIPOS DE SINIESTROS---------" << endl;
  for (int i = 0; i < cantidadTiposSiniestros; i++){
     cout << vTiposSiniestros[i].getId() << " | " << vTiposSiniestros[i].getDescripcion() << " | " << vTiposSiniestros[i].getEliminado() << endl;
  }

  delete[] vClientes;
  delete[] vVehiculos;
  delete[] vPagos;
  delete[] vSiniestros;
  delete[] vPolizas;
  delete[] vLocalidad;
  delete[] vTiposSiniestros;
}

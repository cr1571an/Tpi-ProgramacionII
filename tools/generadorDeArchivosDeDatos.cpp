#include "generadorDeArchivosDeDatos.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "../Clientes.h"
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
#include "../utils.h"

int generarClientes() {
  std::ifstream archivo("../inputData/clientes.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return 1;
  } else {
    cout << "Archivo abierto correctamente!" << endl;
  }

  ClientesArchivo repositorioClientes;

  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    int id = repositorioClientes.getID();
    stringstream ss(linea);
    string campo;

    Cliente c{};

    c.setIdCliente(id);

    getline(ss, campo, ',');
    c.setNombre(campo);

    getline(ss, campo, ',');
    c.setApellido(campo);

    getline(ss, campo, ',');
    c.setDni(campo);

    getline(ss, campo, ',');
    c.setTelefono(campo);

    getline(ss, campo, ',');
    c.setEmail(campo);

    getline(ss, campo, ',');
    c.setEliminado(campo == "true" ? true : false);

    if (repositorioClientes.guardar(c)) {
      cout << "Cliente agregado: " << c.getNombre() << " " << c.getApellido()
           << endl;
    } else {
      cout << "Error al agregar cliente: " << c.getNombre() << " "
           << c.getApellido() << endl;
    }
  }

  archivo.close();

  return 0;
}

int generarVehiculos() {
  std::ifstream archivo("../inputData/vehiculos.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return 1;
  } else {
    cout << "Archivo abierto correctamente!" << endl;
  }

  VehiculosArchivo repositorioVehiculos;

  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    int id = repositorioVehiculos.getID();
    stringstream ss(linea);
    string campo;

    Vehiculo v{};

    v.setId(id);

    getline(ss, campo, ',');
    int idCliente = atoi(campo.c_str());
    v.setIdCliente(idCliente);

    getline(ss, campo, ',');
    v.setAnio(campo);

    getline(ss, campo, ',');
    v.setMarca(campo);

    getline(ss, campo, ',');
    v.setModelo(campo);

    getline(ss, campo, ',');
    v.setPatente(campo);

    getline(ss, campo, ',');
    v.setCategoria(campo);

    getline(ss, campo, ',');
    v.setEliminado(campo == "true" ? true : false);

    if (repositorioVehiculos.guardar(v)) {
      cout << "Vehiculo agregado: " << v.getMarca() << " " << v.getModelo()
           << endl;
    } else {
      cout << "Error al agregar cliente: " << v.getMarca() << " "
           << v.getModelo() << endl;
    }
  }

  archivo.close();

  return 0;
}

int generarPolizas() {
  std::ifstream archivo("../inputData/polizas.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return 1;
  } else {
    cout << "Archivo abierto correctamente!" << endl;
  }

  PolizaArchivo repositorioPolizas;

  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string campo;

    Poliza p{};

    getline(ss, campo, ',');
    int id = atoi(campo.c_str());
    p.setId(id);

    getline(ss, campo, ',');
    int idVehiculo = atoi(campo.c_str());
    p.setIdVehiculo(idVehiculo);

    getline(ss, campo, ',');
    Fecha fechaInicio = procesarFecha(campo);
    p.setFechaInicio(fechaInicio);

    getline(ss, campo, ',');
    Fecha fechaFin = procesarFecha(campo);
    p.setFechaFin(fechaFin);

    getline(ss, campo, ',');
    float campoFloat = atof(campo.c_str());
    p.setPrimaMensual(campoFloat);

    getline(ss, campo, ',');
    p.setTipoSeguro(campo);

    getline(ss, campo, ',');
    p.setVigente(campo == "true" ? true : false);

    getline(ss, campo, ',');
    p.setEliminado(campo == "true" ? true : false);

    if (repositorioPolizas.guardar(p)) {
      cout << "Poliza agregada: " << p.getId() << endl;
    } else {
      cout << "Error al agregar poliza: " << p.getId() << endl;
    }
  }

  archivo.close();

  return 0;
}

int generarPagos() {
  std::ifstream archivo("../inputData/pagos.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return 1;
  } else {
    cout << "Archivo abierto correctamente!" << endl;
  }

  PagoArchivo repositorioPagos;
  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string campo;

    Pago p{};

    getline(ss, campo, ',');
    int id = atoi(campo.c_str());
    p.setId(id);

    getline(ss, campo, ',');
    int idPoliza = atoi(campo.c_str());
    p.setIdPoliza(idPoliza);

    getline(ss, campo, ',');
    Fecha fechaPago = procesarFecha(campo);
    p.setFechaPago(fechaPago);

    getline(ss, campo, ',');
    float campoFloat = atof(campo.c_str());
    p.setMonto(campoFloat);

    getline(ss, campo, ',');
    p.setMetodoDePago(campo);

    getline(ss, campo, ',');
    p.setEstado(campo == "true" ? true : false);

    getline(ss, campo, ',');
    p.setEliminado(campo == "true" ? true : false);

    if (repositorioPagos.guardar(p)) {
      cout << "Pago agregado: " << p.getId() << endl;
    } else {
      cout << "Error al agregar pago: " << p.getId() << endl;
    }
  }

  archivo.close();
  return 0;
}

int generarSiniestros() {
  std::ifstream archivo("../inputData/siniestros.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return 1;
  } else {
    cout << "Archivo abierto correctamente!" << endl;
  }

  SiniestroArchivo repositorioSiniestros;

  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string campo;

    Siniestro s{};

    getline(ss, campo, ',');
    int id = atoi(campo.c_str());
    s.setId(id);

    getline(ss, campo, ',');
    int idPoliza = atoi(campo.c_str());
    s.setIdPoliza(idPoliza);

    getline(ss, campo, ',');
    Fecha fechaSiniestro = procesarFecha(campo);
    s.setFechaSiniestro(fechaSiniestro);

    getline(ss, campo, ',');
    s.setTipoSiniestro(campo);

    getline(ss, campo, ',');
    float campoFloat = atof(campo.c_str());
    s.setCostoEstimado(campoFloat);

    getline(ss, campo, ',');
    s.setEstado(campo == "true" ? true : false);

    getline(ss, campo, ',');
    s.setEliminado(campo == "true" ? true : false);

    if (repositorioSiniestros.guardar(s)) {
      cout << "Siniestro agregado: " << s.getId() << endl;
    } else {
      cout << "Error al agregar siniestro: " << s.getId() << endl;
    }
  }

  archivo.close();

  return 0;
}
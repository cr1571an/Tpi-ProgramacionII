#include <fstream>
#include <iostream>
#include <sstream>
#include "generadorDeArchivosDeDatos.h"
using namespace std;

#include "../Clientes.h"
#include "../ClientesArchivo.h"
#include "../Vehiculo.h"
#include "../VehiculosArchivo.h"

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

void generarPolizas() {}

void generarPagos() {}

void generarSiniestros() {}
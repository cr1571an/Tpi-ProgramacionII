#include "generadorDeArchivosDeDatos.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

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
#include "../utils.h"
#include "../TipoSeguro.h"
#include "../TiposSegurosArchivo.h"
#include "../TiposSiniestrosArchivo.h"
#include "../TipoSiniestro.h"
#include "../PolizaManager.h"

int generarClientes() {
  std::ifstream archivo("inputData/clientes.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo clientes.csv." << endl;
    return 1;
  } else {
    cout << "Archivo clientes.csv abierto correctamente!" << endl;
  }

  ClientesArchivo repositorioClientes;

  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    int id = repositorioClientes.getIdClienteUltimo();
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
    c.setPartido(campo);

    getline(ss, campo, ',');
    c.setLocalidad(campo);

    getline(ss, campo, ',');
    (campo == "true") ? c.eliminar() : c.recuperar();

    getline(ss, campo, ',');
    Fecha fechaNacimiento = procesarFecha(campo);
    c.setFechaNacimiento(fechaNacimiento);

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
  std::ifstream archivo("inputData/vehiculos.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo vehiculos.csv." << endl;
    return 1;
  } else {
    cout << "Archivo vehiculos.csv abierto correctamente!" << endl;
  }

  VehiculosArchivo repositorioVehiculos;

  string linea;
  getline(archivo, linea);  // salteamos encabezado

  while (getline(archivo, linea)) {
    int id = repositorioVehiculos.getIdVehiculoUltimo();
    stringstream ss(linea);
    string campo;

    Vehiculo v{};

    v.setIdVehiculo(id);

    getline(ss, campo, ',');
    int idCliente = atoi(campo.c_str());
    v.setIdCliente(idCliente);

    getline(ss, campo, ',');
    int anio = atoi(campo.c_str());
    v.setAnio(anio);

    getline(ss, campo, ',');
    v.setMarca(campo);

    getline(ss, campo, ',');
    v.setModelo(campo);

    getline(ss, campo, ',');
    v.setPatente(campo);

    getline(ss, campo, ',');
    v.setCategoria(campo);

    getline(ss, campo, ',');
    v.setNumMotor(campo);

    getline(ss, campo, ',');
    v.setNumChasis(campo);

    getline(ss, campo, ',');
    v.setUso(campo);

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
  std::ifstream archivo("inputData/polizas.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo polizas.csv." << endl;
    return 1;
  } else {
    cout << "Archivo polizas.csv abierto correctamente!" << endl;
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
    int sumaAsegurada = atoi(campo.c_str());
    p.setSumaAsegurada(sumaAsegurada);

    getline(ss, campo, ',');
    int idTipoSeguro = atoi(campo.c_str());
    p.setIdTipoSeguro(idTipoSeguro);

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

/* int generarSiniestros() {
  std::ifstream archivo("inputData/siniestros.csv");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo siniestros.csv." << endl;
    return 1;
  } else {
    cout << "Archivo siniestros.csv abierto correctamente!" << endl;
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
    int idTipoSiniestro = atoi(campo.c_str());
    s.setIdTipoSiniestro(idTipoSiniestro);

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
} */

bool generarTiposSeguros(){
    std::ifstream archivo("inputData/tiposSeguros.csv");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo tiposSeguros.csv." << endl;
        return false;
    }
    else {
        cout << "Archivo tiposSeguros.csv abierto correctamente!" << endl;
    }

    TiposSegurosArchivo repositorioTiposSeguros;

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;

        TipoSeguro ts{};

        getline(ss, campo, ',');
        int id = atoi(campo.c_str());
        ts.setId(id);

        getline(ss, campo, ',');
        ts.setDescripcion(campo);

        getline(ss, campo, ',');
        ts.setEliminado(campo == "true" ? true : false);

        if (repositorioTiposSeguros.guardar(ts)) {
            cout << "Tipo de seguro agregado: " << ts.getDescripcion() << endl;
        }
        else {
            cout << "Error al agregar tipo de seguro: " << ts.getDescripcion() << endl;
        }
    }

    archivo.close();

    return true;
}

bool generarTiposSiniestros(){
    std::ifstream archivo("inputData/tiposSiniestros.csv");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo tiposSiniestros.csv." << endl;
        return false;
    }
    else {
        cout << "Archivo tiposSiniestros.csv abierto correctamente!" << endl;
    }

    TiposSiniestrosArchivo repositorioTiposSiniestros;

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;

        TipoSiniestro ts{};

        getline(ss, campo, ',');
        int id = atoi(campo.c_str());
        ts.setId(id);

        getline(ss, campo, ',');
        ts.setDescripcion(campo);

        getline(ss, campo, ',');
        ts.setEliminado(campo == "true" ? true : false);

        if (repositorioTiposSiniestros.guardar(ts)) {
            cout << "Tipo de siniestro agregado: " << ts.getDescripcion() << endl;
        }
        else {
            cout << "Error al agregar tipo de siniestro: " << ts.getDescripcion() << endl;
        }
    }    

    archivo.close();

    return true;
}

// generar Vencimientos es un metodo privado de PolizaManager.
// void generarVencimientos(){
//   PolizaArchivo repositorioPolizas;
//   int cantidadPolizas = repositorioPolizas.getCantidadRegistros();

//   PolizaManager polizaManager;

//   Poliza* polizas= new Poliza[cantidadPolizas]{};
//   repositorioPolizas.leerTodos(polizas, cantidadPolizas);

//   for (int i=0; i< cantidadPolizas; i++){
//     polizaManager.generarVencimientos(polizas[i],3);    
//   }

//   delete[] polizas;
// }
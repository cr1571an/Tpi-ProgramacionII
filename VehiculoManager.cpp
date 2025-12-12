#include <iostream>
#include <string>
#include "VehiculoManager.h"
#include "utils.h"
#include "VehiculoMenu.h"
using namespace std;

VehiculoManager::VehiculoManager()
    : _vehiculosArchivo() {}

void VehiculoManager::cargar(int iDCliente) {
    system("cls");
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout <<"||            ACLARACION!          ||"<<endl;
    cout <<"||  SI INGRESAS '0' EN CUALQUIER   ||"<<endl;
    cout <<"||  CAMPO, LA CARGA SE CANCELARA   ||"<<endl;
    cout <<"||  AUTOMATICAMENTE.               ||"<<endl;
    cout <<"|||||||||||||||||||||||||||||||||||||" << endl;
    system("pause");
    system("cls");
    VehiculoMenu menu;
    int id = _vehiculosArchivo.getIdVehiculoUltimo();
    Cliente cliente = _clientesArchivo.leer(_clientesArchivo.buscarIdCliente(iDCliente));
    string marca, modelo, patente, chasis, numeroMotor;
    int anio;
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout <<"||      CARGAR NUEVO VEHICULO      ||"<<endl;
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "ID: " << id << endl;
    cout << "CLIENTE: " << cliente.getNombre() << " " << cliente.getApellido() << endl;
    cout << "DNI: " << cliente.getDni() << endl;
    cout << "INGRESE MARCA: ";   marca = cargarCadena();if (cortarSiCero(marca)) {mensajeCargaCancelada();return;};
    cout << "INGRESE MODELO: ";  modelo = cargarCadena();if (cortarSiCero(modelo)) {mensajeCargaCancelada();return;};
    cout << "INGRESE PATENTE: "; patente = cargarCadena();if (cortarSiCero(patente)) {mensajeCargaCancelada();return;};
    if (buscarIdPorPatente(patente)!=-1) {cout << "ESTA PATENTE YA ESTA REGISTRADA. NO SE PUEDE VOLVER A REGISTRAR."<<endl;mensajeCargaCancelada();return;};
    cout << "INGRESE ANIO: "; cin >> anio; cin.ignore(); if (anio == 0) {mensajeCargaCancelada();return;};
    if (anio < 1990 || anio > 2025) {cout << "SOLO SE ACEPTAN VEHICULOS DEL ANIO ENTRE 1990 Y 2025." << endl;mensajeCargaCancelada();return;};
    cout << "INGRESE NUMERO DEL CHASIS: "; chasis = cargarCadena();if (cortarSiCero(chasis)){mensajeCargaCancelada();return;};
    if (!buscarNumChasis(chasis)) {cout << "ESTE NUMERO DE CHASIS YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<<endl;mensajeCargaCancelada();return;};
    cout << "INGRESE NUMERO DEL MOTOR: "; numeroMotor = cargarCadena();if (cortarSiCero(numeroMotor)) return;
    if (!buscarNumMotor(numeroMotor)) {cout << "ESTE NUMERO DE MOTOR YA ESTA REGISTRADO. NO SE PUEDE VOLVER A REGISTRAR."<<endl;mensajeCargaCancelada();return;};

    mostrarPantalla(cliente, id, marca, modelo, patente, anio, chasis, numeroMotor);
    string uso = menu.mostrarUso();
    if (uso == "") return;

    mostrarPantalla(cliente, id, marca, modelo, patente, anio, chasis, numeroMotor, uso);

    string categoria = menu.mostrarCategoria();
    if (categoria == "") return;

    mostrarPantalla(cliente, id, marca, modelo, patente, anio, chasis, numeroMotor, uso, categoria);

    Vehiculo v(id, iDCliente, anio, marca, modelo, patente,categoria, false, chasis, numeroMotor, uso);

    if (_vehiculosArchivo.guardar(v)) {
        cout << "VEHICULO CARGADO CORRECTAMENTE." << endl;
    }
    else {
        cout << "NO SE PUDO CARGAR EL VEHICULO." << endl;
    }
}



void VehiculoManager::mostrar() {
    cout << "============================================" << endl;
    cout << "          LISTADO DE LOS VEHICULOS           " << endl;
    cout << "============================================" << endl;
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    if (cantidad == 0) {cout << "NO HAY VEHICULOS REGISTRADOS."<<endl;return;}

    for (int i = 0; i < cantidad; i++) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(i);
        if (!vehiculo.getEliminado()) {
            mostrarLista(vehiculo);
        }
    }
}

void VehiculoManager::eliminar(int idVehiculo) {
    if (_vehiculosArchivo.eliminarVehiculo(idVehiculo)) {
        cout << "VEHICULO ELIMINADO CORRECTAMENTE." << endl;
    } else {
        cout << "NO SE PUDO ELIMINAR EL VEHICULO." << endl;
    }
}

bool VehiculoManager::estadoCliente(int idCliente) {
    int pos = _clientesArchivo.buscarIdCliente(idCliente);
    if (pos != -1) {
        return _clientesArchivo.leer(pos).getEliminado();
    }
    return false;
}


void VehiculoManager::mostrarLista(Vehiculo vehiculo) {
    int pos = _clientesArchivo.buscarIdCliente(vehiculo.getIdCliente());
    Cliente cliente = _clientesArchivo.leer(pos);
    if (!cliente.getEliminado()) {
        cout << endl;
        cout << "ID DEL VEHICULO: " << vehiculo.getIdVehiculo() << endl;
        cout << "CLIENTE: " << cliente.getNombre() + " " + cliente.getApellido()<<endl;
        cout << "D.N.I: "<< cliente.getDni()<<endl;
        cout << "MODELO: " << vehiculo.getModelo() << endl;
        cout << "MARCA: " << vehiculo.getMarca() << endl;
        cout << "PATENTE: " << vehiculo.getPatente() << endl;
        cout << "USO: " << vehiculo.getUso() << endl;
        cout << "CATEGORIA: " << vehiculo.getCategoria() << endl;
        cout << "NUMERO DE CHASIS: " << vehiculo.getNumChasis() << endl;
        cout << "NUMERO DEL MOTOR: " << vehiculo.getNumMotor() << endl;
        cout << "ANIO: " << vehiculo.getAnio() << endl;
        cout << "ESTADO: " << (vehiculo.getEliminado() ? "DADO DE BAJA" : "ACTIVO") << endl;
        cout << endl;
    }
}

int VehiculoManager::mostrarYContarVehiculosDeCliente(int idClienteBuscado) {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        Vehiculo v = _vehiculosArchivo.leer(i);
        if ( v.getIdCliente() == idClienteBuscado) {
            mostrarLista(v);
            contador++;
        }
    }
    return contador;
}

int VehiculoManager::posVehiculoPorClienteId(int idCliente) {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    Vehiculo v;
    for (int i = 0; i < cantidad; i++) {
        v = _vehiculosArchivo.leer(i);
        if (!v.getEliminado() && v.getIdCliente() == idCliente) {
            return i;
        }
    }
    return -1;
}

int VehiculoManager::buscarIdPorPatente(string patente) {
    int cantidad = _vehiculosArchivo.cantidadRegistros();
    Vehiculo v;
    for (int i = 0; i < cantidad; i++) {
        v = _vehiculosArchivo.leer(i);
        if (v.getPatente() == patente) {
            return v.getIdVehiculo();
        }
    }
    return -1;
}

bool VehiculoManager::buscarNumChasis(string numChasis) {
    int cant = _vehiculosArchivo.cantidadRegistros();
    Vehiculo *vehiculos = new Vehiculo[cant];
    _vehiculosArchivo.leerTodos(vehiculos, cant);
    for (int i = 0; i < cant; i++) {
        if (!vehiculos[i].getEliminado() && vehiculos[i].getNumChasis() == numChasis) {
            delete[] vehiculos;
            return false;
        }
    }
    delete[] vehiculos;
    return true;
}

bool VehiculoManager::buscarNumMotor(string numMotor) {
    int cant = _vehiculosArchivo.cantidadRegistros();
    Vehiculo *vehiculos = new Vehiculo[cant];
    _vehiculosArchivo.leerTodos(vehiculos, cant);
    for (int i = 0; i < cant; i++) {
        if (!vehiculos[i].getEliminado() && vehiculos[i].getNumMotor() == numMotor) {
            delete[] vehiculos;
            return false;
        }
    }
    delete[] vehiculos;
    return true;
}

void VehiculoManager::modificarPatente(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE LA NUEVA PATENTE: ";
        string nuevaPatente;
        cin >> nuevaPatente;
        if (buscarIdPorPatente(nuevaPatente) != -1) {
            cout << "YA EXISTE UN VEHICULO CON ESA PATENTE." << endl;
            return;
        }
        vehiculo.setPatente(nuevaPatente);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "PATENTE MODIFICADA CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR LA PATENTE." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarUso(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        VehiculoMenu menu;
        string nuevoUso = menu.mostrarUso();
        vehiculo.setUso(nuevoUso);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "USO MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL USO." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarCategoria(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        VehiculoMenu menu;
        string nuevaCategoria = menu.mostrarCategoria();
        vehiculo.setCategoria(nuevaCategoria);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "CATEGORIA MODIFICADA CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR LA CATEGORIA." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarNumChasis(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE EL NUEVO NUMERO DE CHASIS: ";
        string nuevoChasis;
        cin >> nuevoChasis;
        if (!buscarNumChasis(nuevoChasis)) {
        cout << "YA EXISTE UN VEHICULO CON ESE NUMERO DE CHASIS." << endl;
            return;
        }
        vehiculo.setNumChasis(nuevoChasis);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "NUMERO DE CHASIS MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL NUMERO DE CHASIS." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarNumMotor(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE EL NUEVO NUMERO DE MOTOR: ";
        string nuevoMotor;
        cin >> nuevoMotor;
        if (!buscarNumMotor(nuevoMotor)) {
        cout << "YA EXISTE UN VEHICULO CON ESE NUMERO DE MOTOR." << endl;
            return;
        }
        vehiculo.setNumMotor(nuevoMotor);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "NUMERO DE MOTOR MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL NUMERO DE MOTOR." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::modificarAnio(int idVehiculo) {
    int pos = _vehiculosArchivo.buscarVehiculo(idVehiculo);
    int nuevoAnio;
    if (pos != -1) {
        Vehiculo vehiculo = _vehiculosArchivo.leer(pos);
        cout << "INGRESE EL NUEVO ANIO: ";
        cin >> nuevoAnio;
        if (nuevoAnio < 1990 || nuevoAnio > 2025) { cout << "ANIO INCORRECTO." << endl; return;}
        vehiculo.setAnio(nuevoAnio);
        if (_vehiculosArchivo.actualizarVehiculo(pos, vehiculo)) {
            cout << "ANIO MODIFICADO CORRECTAMENTE." << endl;
        } else {
            cout << "NO SE PUDO MODIFICAR EL ANIO." << endl;
        }
    } else {
        cout << "VEHICULO NO ENCONTRADO." << endl;
    }
}

void VehiculoManager::mostrarPantalla(Cliente cli, int id, string marca, string modelo, string patente, int anio, string chasis, string motor, string uso, string categoria){
    system("cls");
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout <<"||      CARGAR NUEVO VEHICULO      ||"<<endl;
    cout <<"|||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "ID: " << id << endl;
    cout << "CLIENTE: " << cli.getNombre() << " " << cli.getApellido() << endl;
    cout << "DNI: " << cli.getDni() << endl;
    cout << "INGRESE MARCA: " << marca << endl;
    cout << "INGRESE MODELO: " << modelo << endl;
    cout << "INGRESE PATENTE: " << patente << endl;
    cout << "INGRESE ANIO: " << anio << endl;
    cout << "INGRESE NUMERO DEL CHASIS: " << chasis << endl;
    cout << "INGRESE NUMERO DEL MOTOR: " << motor << endl;
    if (uso != "") cout << "USO: " << uso << endl;
    if (categoria != "") cout << "CATEGORIA: " << categoria << endl;
}

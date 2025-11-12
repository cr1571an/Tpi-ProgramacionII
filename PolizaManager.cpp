#include "PolizaManager.h"
#include "PolizaArchivo.h"
#include "utils.h"
#include "Cliente.h"
#include <iostream>
using namespace std;

PolizaManager::PolizaManager()
    : _archivo(), _vehiculoManager(), _archivoCliente(),_archivoVehiculos() {
}

void PolizaManager::mostrar() {
    int cantidad = _archivo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Poliza p = _archivo.leer(i);
        if (!p.getEliminado()) {
            Vehiculo vehiculo = _archivoVehiculos.leer(p.getIdVehiculo());
            Cliente cliente = _archivoCliente.leer(vehiculo.getIdCliente());
            cout << "ID: " << p.getId() << ", Cliente Apellido: " << cliente.getApellido() << " " << cliente.getNombre()
                 << ", Vehiculo: " << p.getIdVehiculo()
                 << ", Seguro: " << p.getTipoSeguro()
                 << ", Fecha Inicio: " << p.getfechaInicio().formatoFecha()
                 << ", Fecha Fin: " << p.getfechaFin().formatoFecha()
                 << ", Vigente: " << (p.getVigente() ? "Sí" : "No") << endl;
        }
    }
}

void PolizaManager::cargar() {
    string patente;
    cout << "Ingrese patente del vehiculo: ";
    patente = cargarCadena();
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        int id = _archivo.getNuevoID();
        Fecha inicio, fin;
        fin.sumarDias(90);
        float prima;
        string tipo;
        cout << "Tipo de seguro: "; tipo = cargarCadena();
        cout << "Prima mensual: "; cin >> prima;

        Poliza p(id, idVehiculo, inicio, fin, prima, tipo, true, false);
        if (_archivo.guardar(p)) cout << "Poliza guardada." << endl;
        else cout << "Error al guardar." << endl;
    } else {
        cout << "No se encontraron vehiculos con esa patente." << endl;
    }
}


void PolizaManager::eliminar() {
    int idPoliza;
    cout << "Ingrese un numero de poliza: ";
    cin >> idPoliza;
    if (idPoliza>= 0){
        int pos = _archivo.buscarID(idPoliza);
        if (pos != -1)
            cout<< (_archivo.eliminar(pos) ? "Poliza eliminada." : "No se encontró la poliza.") << endl;
        else
            cout<<"El ID ingresado no se encontro.";
    }
    else{
        cout<<"El ID ingresado es invalido.";
    }
}

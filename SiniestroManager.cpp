#include "SiniestroManager.h"
#include <iostream>
using namespace std;
#include "utils.h"

SiniestroManager::SiniestroManager()
    : _archivo(), _polizaArchivo() {
}

void SiniestroManager::mostrar() {
    int cantidad = _archivo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Siniestro s = _archivo.leer(i);
        if (!s.getEliminado()) {
            cout << "ID: " << s.getId() << ", Poliza: " << s.getIdPoliza()
                 << ", Tipo: " << s.getTipoSiniestro()
                 << ", Costo: $" << s.getCostoEstimado()
                 << ", Fecha Siniestro: " << s.getFechaSiniestro().formatoFecha()
                 << ", Vigente: " << (s.getEstado() ? "Sí" : "No")
                 << endl;
        }
    }
}


void SiniestroManager::cargar() {
    int idPoliza;
    cout << "ID de la poliza asociada: "; cin >> idPoliza;

    int id = _archivo.getNuevoID();
    int dia, mes, anio;
    cout << "Ingrese el dia de la fecha del siniestro: ";
    cin >> dia;
    cout << "Ingrese el mes de la fecha del siniestro: ";
    cin >> mes;
    cout << "Ingrese el anio de la fecha del siniestro: ";
    cin >> anio;
    Fecha fecha(dia, mes, anio);
    string tipo;
    float costo;
    cout << "Tipo de siniestro: "; tipo = cargarCadena();
    cout << "Costo estimado: "; cin >> costo;

    Siniestro s(id, idPoliza, fecha, tipo, costo, true, false);
    if (_archivo.guardar(s)) cout << "Siniestro registrado." << endl;
    else cout << "Error al guardar." << endl;
}


void SiniestroManager::eliminar() {
    int id;
    cout << "ID del siniestro: "; cin >> id;
    if (id >= 0){
        int pos = _archivo.buscarID(id);
        if (pos != -1) {
            cout << (_archivo.eliminar(pos) ? "Siniestro eliminado." : "No se encontró el siniestro.") << endl;
        } else {
            cout << "No se encontró el siniestro." << endl;
        }
    }
    else{
        cout<<"El ID ingresado es invalido.";
    }
}

void SiniestroManager::recuperar() {
    int idSiniestro;
    cout << "Ingrese un numero de siniestro: ";
    cin >> idSiniestro;
    if (idSiniestro>= 0){
        int pos = _archivo.buscarID(idSiniestro);
        if (pos != -1 ){
            Siniestro siniestro = _archivo.leer(pos);
            siniestro.setEliminado(false);            
            cout<< (_archivo.guardar(siniestro, pos) ? "Siniestro recuperado." : "No se pudo recuperar el siniestro.") << endl;          
        }
        else
            cout<<"El ID ingresado no se encontro.";
    }
    else{
        cout<<"El ID ingresado no es invalido.";
    }
}

void SiniestroManager::buscarPorIdPoliza() {
    int idPoliza;
    cout << "ID de la poliza: "; cin >> idPoliza;

    int cantidad = _archivo.getCantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidad; i++) {
        Siniestro s = _archivo.leer(i);
        if (s.getIdPoliza() == idPoliza && !s.getEliminado()) {
            cout << "ID: " << s.getId() << ", Tipo: " << s.getTipoSiniestro()
                 << ", Costo: $" << s.getCostoEstimado()
                 << ", Fecha Siniestro: " << s.getFechaSiniestro().formatoFecha()
                 << ", Vigente: " << (s.getEstado() ? "Sí" : "No")
                 << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron siniestros para la poliza indicada." << endl;
    }
}

void SiniestroManager::modificarFechaSiniestro() {
    int id;
    cout << "ID del siniestro a modificar: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        int dia, mes, anio;
        cout << "Nueva fecha - Dia: "; cin >> dia;
        cout << "Nueva fecha - Mes: "; cin >> mes;
        cout << "Nueva fecha - Anio: "; cin >> anio;
        Fecha nuevaFecha(dia, mes, anio);
        s.setFechaSiniestro(nuevaFecha);
        cout << (_archivo.guardar(s, pos) ? "Fecha modificada." : "Error al modificar la fecha.") << endl;
    } else {
        cout << "No se encontró el siniestro." << endl;
    }
}

void SiniestroManager::modificarTipoSiniestro() {
    int id;
    cout << "ID del siniestro a modificar: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        string nuevoTipo;
        cout << "Nuevo tipo de siniestro: "; nuevoTipo = cargarCadena();
        s.setTipoSiniestro(nuevoTipo);
        cout << (_archivo.guardar(s, pos) ? "Tipo de siniestro modificado." : "Error al modificar el tipo de siniestro.") << endl;
    } else {
        cout << "No se encontró el siniestro." << endl;
    }
}

void SiniestroManager::modificarCostoEstimado() {
    int id;
    cout << "ID del siniestro a modificar: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        float nuevoCosto;
        cout << "Nuevo costo estimado: "; cin >> nuevoCosto;
        s.setCostoEstimado(nuevoCosto);
        cout << (_archivo.guardar(s, pos) ? "Costo estimado modificado." : "Error al modificar el costo estimado.") << endl;
    } else {
        cout << "No se encontró el siniestro." << endl;
    }
}

void SiniestroManager::modificarEstadoSiniestro() {
    int id;
    cout << "ID del siniestro a modificar: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        bool nuevoEstado;
        cout << "Nuevo estado (1 para vigente, 0 para no vigente): "; cin >> nuevoEstado;
        s.setEstado(nuevoEstado);
        cout << (_archivo.guardar(s, pos) ? "Estado modificado." : "Error al modificar el estado.") << endl;
    } else {
        cout << "No se encontró el siniestro." << endl;
    }
}
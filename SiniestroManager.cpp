#include "SiniestroManager.h"
#include <iostream>
using namespace std;
#include "utils.h"

SiniestroManager::SiniestroManager()
    : _archivo(), _polizaArchivo() {
}

void SiniestroManager::mostrar() {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad != 0) {
        for (int i = 0; i < cantidad; i++) {
            Siniestro s = _archivo.leer(i);
            if (!s.getEliminado()) 
                mostrarSiniestro(s);
        }
    }
    else {
        cout << "No hay siniestros para mostrar." << endl;
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
    int idTipo;    
    float costo;
    
    cout << "Id del Tipo de siniestro: "; cin >> idTipo;
    if (_tiposSiniestrosArchivo.buscarID(idTipo) == -1) {
        cout << "La poliza asociada no existe. Operacion cancelada." << endl;
        return;
    }

    cout << "Costo estimado: "; cin >> costo;
    if (costo < 0) {
        cout << "El costo estimado no puede ser negativo. Operacion cancelada." << endl;
        return;
    }

    Siniestro s(id, idPoliza, fecha, idTipo, costo, true, false);
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
            mostrarSiniestro(s);
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
        int nuevoTipo;
        cout << "Nuevo tipo de siniestro: "; 
        cin >> nuevoTipo;
        int posTipo = _tiposSiniestrosArchivo.buscarID(nuevoTipo);
        if (posTipo == -1) {
            cout << "Tipo de siniestro no encontrado. Modificación cancelada." << endl;
            return;
        }
        s.setIdTipoSiniestro(nuevoTipo);
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

void SiniestroManager::mostrarSiniestro(Siniestro siniestro) {
    int posicion = _tiposSiniestrosArchivo.buscarID(siniestro.getIdTipoSiniestro());
    TipoSiniestro tipoSiniestro = _tiposSiniestrosArchivo.leer(posicion); 
    cout << "ID: " << siniestro.getId() << ", Poliza: " << siniestro.getIdPoliza()
         << ", Tipo: " << tipoSiniestro.getDescripcion()
         << ", Costo: $" << siniestro.getCostoEstimado()
         << ", Fecha Siniestro: " << siniestro.getFechaSiniestro().formatoFecha()
         << ", Aprobado: " << (siniestro.getEstado() ? "Sí" : "No")
         << endl;
}

void SiniestroManager::reporteSiniestrosPorTipo() {
    int cantidadTipos = _tiposSiniestrosArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidadTipos; i++) {
        TipoSiniestro tipo = _tiposSiniestrosArchivo.leer(i);
        if (!tipo.getEliminado()) {
            cout << "Tipo de Siniestro: " << tipo.getDescripcion() << endl;
            int cantidadSiniestros = _archivo.getCantidadRegistros();
            int contador = 0;
            for (int j = 0; j < cantidadSiniestros; j++) {
                Siniestro s = _archivo.leer(j);
                if (s.getIdTipoSiniestro() == tipo.getId() && !s.getEliminado()) {
                    contador++;                    
                }
            }
            cout << "Cantidad de siniestros: " << contador << endl;
        }
    }

}

void SiniestroManager::listadoSiniestrosPorPoliza(){
    int idPoliza;
    cout << "ID de la poliza: "; cin >> idPoliza;
    int cantidadPolizas = _polizaArchivo.getCantidadRegistros();
    if (idPoliza >= 1 && idPoliza <= cantidadPolizas){      
        int cantidadSiniestros = _archivo.getCantidadRegistros();
        bool encontrado = false;
        for (int i = 0; i < cantidadSiniestros; i++) {
            Siniestro s = _archivo.leer(i);
            if (s.getIdPoliza() == idPoliza && !s.getEliminado()) {
                mostrarSiniestro(s);
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No se encontraron siniestros para la poliza indicada." << endl;
        }
    }
    else{
        cout<<"El ID de la poliza es invalido.";
    }
    
}
void SiniestroManager::listadoSiniestrosAprobados(){
    int cantidadSiniestros = _archivo.getCantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidadSiniestros; i++) {
        Siniestro s = _archivo.leer(i);
        if (s.getEstado() && !s.getEliminado()) {
            mostrarSiniestro(s);
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron siniestros aprobados." << endl;
    }
}
void SiniestroManager::listadoSiniestrosNoAprobados(){
    int cantidadSiniestros = _archivo.getCantidadRegistros();
    bool encontrado = false;
    for (int i = 0; i < cantidadSiniestros; i++) {
        Siniestro s = _archivo.leer(i);
        if (!s.getEstado() && !s.getEliminado()) {
            mostrarSiniestro(s);
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron siniestros no aprobados." << endl;
    }
}
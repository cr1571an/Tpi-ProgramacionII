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
        Siniestro* vectSiniestros = new Siniestro[cantidad];
        cantidad = _archivo.leerTodos(vectSiniestros, cantidad);
        ordenarPorFechaSiniestro(vectSiniestros, cantidad);
        for (int i = 0; i < cantidad; i++) {
            Siniestro s = vectSiniestros[i];
            if (!s.getEliminado()) 
                mostrarSiniestro(s);
        }
        delete[] vectSiniestros;
    }
    else {
        cout << "NO HAY SINIESTROS PARA MOSTRAR." << endl;
    }    
}

void SiniestroManager::ordenarPorFechaSiniestro(Siniestro vect[], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (vect[j].getFechaSiniestro() > vect[j + 1].getFechaSiniestro()) {
                Siniestro temp = vect[j];
                vect[j] = vect[j + 1];
                vect[j + 1] = temp;
            }
        }
    }
}

void SiniestroManager::cargar() {
    int idPoliza;
    cout << "ID DE LA POLIZA ASOCIADA: "; cin >> idPoliza;

    int id = _archivo.getNuevoID();
    int dia, mes, anio;
    cout << "INGRESE EL DIA DE LA FECHA DEL SINIESTRO (DD): ";
    cin >> dia;
    cout << "INGRESE EL MES DE LA FECHA DEL SINIESTRO (MM): ";
    cin >> mes;
    cout << "INGRESE EL ANIO DE LA FECHA DEL SINIESTRO (AAAA): ";
    cin >> anio;

    Fecha fecha(dia, mes, anio);
    int idTipo;    
    float costo;
    
    cout << "ID DEL TIPO DE SINIESTRO: "; cin >> idTipo;
    if (_tiposSiniestrosArchivo.buscarID(idTipo) == -1) {
        cout << "LA POLIZA ASOCIADA NO EXISTE. OPERACION CANCELADA." << endl;
        return;
    }

    cout << "COSTO ESTIMADO: "; cin >> costo;
    if (costo < 0) {
        cout << "EL COSTO ESTIMADO NO PUEDE SER NEGATIVO. OPERACION CANCELADA." << endl;
        return;
    }

    Siniestro s(id, idPoliza, fecha, idTipo, costo, true, false);
    if (_archivo.guardar(s)) cout << "SINIESTRO REGISTRADO." << endl;
    else cout << "ERROR AL GUARDAR." << endl;
}


void SiniestroManager::eliminar() {
    int id;
    cout << "ID DEL SINIESTRO: "; cin >> id;
    if (id >= 0){
        int pos = _archivo.buscarID(id);
        if (pos != -1) {
            cout << (_archivo.eliminar(pos) ? "SINIESTRO ELIMINADO." : "NO SE ENCONTRO EL SINIESTRO.") << endl;
        } else {
            cout << "NO SE ENCONTRO EL SINIESTRO." << endl;
        }
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
    }
}

void SiniestroManager::recuperar() {
    int idSiniestro;
    cout << "INGRESE UN NUMERO DE SINIESTRO: ";
    cin >> idSiniestro;
    if (idSiniestro>= 0){
        int pos = _archivo.buscarID(idSiniestro);
        if (pos != -1 ){
            Siniestro siniestro = _archivo.leer(pos);
            siniestro.setEliminado(false);            
            cout<< (_archivo.guardar(siniestro, pos) ? "SINIESTRO RECUPERADO." : "NO SE PUDO RECUPERAR EL SINIESTRO.") << endl;          
        }
        else
            cout<<"EL ID INGRESADO NO SE ENCONTRO.";
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
    }
}

void SiniestroManager::buscarPorIdPoliza() {
    int idPoliza;
    cout << "ID DE LA POLIZA: "; cin >> idPoliza;

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
        cout << "NO SE ENCONTRARON SINIESTROS PARA LA POLIZA INDICADA." << endl;
    }
}

void SiniestroManager::modificarFechaSiniestro() {
    int id;
    cout << "ID DEL SINIESTRO A MODIFICAR: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        int dia, mes, anio;
        cout << "NUEVA FECHA - DIA: "; cin >> dia;
        cout << "NUEVA FECHA - MES: "; cin >> mes;
        cout << "NUEVA FECHA - ANIO: "; cin >> anio;
        Fecha nuevaFecha(dia, mes, anio);
        s.setFechaSiniestro(nuevaFecha);
        cout << (_archivo.guardar(s, pos) ? "FECHA MODIFICADA." : "ERROR AL MODIFICAR LA FECHA.") << endl;
    } else {
        cout << "NO SE ENCONTRO EL SINIESTRO." << endl;
    }
}

void SiniestroManager::modificarTipoSiniestro() {
    int id;
    cout << "ID DEL SINIESTRO A MODIFICAR: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        int nuevoTipo;
        cout << "NUEVO TIPO DE SINIESTRO: "; 
        cin >> nuevoTipo;
        int posTipo = _tiposSiniestrosArchivo.buscarID(nuevoTipo);
        if (posTipo == -1) {
            cout << "TIPO DE SINIESTRO NO ENCONTRADO. MODIFICACION CANCELADA." << endl;
            return;
        }
        s.setIdTipoSiniestro(nuevoTipo);
        cout << (_archivo.guardar(s, pos) ? "TIPO DE SINIESTRO MODIFICADO." : "ERROR AL MODIFICAR EL TIPO DE SINIESTRO.") << endl;
    } else {
        cout << "NO SE ENCONTRO EL SINIESTRO." << endl;
    }
}

void SiniestroManager::modificarCostoEstimado() {
    int id;
    cout << "ID DEL SINIESTRO A MODIFICAR: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        float nuevoCosto;
        cout << "NUEVO COSTO ESTIMADO: "; cin >> nuevoCosto;
        s.setCostoEstimado(nuevoCosto);
        cout << (_archivo.guardar(s, pos) ? "COSTO ESTIMADO MODIFICADO." : "ERROR AL MODIFICAR EL COSTO ESTIMADO.") << endl;
    } else {
        cout << "NO SE ENCONTRO EL SINIESTRO." << endl;
    }
}

void SiniestroManager::modificarEstadoSiniestro() {
    int id;
    cout << "ID DEL SINIESTRO A MODIFICAR: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        bool nuevoEstado;
        cout << "NUEVO ESTADO (1 PARA VIGENTE, 0 PARA NO VIGENTE): "; cin >> nuevoEstado;
        s.setEstado(nuevoEstado);
        cout << (_archivo.guardar(s, pos) ? "ESTADO MODIFICADO." : "ERROR AL MODIFICAR EL ESTADO.") << endl;
    } else {
        cout << "NO SE ENCONTRO EL SINIESTRO." << endl;
    }
}

void SiniestroManager::mostrarSiniestro(Siniestro siniestro) {
    int posicion = _tiposSiniestrosArchivo.buscarID(siniestro.getIdTipoSiniestro());
    TipoSiniestro tipoSiniestro = _tiposSiniestrosArchivo.leer(posicion); 
    cout << "ID: " << siniestro.getId() << ", POLIZA: " << siniestro.getIdPoliza()
         << ", TIPO: " << tipoSiniestro.getDescripcion()
         << ", COSTO: $" << siniestro.getCostoEstimado()
         << ", FECHA SINIESTRO: " << siniestro.getFechaSiniestro().formatoFecha()
         << ", APROBADO: " << (siniestro.getEstado() ? "SÍ" : "NO")
         << endl;
}

void SiniestroManager::reporteSiniestrosPorTipo() {
    int cantidadTipos = _tiposSiniestrosArchivo.getCantidadRegistros();
    for (int i = 0; i < cantidadTipos; i++) {
        TipoSiniestro tipo = _tiposSiniestrosArchivo.leer(i);
        if (!tipo.getEliminado()) {
            cout << "TIPO DE SINIESTRO: " << tipo.getDescripcion() << endl;
            int cantidadSiniestros = _archivo.getCantidadRegistros();
            int contador = 0;
            for (int j = 0; j < cantidadSiniestros; j++) {
                Siniestro s = _archivo.leer(j);
                if (s.getIdTipoSiniestro() == tipo.getId() && !s.getEliminado()) {
                    contador++;                    
                }
            }
            cout << "CANTIDAD DE SINIESTROS: " << contador << endl;
        }
    }

}

void SiniestroManager::listadoSiniestrosPorPoliza(){
    int idPoliza;
    cout << "ID DE LA POLIZA: "; cin >> idPoliza;
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
            cout << "NO SE ENCONTRARON SINIESTROS PARA LA POLIZA INDICADA." << endl;
        }
    }
    else{
        cout<<"EL ID DE LA POLIZA ES INVALIDO." << endl;
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
        cout << "NO SE ENCONTRARON SINIESTROS APROBADOS." << endl;
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
        cout << "NO SE ENCONTRARON SINIESTROS NO APROBADOS." << endl;
    }
}
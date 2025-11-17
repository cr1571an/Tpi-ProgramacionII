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
                 << ", Prima: " << p.getPrimaMensual()
                 << ", Vigente: " << (p.getVigente() ? "Sí" : "No") << endl;
        }
    }
}

void PolizaManager::cargar() {
    int idCliente = _clienteMenu.buscarCliente();
    int pos = _archivoCliente.buscarIdCliente(idCliente);
    if (pos == -1) {
        cout << "ERROR!. EL CLIENTE NO EXISTE." << endl;
        return;
    }
    if (pos == -3) {
        cout << "ERROR!. EL CLIENTE ESTA ELIMINADO." << endl;
        _clienteMenu.darAltaCliente(idCliente);
        return;
    }
    Cliente cliente = _archivoCliente.leer(pos);
    if (cliente.getEliminado()) {
        cout << "ERROR!. EL CLIENTE ESTA ELIMINADO." << endl;
        _clienteMenu.darAltaCliente(idCliente);
        return;
    }
    _vehiculoManager.mostrarVehiculosDeCliente(idCliente);
    cout << "INGRESE EL ID DEL VEHICULO PARA LA POLIZA: ";
    int idVehiculo;
    cin >> idVehiculo;
    int posVehiculo = _archivoVehiculos.buscarIdVehiculo(idVehiculo);
    if (posVehiculo < 0) {
        cout << "ERROR!. EL VEHICULO NO EXISTE." << endl;
        return;
    }
    Vehiculo vehiculo = _archivoVehiculos.leer(posVehiculo);
    if (vehiculo.getIdCliente() != idCliente || vehiculo.getEliminado()) {
        cout << "ERROR!. EL VEHICULO NO PERTENECE AL CLIENTE O ESTA ELIMINADO." << endl;
        return;
    }

    int id = _archivo.getNuevoID();
    Fecha inicio, fin;
    fin.sumarDias();
    float prima;
    string tipo;
    cout << "TIPO DE SEGURO: "; tipo = cargarCadena();
    cout << "PRIMA MENSUAL: "; cin >> prima;

    Poliza p(id, idVehiculo, inicio, fin, prima, tipo, true, false);
    if (_archivo.guardar(p)) cout << "POLIZA GUARDADA." << endl;
    else cout << "ERROR AL GUARDAR." << endl;
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
void PolizaManager::recuperar() {
    int idPoliza;
    cout << "Ingrese un numero de poliza: ";
    cin >> idPoliza;
    if (idPoliza>= 0){
        int pos = _archivo.buscarID(idPoliza);
        if (pos != -1 ){
            Poliza poliza = _archivo.leer(pos);
            poliza.setEliminado(false);            
            cout<< (_archivo.guardar(poliza, pos) ? "Poliza recuperada." : "No se pudo recuperar la poliza.") << endl;          
        }
        else
            cout<<"El ID ingresado no se encontro.";
    }
    else{
        cout<<"El ID ingresado es invalido.";
    }
}

void PolizaManager::buscarPorPatente(){
    bool encontrado = false;
    string patente;
    cout << "Ingrese patente del vehiculo: ";
    patente = cargarCadena();
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        int cantidad = _archivo.getCantidadRegistros();
        for (int i = 0; i < cantidad; i++) {
            Poliza p = _archivo.leer(i);
            if (p.getIdVehiculo() == idVehiculo && !p.getEliminado()) {
                Vehiculo vehiculo = _archivoVehiculos.leer(p.getIdVehiculo());
                Cliente cliente = _archivoCliente.leer(vehiculo.getIdCliente());
                cout << "ID: " << p.getId() << ", Cliente Apellido: " << cliente.getApellido() << " " << cliente.getNombre()
                     << ", Vehiculo: " << p.getIdVehiculo()
                     << ", Seguro: " << p.getTipoSeguro()
                     << ", Fecha Inicio: " << p.getfechaInicio().formatoFecha()
                     << ", Fecha Fin: " << p.getfechaFin().formatoFecha()
                     << ", Vigente: " << (p.getVigente() ? "Sí" : "No") << endl;
                encontrado = true;
                break;
            }            
        }
        if (!encontrado) {
            cout << "No se encontraron polizas con esa patente." << endl;
        }
    }
    else {
        cout << "No se encontraron vehiculos con esa patente." << endl;
    }

}

int PolizaManager::buscarPorId(){
    int idPoliza;    
    
    cout << "Ingrese un numero de poliza: ";
    cin >> idPoliza;
    if (idPoliza>= 0){
        int pos = _archivo.buscarID(idPoliza);
        return pos;
    }
    else{
        cout<<"El ID ingresado es invalido.";
    }

    return -1;
}
void PolizaManager::modificarFechaInicio(){
    int dia,mes,anio;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        Fecha nuevaFechaInicio, nuevaFechaFin;
        cout << "Ingrese el dia de la fecha de inicio: ";
        cin >> dia;
        cout << "Ingrese el mes de la fecha de inicio: ";
        cin >> mes;
        cout << "Ingrese el anio de la fecha de inicio: ";
        cin >> anio;

        nuevaFechaInicio.setDia(dia);
        nuevaFechaInicio.setMes(mes);
        nuevaFechaInicio.setAnio(anio);
        nuevaFechaFin = nuevaFechaInicio;
        nuevaFechaFin.sumarDias();
        poliza.setFechaInicio(nuevaFechaInicio);
        poliza.setFechaFin(nuevaFechaFin);
        
        cout << (_archivo.guardar(poliza, pos) ? "Poliza modificada." : "No se pudo modificar la poliza.");
    }
    else
        cout<<"El ID ingresado no se encontro.";
}
void PolizaManager::modificarPrima(){
    float nuevaPrima;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        cout << "Ingrese la nueva prima mensual: ";
        cin >> nuevaPrima;
        poliza.setPrimaMensual(nuevaPrima);
        cout << (_archivo.guardar(poliza, pos) ? "Poliza modificada." : "No se pudo modificar la poliza.");
    }
    else
        cout<<"El ID ingresado no se encontro.";

}
void PolizaManager::modificarTipoSeguro(
){
    string nuevoTipo;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        cout << "Ingrese el nuevo tipo de seguro: ";
        nuevoTipo = cargarCadena();
        poliza.setTipoSeguro(nuevoTipo);
        cout << (_archivo.guardar(poliza, pos) ? "Poliza modificada." : "No se pudo modificar la poliza.");
    }
    else
        cout<<"El ID ingresado no se encontro.";
}
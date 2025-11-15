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
    string patente;
    cout << "Ingrese patente del vehiculo: ";
    patente = cargarCadena();
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        int id = _archivo.getNuevoID();
        Fecha inicio, fin;
        fin.sumarDias();
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

void PolizaManager::listarPolizasActivas() {
    int cantidad = _archivo.getCantidadRegistros();
    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (p.getVigente() && !p.getEliminado()) {
            Vehiculo vehiculo = _archivoVehiculos.leer(p.getIdVehiculo());
            Cliente cliente = _archivoCliente.leer(vehiculo.getIdCliente());
            cout << "ID: " << p.getId() << ", Cliente Apellido: " << cliente.getApellido() << " " << cliente.getNombre()
                 << ", Vehiculo: " << p.getIdVehiculo()
                 << ", Seguro: " << p.getTipoSeguro()
                 << ", Fecha Inicio: " << p.getfechaInicio().formatoFecha()
                 << ", Fecha Fin: " << p.getfechaFin().formatoFecha()
                 << ", Prima: " << p.getPrimaMensual() << endl;
        }
    }

    delete[] polizas;
}

void PolizaManager::modificarActivaInactiva() {
    int pos = buscarPorId();
    if (pos != -1) {
        Poliza poliza = _archivo.leer(pos);
        bool vigente = poliza.getVigente();
        poliza.setVigente(!vigente);
        cout << (_archivo.guardar(poliza, pos) ? "Poliza modificada." : "No se pudo modificar la poliza.");
    } else {
        cout << "El ID ingresado no se encontro.";
    }
}

void PolizaManager::listarPorFechaVencimiento() {
    int cantidad = _archivo.getCantidadRegistros();
    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);
   
    for(int i=0; i<cantidad-1; i++){
        bool intercambio = false;
        for(int j=0; j<cantidad - 1 - i; j++){
            if(polizas[j].getfechaFin() > polizas[j+1].getfechaFin()){
                Poliza aux = polizas[j];
                polizas[j] = polizas[j+1];
                polizas[j+1] = aux;
                intercambio = true;
            }
        } 
        
        if(!intercambio){
            break;    
        }
  }  

  for (int i = 0; i < cantidad; i++)
  {
    mostrarPoliza(polizas[i]);
    cout << "------------------------" << endl;
  }
    
    delete [] polizas;    
}

void PolizaManager::mostrarPoliza(Poliza poliza){
    Vehiculo vehiculo = _archivoVehiculos.leer(poliza.getIdVehiculo());
    Cliente cliente = _archivoCliente.leer(vehiculo.getIdCliente());
    cout << "ID: " << poliza.getId() 
         << ", Cliente: " << cliente.getApellido() << " " << cliente.getNombre()
         << ", Vehiculo ID: " << poliza.getIdVehiculo()
         << ", Tipo de Seguro: " << poliza.getTipoSeguro()         
         << ", Fecha Inicio: " << poliza.getfechaInicio().formatoFecha()
         << ", Fecha Fin: " << poliza.getfechaFin().formatoFecha()
         << ", Prima Mensual: " << poliza.getPrimaMensual()
         << ", Vigente: " << (poliza.getVigente() ? "Sí" : "No")
         << ", Eliminado: " << (poliza.getEliminado() ? "Sí" : "No") 
         << endl;
}
#include "PolizaManager.h"
#include "PolizaArchivo.h"
#include "utils.h"
#include "Cliente.h"
#include "TipoSeguro.h"
#include <iostream>
using namespace std;

PolizaManager::PolizaManager()
    : _archivo(), _vehiculoManager(), _archivoCliente(),_archivoVehiculos() {
}

void PolizaManager::mostrar() {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "No hay polizas para mostrar." << endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        Poliza p = _archivo.leer(i);
        if (!p.getEliminado()) {
            mostrarPoliza(p);
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
        int tipo;
        cout << "Id Tipo de seguro: "; cin >> tipo;
        int posTipoSeguro = _archivoTipoSeguros.buscarID(tipo);
        if (posTipoSeguro == -1) {
            cout << "Tipo de seguro no encontrado. Operacion cancelada." << endl;
            return;
        }

        cout << "Prima mensual: "; cin >> prima;

        Poliza p(id, idVehiculo, inicio, fin, prima, tipo, true, false);
        cout << (_archivo.guardar(p) ? "Poliza creada." : "No se pudo crear la poliza.") << endl;
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
                mostrarPoliza(p);
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
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        Fecha nuevaFechaInicio, nuevaFechaFin;
        nuevaFechaInicio=leerFechaValida();

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
        if (nuevaPrima > 0){
            poliza.setPrimaMensual(nuevaPrima);
            cout << (_archivo.guardar(poliza, pos) ? "Poliza modificada." : "No se pudo modificar la poliza.");
        }
        else
            cout << "El valor ingresado es invalido.";
    }
    else
        cout<<"El ID ingresado no se encontro.";

}
void PolizaManager::modificarTipoSeguro(){
    int nuevoTipo;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        cout << "Ingrese el id del nuevo tipo de seguro: ";
        cin >> nuevoTipo;
        if (_archivoTipoSeguros.buscarID(nuevoTipo) != -1){
            poliza.setIdTipoSeguro(nuevoTipo);
            cout << (_archivo.guardar(poliza, pos) ? "Poliza modificada." : "No se pudo modificar la poliza.");
        }
        else
            cout<<"El ID ingresado del tipo de seguro no se encontro.";
    }
    else
        cout<<"El ID de la poliza ingresado no se encontro.";
}

void PolizaManager::listarPolizasActivas() {
    int cantidad = _archivo.getCantidadRegistros();
    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (p.getVigente() && !p.getEliminado()) {
            mostrarPoliza(p);
        }
    }

    delete[] polizas;
}

void PolizaManager::listarPolizasInactivas() {
    int cantidad = _archivo.getCantidadRegistros();
    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (!p.getVigente() && !p.getEliminado()) {
            mostrarPoliza(p);
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
    if (polizas[i].getEliminado() || !polizas[i].getVigente())
      continue;
    mostrarPoliza(polizas[i]);
    cout << "------------------------" << endl;
  }

    delete [] polizas;
}

void PolizaManager::mostrarPoliza(Poliza poliza){
    int posVehiculo = _archivoVehiculos.buscarIdVehiculo(poliza.getIdVehiculo());
    Vehiculo vehiculo = _archivoVehiculos.leer(posVehiculo);
    int posCliente = _archivoCliente.buscarIdCliente(vehiculo.getIdCliente());
    Cliente cliente = _archivoCliente.leer(posCliente);
    int posTipoSeguro = _archivoTipoSeguros.buscarID(poliza.getIdTipoSeguro());
    TipoSeguro tipoSeguro = _archivoTipoSeguros.leer(posTipoSeguro);
    cout << "ID: " << poliza.getId()
         << ", Cliente: " << cliente.getApellido() << " " << cliente.getNombre()
         << ", Vehiculo ID: " << poliza.getIdVehiculo()
         << ", Patente: " << vehiculo.getPatente()
         << ", Tipo de Seguro: " << tipoSeguro.getDescripcion()
         << ", Fecha Inicio: " << poliza.getfechaInicio().formatoFecha()
         << ", Fecha Fin: " << poliza.getfechaFin().formatoFecha()
         << ", Prima Mensual: " << poliza.getPrimaMensual()
         << ", Vigente: " << (poliza.getVigente() ? "Sí" : "No")
         << ", Eliminado: " << (poliza.getEliminado() ? "Sí" : "No")
         << endl;
}

void PolizaManager::buscarPorDniCliente(){
    bool encontrado = false;
    string dni;
    cout << "Ingrese DNI del cliente: ";
    dni = cargarCadena();
    int idCliente = _archivoCliente.buscarDNI(dni);
    if (idCliente != -1) {
        int cantidad = _archivo.getCantidadRegistros();
        Poliza* polizas = new Poliza[cantidad]{};
        _archivo.leerTodos(polizas, cantidad);
        for (int i = 0; i < cantidad; i++) {
            Poliza p = polizas[i];
            Vehiculo vehiculo = _archivoVehiculos.leer(p.getIdVehiculo());
            if (vehiculo.getIdCliente() == idCliente && !p.getEliminado()) {
                mostrarPoliza(p);
                encontrado = true;
            }
        }
        delete[] polizas;
        if (!encontrado) {
            cout << "No se encontraron polizas para ese cliente." << endl;
        }
    }
    else {
        cout << "No se encontraron clientes con ese DNI." << endl;
    }
}

void PolizaManager::procesarPolizas(){
    int cantidad = _archivo.getCantidadRegistros();
    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);

    for (int i = 0; i < cantidad; i++) {
        Poliza p = polizas[i];
        Fecha fechaFin = p.getfechaFin();
        Fecha fechaActual;

        if (fechaActual > fechaFin && p.getVigente() && !p.getEliminado()) {
            p.setVigente(false);
            _archivo.guardar(p, i);
            cout << "Poliza ID " << p.getId() << " ha sido marcada como no vigente." << endl;
        }
    }

    delete [] polizas;
}

void PolizaManager::reportePolizasVigentesYVencidas(){
    int mes, anio;
    cout << "Ingrese mes para la consulta del reporte: ";
    cin >> mes;
    if (mes < 1 || mes > 12) {
        cout << "Mes invalido. Debe estar entre 1 y 12." << endl;
        return;
    }
    cout << "Ingrese anio para la consulta del reporte: ";
    cin >> anio;
    if (anio < 2020 || anio > 2030) {
        cout << "Anio invalido. Debe estar entre 2020 y 2030." << endl;
        return;
    }

    int cantidad = _archivo.getCantidadRegistros();
    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);

    int cantidadFiltradas = cantidadPolizasPeriodo(polizas, cantidad, Fecha(1,mes,anio));
    if (cantidadFiltradas == 0) {
        cout << "No se encontraron polizas vencientes y vigentes en el periodo indicado." << endl;
        delete [] polizas;
        return;
    }

    int cantidadSeguros = _archivoTipoSeguros.getCantidadRegistros();
    TipoSeguro* tiposSeguros = new TipoSeguro[cantidadSeguros]{};
    _archivoTipoSeguros.leerTodos(tiposSeguros, cantidadSeguros);

    Poliza** polizasFiltradas = new Poliza*[cantidadFiltradas]{};
    filtrarPolizasPorFecha(polizas, polizasFiltradas, cantidad, Fecha(1,mes,anio));

    for (int i=0; i < cantidadSeguros; i++) {
        TipoSeguro tipoSeguro = tiposSeguros[i];
        if (tipoSeguro.getEliminado()) {
            continue;
        }

        cout << "Tipo de Seguro: " << tipoSeguro.getDescripcion() << endl;
        int contadorVigentes = 0;
        int contadorVencidas = 0;

        for (int j=0; j < cantidadFiltradas; j++) {
            Poliza* poliza = polizasFiltradas[j];
            (*poliza).getEliminado();
            if (poliza->getIdTipoSeguro() == tipoSeguro.getId() && !poliza->getEliminado()) {
                if (poliza->getVigente()) {
                    contadorVigentes++;
                } else {
                    contadorVencidas++;
                }
            }
        }

        cout << "  Polizas Vigentes: " << contadorVigentes << endl;
        cout << "  Polizas Vencidas: " << contadorVencidas << endl;
    }

    delete [] polizas;
    delete [] polizasFiltradas;
    delete [] tiposSeguros;
}

int PolizaManager::cantidadPolizasPeriodo(Poliza polizas[],int cantidadPolizas, Fecha FechaConsulta){
    int contador = 0;
    for (int i = 0; i < cantidadPolizas; i++) {
        if (polizas[i].getfechaFin() == FechaConsulta && !polizas[i].getEliminado()) {
            contador++;
        }
    }
    return contador;
}

void PolizaManager::filtrarPolizasPorFecha(Poliza polizas[], Poliza* polizasFiltradas[], int cantidadPolizas,Fecha FechaConsulta){
    int indiceFiltrado = 0;
    for (int i = 0; i < cantidadPolizas; i++) {
        if (polizas[i].getfechaFin() == FechaConsulta && !polizas[i].getEliminado()) {
            polizasFiltradas[indiceFiltrado] = &polizas[i];
            indiceFiltrado++;
        }
    }
}

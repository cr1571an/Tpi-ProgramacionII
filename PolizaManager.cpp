#include "PolizaManager.h"
#include "utils.h"
#include "Cliente.h"
#include "TipoSeguro.h"
#include <iostream>
using namespace std;

PolizaManager::PolizaManager()
    : _archivo(), _vehiculoManager(), _archivoCliente(),_archivoVehiculos() {
}

void PolizaManager::mostrar() {
    cout << "-- LISTADO DE POLIZAS --" << endl;
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS PARA MOSTRAR." << endl;
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
    cout << "-- FORMULARIO DE ALTA DE POLIZA --" << endl;
    cout << "INGRESE LA PATENTE DEL VEHICULO: ";
    patente = cargarCadena();
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        if (tienePolizasVigentes(idVehiculo)) {
            cout << "EL VEHICULO YA TIENE UNA POLIZA VIGENTE. NO SE PUEDE CREAR UNA NUEVA POLIZA." << endl;
            return;
        }
        int id = _archivo.getNuevoID();
        Fecha inicio, fin;
        cout << "FECHA DE INICIO DE LA POLIZA:" << endl;
        inicio = leerFechaValida();
        fin = inicio;        
        fin.sumarDias();
        float prima;
        int tipo;
        cout << "ID TIPO DE SEGURO: "; cin >> tipo;
        int posTipoSeguro = _archivoTipoSeguros.buscarID(tipo);
        if (posTipoSeguro == -1) {
            cout << "TIPO DE SEGURO NO ENCONTRADO. OPERACION CANCELADA." << endl;
            return;
        }

        cout << "PRIMA MENSUAL: "; cin >> prima;

        Poliza p(id, idVehiculo, inicio, fin, prima, tipo, true, false);
        cout << (_archivo.guardar(p) ? "POLIZA CREADA." : "NO SE PUDO CREAR LA POLIZA.") << endl;
        generarVencimientos(p,3);
    } else {
        cout << "NO SE ENCONTRARON VEHICULOS CON ESA PATENTE." << endl;
    }
}


void PolizaManager::eliminar() {
    int idPoliza;
    cout << "INGRESE UN NUMERO DE POLIZA: ";
    cin >> idPoliza;
    if (idPoliza>= 0){
        int pos = _archivo.buscarID(idPoliza);
        if (pos != -1)
            cout<< (_archivo.eliminar(pos) ? "POLIZA ELIMINADA." : "NO SE ENCONTRO LA POLIZA.") << endl;
        else
            cout<<"EL ID INGRESADO NO SE ENCONTRO.";
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
    }
}
void PolizaManager::recuperar() {
    int idPoliza;
    cout << "INGRESE UN NUMERO DE POLIZA: ";
    cin >> idPoliza;
    if (idPoliza>= 0){
        int pos = _archivo.buscarID(idPoliza);
        if (pos != -1 ){
            Poliza poliza = _archivo.leer(pos);
            poliza.setEliminado(false);
            cout<< (_archivo.guardar(poliza, pos) ? "POLIZA RECUPERADA." : "NO SE PUDO RECUPERAR LA POLIZA.") << endl;
        }
        else
            cout<<"EL ID INGRESADO NO SE ENCONTRO.";
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
    }
}

void PolizaManager::buscarPorPatente(){
    bool encontrado = false;
    string patente;
    cout << "INGRESE PATENTE DEL VEHICULO: ";
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
            cout << "NO SE ENCONTRARON POLIZAS CON ESA PATENTE." << endl;
        }
    }
    else {
        cout << "NO SE ENCONTRARON VEHICULOS CON ESA PATENTE." << endl;
    }

}

int PolizaManager::buscarPorId(){
    int idPoliza;

    cout << "INGRESE UN NUMERO DE POLIZA: ";
    cin >> idPoliza;
    if (idPoliza>= 0){
        int pos = _archivo.buscarID(idPoliza);
        return pos;
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
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

        cout << (_archivo.guardar(poliza, pos) ? "POLIZA MODIFICADA." : "NO SE PUDO MODIFICAR LA POLIZA.");
    }
    else
        cout<<"EL ID INGRESADO NO SE ENCONTRO.";
}
void PolizaManager::modificarPrima(){
    float nuevaPrima;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        cout << "INGRESE LA NUEVA PRIMA MENSUAL: ";
        cin >> nuevaPrima;
        if (nuevaPrima > 0){
            poliza.setPrimaMensual(nuevaPrima);
            cout << (_archivo.guardar(poliza, pos) ? "POLIZA MODIFICADA." : "NO SE PUDO MODIFICAR LA POLIZA.");
        }
        else
            cout << "EL VALOR INGRESADO ES INVALIDO.";
    }
    else
        cout<<"EL ID INGRESADO NO SE ENCONTRO.";

}
void PolizaManager::modificarTipoSeguro(){
    int nuevoTipo;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        cout << "INGRESE EL ID DEL NUEVO TIPO DE SEGURO: ";
        cin >> nuevoTipo;
        if (_archivoTipoSeguros.buscarID(nuevoTipo) != -1){
            poliza.setIdTipoSeguro(nuevoTipo);
            cout << (_archivo.guardar(poliza, pos) ? "POLIZA MODIFICADA." : "NO SE PUDO MODIFICAR LA POLIZA.");
        }
        else
            cout<<"EL ID INGRESADO DEL TIPO DE SEGURO NO SE ENCONTRO.";
    }
    else
        cout<<"EL ID DE LA POLIZA INGRESADO NO SE ENCONTRO.";
}

void PolizaManager::listarPolizasVigentes() {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS VIGENTES PARA MOSTRAR." << endl;
        return;
    }

    cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||              POLIZAS VIGENTES                  ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    )";
    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (estaVigente(p) && !p.getEliminado())
            mostrarPoliza(p);
        
    }

    delete[] polizas;
}

void PolizaManager::listarPolizasNoVigentes() {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS NO VIGENTES PARA MOSTRAR." << endl;
        return;
    }

    cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||              POLIZAS NO VIGENTES               ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    )";

    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (!estaVigente(p) && !p.getEliminado())
            mostrarPoliza(p);
    }

    delete[] polizas;
}

void PolizaManager::listarPorFechaVencimiento() {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS PARA MOSTRAR." << endl;
        return;
    }

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
    if (polizas[i].getEliminado())
      continue;
    mostrarPoliza(polizas[i]);
    cout << "------------------------" << endl;
  }

    delete [] polizas;
}

void PolizaManager::mostrarPoliza(Poliza poliza){
    int posVehiculo = _archivoVehiculos.buscarVehiculo(poliza.getIdVehiculo());
    Vehiculo vehiculo = _archivoVehiculos.leer(posVehiculo);
    int posCliente = _archivoCliente.buscarIdCliente(vehiculo.getIdCliente());
    Cliente cliente = _archivoCliente.leer(posCliente);
    int posTipoSeguro = _archivoTipoSeguros.buscarID(poliza.getIdTipoSeguro());
    TipoSeguro tipoSeguro = _archivoTipoSeguros.leer(posTipoSeguro);
    cout << "---------------------------------------------\n";
    cout << "              POLIZA N° " << poliza.getId() << "\n";
    cout << "---------------------------------------------\n";
    cout << "Cliente ID    : " << cliente.getIdCliente() << "\n";
    cout << "Cliente        : " << cliente.getApellido() << " " << cliente.getNombre() << "\n";
    cout << "DNI           : " << cliente.getDni() << "\n";
    cout << "Vehículo ID    : " << poliza.getIdVehiculo() << "\n";
    cout << "Patente        : " << vehiculo.getPatente() << "\n";
    cout << "Tipo Seguro    : " << tipoSeguro.getDescripcion() << "\n";
    cout << "Fecha Inicio   : " << poliza.getfechaInicio().formatoFecha() << "\n";
    cout << "Fecha Fin      : " << poliza.getfechaFin().formatoFecha() << "\n";
    cout << "Prima Mensual  : " << poliza.getPrimaMensual() << "\n";
    cout << "Suma Asegurada : " << poliza.getSumaAsegurada() << "\n";
    cout << "Eliminado      : " << (poliza.getEliminado() ? "SI" : "NO") << "\n";
    cout << "---------------------------------------------\n";

}

void PolizaManager::buscarPorDniCliente(){
    bool encontrado = false;
    string dni;
    cout << "INGRESE DNI DEL CLIENTE: ";
    dni = cargarCadena();
    int posCliente = _archivoCliente.buscarDNI(dni);

    if (posCliente != -1) {
        Cliente cliente = _archivoCliente.leer(posCliente);
        int idCliente = cliente.getIdCliente();
        int cantidad = _archivo.getCantidadRegistros();
        Poliza* polizas = new Poliza[cantidad]{};
        _archivo.leerTodos(polizas, cantidad);
        for (int i = 0; i < cantidad; i++) {
            Poliza p = polizas[i];
            int posVehiculo = _archivoVehiculos.buscarVehiculo(p.getIdVehiculo());
            Vehiculo vehiculo = _archivoVehiculos.leer(posVehiculo);
            if (vehiculo.getIdCliente() == idCliente && !p.getEliminado()) {
                mostrarPoliza(p);
                encontrado = true;
            }
        }
        delete[] polizas;
        if (!encontrado) {
            cout << "NO SE ENCONTRARON POLIZAS PARA ESE CLIENTE." << endl;
        }
    }
    else {
        cout << "NO SE ENCONTRARON CLIENTES CON ESE DNI." << endl;
    }
}
void PolizaManager::reportePolizasVigentesYVencidas(){
//     int mes, anio;
//     cout << "INGRESE MES PARA LA CONSULTA DEL REPORTE: ";
//     cin >> mes;
//     if (mes < 1 || mes > 12) {
//         cout << "MES INVALIDO. DEBE ESTAR ENTRE 1 Y 12." << endl;
//         return;
//     }
//     cout << "INGRESE ANIO PARA LA CONSULTA DEL REPORTE: ";
//     cin >> anio;
//     if (anio < 2020 || anio > 2030) {
//         cout << "ANIO INVALIDO. DEBE ESTAR ENTRE 2020 Y 2030." << endl;
//         return;
//     }

//     int cantidad = _archivo.getCantidadRegistros();
//     Poliza* polizas = new Poliza[cantidad]{};
//     _archivo.leerTodos(polizas, cantidad);

//     int cantidadFiltradas = cantidadPolizasPeriodo(polizas, cantidad, Fecha(1,mes,anio));
//     if (cantidadFiltradas == 0) {
//         cout << "NO SE ENCONTRARON POLIZAS VIGENTES Y VENCIDAS EN EL PERIODO INDICADO." << endl;
//         delete [] polizas;
//         return;
//     }

//     cout << "------------------------" << endl;
//     cout << "REPORTE DE SEGURO" << endl;

//     int cantidadSeguros = _archivoTipoSeguros.getCantidadRegistros();
//     TipoSeguro* tiposSeguros = new TipoSeguro[cantidadSeguros]{};
//     _archivoTipoSeguros.leerTodos(tiposSeguros, cantidadSeguros);

//     Poliza** polizasFiltradas = new Poliza*[cantidadFiltradas]{};
//     filtrarPolizasPorFecha(polizas, polizasFiltradas, cantidad, Fecha(1,mes,anio));

//     for (int i=0; i < cantidadSeguros; i++) {
//         TipoSeguro tipoSeguro = tiposSeguros[i];
//         if (tipoSeguro.getEliminado()) {
//             continue;
//         }

//         cout << "TIPO DE SEGURO: " << tipoSeguro.getDescripcion() << endl;
//         int contadorVigentes = 0;
//         int contadorVencidas = 0;

//         for (int j=0; j < cantidadFiltradas; j++) {
//             Poliza* poliza = polizasFiltradas[j];
//             (*poliza).getEliminado();
//             if (poliza->getIdTipoSeguro() == tipoSeguro.getId() && !poliza->getEliminado()) {
//                 if (poliza->getVigente()) {
//                     contadorVigentes++;
//                 } else {
//                     contadorVencidas++;
//                 }
//             }
//         }

//         cout << "  POLIZAS VIGENTES: " << contadorVigentes << endl;
//         cout << "  POLIZAS VENCIDAS: " << contadorVencidas << endl;
//     }

//     delete [] polizas;
//     delete [] polizasFiltradas;
//     delete [] tiposSeguros;
// }

// int PolizaManager::cantidadPolizasPeriodo(Poliza polizas[],int cantidadPolizas, Fecha FechaConsulta){
//     int contador = 0;
//     for (int i = 0; i < cantidadPolizas; i++) {
//         if (polizas[i].getfechaFin() == FechaConsulta && !polizas[i].getEliminado()) {
//             contador++;
//         }
//     }
//     return contador;
}

void PolizaManager::filtrarPolizasPorFecha(Poliza polizas[], Poliza* polizasFiltradas[], int cantidadPolizas,Fecha FechaConsulta){
//     int indiceFiltrado = 0;
//     for (int i = 0; i < cantidadPolizas; i++) {
//         if (polizas[i].getfechaFin() == FechaConsulta && !polizas[i].getEliminado()) {
//             polizasFiltradas[indiceFiltrado] = &polizas[i];
//             indiceFiltrado++;
//         }
//     }
}

void PolizaManager::generarVencimientos(Poliza poliza, int cantidadVencimientos) {
    VencimientosArchivo _archivoVencimientos;
    Fecha fechaVencimiento = poliza.getfechaInicio();
    for (int i = 0; i < cantidadVencimientos; i++) {
        fechaVencimiento.sumarDias(30);
        int idVencimiento = _archivoVencimientos.getNuevoID();
        float montoVencimiento = calcularMontoVencimiento(poliza.getPrimaMensual());
        Vencimiento vencimiento(idVencimiento, poliza.getId(), fechaVencimiento, montoVencimiento, false, false);
        cout << (_archivoVencimientos.guardar(vencimiento) ? "VENCIMIENTO CREADO,CON FECHA: " + vencimiento.getVencimiento().formatoFecha() : "NO SE PUDO CREAR EL VENCIMIENTO.") << endl;
    }
}

float PolizaManager::calcularMontoVencimiento(int primaMensual) {
    float iva = primaMensual * 0.21;
    return primaMensual + iva;
}

bool PolizaManager::estaVigente(Poliza poliza) {
    Fecha fechaActual;
    return (poliza.getfechaInicio() <= fechaActual && fechaActual <= poliza.getfechaFin());
}

bool PolizaManager::tienePolizasVigentes(int idVehiculo) {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        return false;
    }
    
    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);
    
    for (int i = 0; i < cantidad; i++) {
        Poliza p = polizas[i];
        if (p.getIdVehiculo() == idVehiculo && estaVigente(p) && !p.getEliminado()) {
            delete[] polizas;
            return true;
        }
    }
    delete[] polizas;
    return false;
}

void PolizaManager::reportePolizasSinCobertura() {
    cout << "-- REPORTE DE POLIZAS SIN COBERTURA --" << endl;
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS PARA MOSTRAR." << endl;
        return; 
    }
    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < cantidad; i++) {
        Poliza p = polizas[i];
        if (!p.getEliminado()) {
            int cantidadVencimientos = _archivoVencimientos.getCantidadRegistros();
            Vencimiento * vencimientos = new Vencimiento[cantidadVencimientos]{};
            _archivoVencimientos.leerTodos(vencimientos, cantidadVencimientos);
            
            for (int j = 0; j < cantidadVencimientos; j++) {
                Vencimiento v = vencimientos[j];
                if (v.getIdPoliza() == p.getId() && v.estaVencido()) {
                    mostrarPoliza(p);
                    delete[] vencimientos;
                    delete[] polizas;
                    return;
                }
            }
            delete[] vencimientos;
            if (cantidadVencimientos == 0) {
                cout << "NO HAY VENCIMIENTOS REGISTRADOS." << endl;
                delete[] polizas;
                return;
            }            
        }
    }
    delete[] polizas;
}

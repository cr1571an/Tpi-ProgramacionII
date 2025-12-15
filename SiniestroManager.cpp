#include "SiniestroManager.h"
#include <iostream>
using namespace std;
#include "utils.h"
#include "TipoSiniestro.h"
#include <iomanip>

SiniestroManager::SiniestroManager()
    : _archivo(), _polizaArchivo(), _tiposSiniestrosArchivo(), _vehiculoArchivo(), _clienteArchivo(), _pagoManager(), _vencimientosArchivo() {
}

void SiniestroManager::mostrar() {
    cout << "============================================" << endl;
    cout << "            LISTADO DE SINIESTROS           " << endl;
    cout << "============================================" << endl;

    cout << "ORDENADADOS POR FECHA DE SINIESTRO" << endl;
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
    Fecha f;
    int id = _archivo.getNuevoID();
    int idTipoSiniestro = mostrarOpcionesDeSiniestros();
    if (idTipoSiniestro == 0) return;
    system("cls");
    cout << "=============================================" << endl;
    cout << centrar("TIPO DE SINIESTRO " + _tiposSiniestrosArchivo.leer(idTipoSiniestro - 1).getDescripcion(),45)<<endl;
    cout << centrar("NUMERO DE SINIESTRO " + to_string(id),45)<<endl;
    cout << centrar("FECHA DE ALTA " + f.formatoFecha() ,45)<<endl;
    cout << "============================================" << endl;
    int idPoliza;
    cout << "ID DE LA POLIZA ASOCIADA: "; cin >> idPoliza;
    int posPoliza = _polizaArchivo.buscarID(idPoliza);
    if (posPoliza == -1){
        cout<< "EL ID INGRESADO NO EXISTE. SE CANCELA EL ALTA DE SINIESTRO."<<endl;
        return;
    }
    Poliza poliza = _polizaArchivo.leer(posPoliza);
    if (poliza.getEliminado()){
        cout << "LA POLIZA SE ENCUENTRA ELIMINADA. SE CANCELA EL ALTA DE SINIESTRO." << endl;
        return;
    }

    if (!poliza.estaVigente(f)) {
        cout << "LA POLIZA NO ESTA VIGENTE EN LA FECHA DEL SINIESTRO. SE CANCELA EL ALTA DE SINIESTRO." << endl;
        return;
    }

    float costo;       
    cout << "COSTO ESTIMADO: "; cin >> costo;
    if (costo <= 0 || costo > 10000000) {
        cout << "EL COSTO NO PUEDE SER NEGATIVO O SUPERIOR A 10.000.000. SE CANCELA EL ALTA DE SINIESTRO." << endl;
        return;
    }

    Siniestro s(id, idPoliza, f, idTipoSiniestro, costo, false);
    if (_archivo.guardar(s)) cout << "SINIESTRO REGISTRADO." << endl;
    else cout << "ERROR AL GUARDAR." << endl;

}


void SiniestroManager::eliminar() {
    cout << "============================================" << endl;
    cout << "         ELIMINAR SINIESTRO POR ID          " << endl;
    cout << "============================================" << endl;
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
    cout << "============================================" << endl;
    cout << "        RECUPERAR SINIESTRO POR ID          " << endl;
    cout << "============================================" << endl;
    int idSiniestro;
    cout << "INGRESE UN ID DE SINIESTRO: ";
    cin >> idSiniestro;
    if (idSiniestro>= 0){
        int pos = _archivo.buscarID(idSiniestro);
        if (pos != -1 ){
            Siniestro siniestro = _archivo.leer(pos);
            siniestro.setEliminado(false);            
            cout<< (_archivo.guardar(siniestro, pos) ? "SINIESTRO RECUPERADO." : "NO SE PUDO RECUPERAR EL SINIESTRO.") << endl;          
        }
        else
            cout<<"EL ID INGRESADO NO SE ENCONTRO."<<endl;
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO."<<endl;;
    }
}

void SiniestroManager::buscarPorIdPoliza() {
    cout << "============================================" << endl;
    cout << "   BUSCAR SINIESTROS ASOCIADOS A UNA POLIZA " << endl;
    cout << "============================================" << endl;
    int idPoliza;
    cout << "ID DE LA POLIZA: "; cin >> idPoliza;
    if (idPoliza < 0) {
        cout << "EL ID DE LA POLIZA ES INVALIDO." << endl;
        return;
    }

    int pos = _polizaArchivo.buscarID(idPoliza);
    if (pos != -1) {
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
            cout << "NO SE ENCONTRARON SINIESTROS PARA EL ID DE POLIZA INGRESADO." << endl;
        }
    }
    else{
        cout << "EL ID DE POLIZA INGRESADO NO EXISTE." << endl;
    }
}

void SiniestroManager::modificarFechaSiniestro() {
    cout << "============================================" << endl;
    cout << "        MODICAR FECHA DEL SINIESTRO         " << endl;
    cout << "============================================" << endl;
    int id;
    cout << "ID DEL SINIESTRO A MODIFICAR: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        Fecha nuevaFecha = leerFechaValida();
        if (nuevaFecha.getAnio() == -1){
            cout<< "SE CANCELA LA OPERACION." << endl;
        }
        s.setFechaSiniestro(nuevaFecha);
        cout << (_archivo.guardar(s, pos) ? "FECHA MODIFICADA." : "ERROR AL MODIFICAR LA FECHA.") << endl;
    } else {
        cout << "EL ID DE SINIESTRO INGRESADO NO EXISTE." << endl;
    }
}

void SiniestroManager::modificarTipoSiniestro() {
    cout << "============================================" << endl;
    cout << "      MODIFICAR EL TIPO DE SINIESTRO        " << endl;
    cout << "============================================" << endl;
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
    cout << "============================================" << endl;
    cout << "        MODIFICAR EL COSTO ESTIMADO         " << endl;
    cout << "============================================" << endl;
    int id;
    cout << "ID DEL SINIESTRO A MODIFICAR: "; cin >> id;
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        float nuevoCosto;
        cout << "NUEVO COSTO ESTIMADO: "; cin >> nuevoCosto;
        if (nuevoCosto < 0) {
            cout << "EL COSTO ESTIMADO NO PUEDE SER NEGATIVO. MODIFICACION CANCELADA." << endl;
            return;
        }
        s.setCostoEstimado(nuevoCosto);
        cout << (_archivo.guardar(s, pos) ? "COSTO ESTIMADO MODIFICADO." : "ERROR AL MODIFICAR EL COSTO ESTIMADO.") << endl;
    } else {
        cout << "NO SE ENCONTRO EL SINIESTRO." << endl;
    }
}

void SiniestroManager::mostrarSiniestro(Siniestro siniestro) {
    int posSiniestro = _tiposSiniestrosArchivo.buscarID(siniestro.getIdTipoSiniestro());
    TipoSiniestro tipoSiniestro = _tiposSiniestrosArchivo.leer(posSiniestro);

    int posPoliza = _polizaArchivo.buscarID(siniestro.getIdPoliza());
    Poliza poliza = _polizaArchivo.leer(posPoliza);

    int posVehiculo = _vehiculoArchivo.buscarVehiculo(poliza.getIdVehiculo());
    Vehiculo vehiculo = _vehiculoArchivo.leer(posVehiculo);

    int posCliente = _clienteArchivo.buscarIdCliente(vehiculo.getIdCliente());
    Cliente cliente = _clienteArchivo.leer(posCliente);

    
    cout << "---------------------------------------------\n";
    cout << "              SINIESTRO N° " << siniestro.getId() << "\n";
    cout << "---------------------------------------------\n";
    cout << "Póliza ID        : " << siniestro.getIdPoliza() << "\n";
    cout << "Vehículo ID       : " << vehiculo.getIdVehiculo() << "\n";
    cout << "Patente          : " << vehiculo.getPatente() << "\n";
    cout << "Cliente ID       : " << cliente.getIdCliente() << "\n";
    cout << "Cliente          : " << cliente.getApellido() << " " << cliente.getNombre() << "\n";
    cout << "Tipo             : " << tipoSiniestro.getDescripcion() << "\n";
    cout << "Costo Estimado   : $" << fixed << setprecision(2)<< siniestro.getCostoEstimado() << "\n";
    cout << "Fecha Siniestro  : " << siniestro.getFechaSiniestro().formatoFecha() << "\n";
    cout << "---------------------------------------------\n";
}

void SiniestroManager::reporteCoberturaSiniestros(){
    int cantidadSiniestros = _archivo.getCantidadRegistros();
    if (cantidadSiniestros == 0) {
        cout << "NO SE ENCONTRARON SINIESTROS. NO ES POSIBLE REALIZAR EL REPORTE." << endl;
        return;
    }

    cout << "============================================================" << endl;
    cout << "   REPORTE COBERTURA DE SINIESTROS POR PERIODO DE FECHAS    " << endl;
    cout << "============================================================" << endl;
    cout << "INGRESE LA FECHA INICIAL: "; 
    Fecha fechaDesde = leerFechaValida();
    if (fechaDesde.getAnio() == -1) {
        cout << "SE CANCELA LA OPERACION." << endl;
        return;
    }
    cout << "INGRESE LA FECHA FINAL: "; 
    Fecha fechaHasta = leerFechaValida();

    if (fechaHasta.getAnio() == -1) {
        cout << "SE CANCELA LA OPERACION." << endl;
        return;
    }

    if (fechaHasta < fechaDesde) {
        cout << "LA FECHA FINAL NO PUEDE SER MENOR A LA FECHA INICIAL." << endl;
        return;
    }

    if (fechaDesde.getAnio() < 2023 || fechaHasta.getAnio() > 2027) {
        cout << "EL PERIODO DE FECHAS DEBE ESTAR ENTRE 2023 Y 2027." << endl;
        return;
    }

    Siniestro* siniestros = new Siniestro[cantidadSiniestros]{};
    _archivo.leerTodos(siniestros,cantidadSiniestros);

    int cantidadSiniestrosFiltrados = cantidadSiniestrosPeriodo(fechaDesde, fechaHasta, siniestros, cantidadSiniestros);
    if (cantidadSiniestrosFiltrados == 0) {
        cout << "NO SE ENCONTRARON SINIESTROS EN EL PERIODO INDICADO." << endl;
        delete[] siniestros;
        return;
    }

    Siniestro** siniestrosFiltrados = new Siniestro*[cantidadSiniestrosFiltrados]{};
    filtrarPorPeriodo(fechaDesde, fechaHasta, siniestros, siniestrosFiltrados, cantidadSiniestros);

    if (cantidadSiniestrosFiltrados == 0) {
        cout << "NO SE ENCONTRARON SINIESTROS EN EL PERIODO INDICADO." << endl;
        delete[] siniestros;
        delete[] siniestrosFiltrados;
        return;
    }

    cout << "============================================================" << endl;
    cout << "   REPORTE COBERTURA DE SINIESTROS POR PERIODO DE FECHAS    " << endl;
    cout << "============================================================" << endl;
    cout << "FECHA INICIAL: " << fechaDesde.formatoFecha() << endl << "FECHA FINAL: " << fechaHasta.formatoFecha() << endl;
    cout << "============================================================" << endl;
    cout << "NUMERO DE SINIESTROS: " << cantidadSiniestrosFiltrados << endl;
    cout << "============================================================" << endl;
    cout << "============================================================" << endl;

    int cantidadAprobados = 0;
    int cantidadNoAprobados = 0;


    for (int i = 0; i < cantidadSiniestrosFiltrados; i++) {
        int idPoliza = (*siniestrosFiltrados[i]).getIdPoliza();
        int pos = _polizaArchivo.buscarID(idPoliza);
        Poliza poliza = _polizaArchivo.leer(pos);

        Fecha fechaSiniestro = (*siniestrosFiltrados[i]).getFechaSiniestro();
        bool vigente = (fechaSiniestro >= poliza.getfechaInicio() && fechaSiniestro <= poliza.getfechaFin());
        bool alDia = _pagoManager.polizaPagosAlDia(idPoliza);
        bool conCobertura = (validarCobertura(fechaSiniestro, idPoliza));
        if (vigente && alDia && conCobertura) {
            mostrarSiniestro(*siniestrosFiltrados[i]);
            cout << "SINIESTRO APROBADO" << endl;
            cantidadAprobados++;
            cout << "============================================================" << endl;
        }
        else{
            mostrarSiniestro(*siniestrosFiltrados[i]);
            cout << "SINIESTRO NO APROBADO" << endl;
                if (!vigente) {
            cout << "Motivo: SINIESTRO FUERA DE LA FECHA DE VIGENCIA DE LA POLIZA." << endl;
            }

            if (!alDia) {
                cout << "Motivo: EXISTEN VENCIMIENTOS IMPAGOS (POLIZA NO AL DIA)." << endl;
            }
            else if (!conCobertura) {
                    cout << "Motivo: SE REALIZO EL PAGO POSTERIOR A LA FECHA DEL SINIESTRO." << endl;  
            }

            cantidadNoAprobados++;
            cout << "============================================================" << endl;            
        }
    }
    
    delete[] siniestros;
    delete[] siniestrosFiltrados;
}   

int SiniestroManager::cantidadSiniestrosPeriodo(Fecha fechaDesde, Fecha fechaHasta, Siniestro siniestros[], int cantidad){
    int cantidadSiniestrosFiltrados = 0;

    for (int i = 0; i < cantidad; i++) {
        Fecha fechaSiniestro = siniestros[i].getFechaSiniestro();
        if (fechaSiniestro >= fechaDesde && fechaSiniestro <= fechaHasta) {
            cantidadSiniestrosFiltrados++;
        }
    }
    return cantidadSiniestrosFiltrados;

}

void SiniestroManager::filtrarPorPeriodo(Fecha fechaDesde, Fecha fechaHasta, Siniestro siniestros[],Siniestro* siniestrosFiltrados[], int cantidadSiniestros){
    int cantidadSiniestrosFiltrados= 0;

    for (int i = 0; i < cantidadSiniestros; i++) {
        Fecha fechaSiniestro = siniestros[i].getFechaSiniestro();
        if (fechaSiniestro >= fechaDesde && fechaSiniestro <= fechaHasta && !siniestros[i].getEliminado()) {
            siniestrosFiltrados[cantidadSiniestrosFiltrados] = &siniestros[i];
            cantidadSiniestrosFiltrados++;
        }
    }    
}

bool SiniestroManager::validarCobertura(Fecha fechaSiniestro, int idPoliza){
    int cantidadPagos = _pagoManager.cantidadPagosPorPoliza(idPoliza);
    if (cantidadPagos == 0) {
        return false;
    }
    Pago* pagosRealizados = new Pago[cantidadPagos]{};
    _pagoManager.pagosPorPolizaId(idPoliza, pagosRealizados, cantidadPagos);

    for(int i=0; i<cantidadPagos; i++){
        int posVencimiento = _vencimientosArchivo.buscarID(pagosRealizados[i].getIdVencimiento());
        Vencimiento vencimiento = _vencimientosArchivo.leer(posVencimiento);

        Fecha inicio = vencimiento.getVencimiento();      
        Fecha fin = inicio;
        fin.sumarMes(1);
            
        if (fechaSiniestro >= inicio && fechaSiniestro <= fin){
            bool cubre = fechaSiniestro >= pagosRealizados[i].getFechaPago();
            delete[] pagosRealizados;
            return cubre;
        }
    }        
    delete [] pagosRealizados;
    return false;
}

int SiniestroManager::mostrarOpcionesDeSiniestros() {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||          SELECCIONE UN SINIESTRO      ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - CHOQUE                        ||" << endl;
    cout << "||     2 - ROBO                          ||" << endl;
    cout << "||     3 - INCENDIO                      ||" << endl;
    cout << "||     4 - GRANIZO                       ||" << endl;
    cout << "||---------------------------------------||" << endl;
    cout << "||     0 - VOLVER                        ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl<< endl;
    int opcion;
    do {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        if (opcion < 0 || opcion > 4) {
            cout << "OPCION INCORRECTA..." << endl;
        }
    } while (opcion < 0 || opcion > 4);

    return opcion;
}
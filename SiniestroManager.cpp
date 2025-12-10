#include "SiniestroManager.h"
#include <iostream>
using namespace std;
#include "utils.h"
#include "TipoSiniestro.h"

SiniestroManager::SiniestroManager()
    : _archivo(), _polizaArchivo() {
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
    cout << "============================================" << endl;
    cout << "       FORMULARIO DE ALTA DE SINIESTRO      " << endl;
    cout << "============================================" << endl;
    int idPoliza;
    cout << "ID DE LA POLIZA ASOCIADA: "; cin >> idPoliza;
    int posPoliza = _polizaArchivo.buscarID(idPoliza);
    if (posPoliza == -1){
        cout<< "EL ID INGRESADO NO EXISTE. SE CANCELA EL ALTA DE SINIESTRO."<<endl;
        return;
    }

    int id = _archivo.getNuevoID();

    Fecha fecha = leerFechaValida();
    int anio = fecha.getAnio();

    if (anio == -1){
        cout<< "FECHA INVALIDA, SE CANCELA EL ALTA DE SINIESTRO."<<endl;
        return;
    }
    if (anio < 2023 || anio > 2027) {
    cout << "EL ANIO DEBE ESTAR ENTRE 2023 Y 2027. SE CANCELA EL ALTA DE SINIESTRO."<<endl;
    return;
}
    int idTipo;    
    float costo;
    
    cout << "COSTO ESTIMADO: "; cin >> costo;
    if (costo < 0) {
        cout << "EL COSTO NO PUEDE SER NEGATIVO. SE CANCELA EL ALTA DE SINIESTRO." << endl;
        return;
    }

    int cantidadTiposSiniestros = _tiposSiniestrosArchivo.getCantidadRegistros();
    TipoSiniestro* tiposSiniestros = new TipoSiniestro[cantidadTiposSiniestros]{};

    _tiposSiniestrosArchivo.leerTodos(tiposSiniestros,cantidadTiposSiniestros);

    for (int i=0;i<cantidadTiposSiniestros;i++)
        cout<< i+1 <<") " << tiposSiniestros[i].getDescripcion()<<endl;    
    
    cout << "INGRESE UN TIPO DE SINIESTRO: "; cin >> idTipo;
    
    if ( idTipo < 1 || idTipo > cantidadTiposSiniestros ){
        cout<<"OPCION INGRESA INVALIDA, SE CANCELA EL ALTA DE SINIESTRO."<<endl;;
        delete[] tiposSiniestros;
        return;
    }

    Siniestro s(id, idPoliza, fecha, idTipo, costo, false);
    if (_archivo.guardar(s)) cout << "SINIESTRO REGISTRADO." << endl;
    else cout << "ERROR AL GUARDAR." << endl;

    delete[] tiposSiniestros;
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
            cout<<"EL ID INGRESADO NO SE ENCONTRO.";
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
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
    cout << "Costo Estimado   : $" << siniestro.getCostoEstimado() << "\n";
    cout << "Fecha Siniestro  : " << siniestro.getFechaSiniestro().formatoFecha() << "\n";
    cout << "---------------------------------------------\n";
}

// void SiniestroManager::reporteSiniestrosPorTipo() {
//     int cantidadTipos = _tiposSiniestrosArchivo.getCantidadRegistros();
//     if (cantidadTipos == 0) {
//         cout << "NO SE ENCONTRARON TIPOS DE SINIESTROS." << endl;
//         return;
//     }
//     cout << "------------------------" << endl;
//     cout << "REPORTE DE SINIESTROS POR TIPO" << endl;
//     cout << "------------------------" << endl;
//     for (int i = 0; i < cantidadTipos; i++) {
//         TipoSiniestro tipo = _tiposSiniestrosArchivo.leer(i);
//         if (!tipo.getEliminado()) {
//             cout << "TIPO DE SINIESTRO: " << tipo.getDescripcion() << endl;
//             int cantidadSiniestros = _archivo.getCantidadRegistros();
//             int contador = 0;
//             for (int j = 0; j < cantidadSiniestros; j++) {
//                 Siniestro s = _archivo.leer(j);
//                 if (s.getIdTipoSiniestro() == tipo.getId() && !s.getEliminado()) {
//                     contador++;                    
//                 }
//             }
//             cout << "CANTIDAD DE SINIESTROS: " << contador << endl;
//         }
//     }

// }

// void SiniestroManager::listadoSiniestrosPorPoliza(){
//     int idPoliza;
//     cout << "ID DE LA POLIZA: "; cin >> idPoliza;
//     int cantidadPolizas = _polizaArchivo.getCantidadRegistros();
//     if (idPoliza >= 1 && idPoliza <= cantidadPolizas){      
//         int cantidadSiniestros = _archivo.getCantidadRegistros();
//         bool encontrado = false;
//         for (int i = 0; i < cantidadSiniestros; i++) {
//             Siniestro s = _archivo.leer(i);
//             if (s.getIdPoliza() == idPoliza && !s.getEliminado()) {
//                 mostrarSiniestro(s);
//                 encontrado = true;
//             }
//         }
//         if (!encontrado) {
//             cout << "NO SE ENCONTRARON SINIESTROS PARA LA POLIZA INDICADA." << endl;
//         }
//     }
//     else{
//         cout<<"EL ID DE LA POLIZA ES INVALIDO." << endl;
//     }
    
// }
// void SiniestroManager::listadoSiniestrosAprobados(){
//     int cantidadSiniestros = _archivo.getCantidadRegistros();
//     bool encontrado = false;
//     for (int i = 0; i < cantidadSiniestros; i++) {
//         Siniestro s = _archivo.leer(i);
//         if (s.getEstado() && !s.getEliminado()) {
//             mostrarSiniestro(s);
//             encontrado = true;
//         }
//     }
//     if (!encontrado) {
//         cout << "NO SE ENCONTRARON SINIESTROS APROBADOS." << endl;
//     }
// }
// void SiniestroManager::listadoSiniestrosNoAprobados(){
//     int cantidadSiniestros = _archivo.getCantidadRegistros();
//     bool encontrado = false;
//     for (int i = 0; i < cantidadSiniestros; i++) {
//         Siniestro s = _archivo.leer(i);
//         if (!s.getEstado() && !s.getEliminado()) {
//             mostrarSiniestro(s);
//             encontrado = true;
//         }
//     }
//     if (!encontrado) {
//         cout << "NO SE ENCONTRARON SINIESTROS NO APROBADOS." << endl;
//     }
// }
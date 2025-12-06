#include "Reportes.h"
#include <iostream>
#include "utils.h"

using namespace std;

Reportes::Reportes()
    : _clientesArchivo(),_vehiculosArchivo(),_polizasArchivo(),_siniestroArchivo(){
}

Reportes::Reportes(string archivoClientes, string archivoVehiculos, string archivoPolizas,string archivoSiniestros)
    : _clientesArchivo(archivoClientes), _vehiculosArchivo(archivoVehiculos), _polizasArchivo(archivoPolizas),_siniestroArchivo(archivoSiniestros){
}

void Reportes::clientesConSiniestrosEntreFecha() {
    int cantClientes = _clientesArchivo.getCantidadRegistros();
    if ( cantClientes== 0) {cout << "NO HAY CLIENTES REGISTRADOS."<< endl;return;}
    int cantVehiculos = _vehiculosArchivo.cantidadRegistros();
    if (cantVehiculos == 0) {cout << "NO HAY VEHICULOS REGISTRADOS." <<endl;return;}
    int cantSiniestros = _siniestroArchivo.getCantidadRegistros();
    if (cantSiniestros == 0) {cout << "NO HAY SINIESTROS REGISTRADOS." <<endl;return;}
    int cantPolizas = _polizasArchivo.getCantidadRegistros();
    if (cantPolizas == 0) {cout << "NO HAY POLIZAS REGISTRADOS." << endl;return;}
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout << "| CONSULTA DE CLIENTES CON SINIESTROS EN DETERMINADA FECHAS  |"<<endl;
    cout << "--------------------------------------------------------------"<<endl<< endl;
    cout << "INGRESE LA FECHA DE INICIO DEL PERIODO"<<endl;
    Fecha fechaInicio = leerFechaValida();
    if (fechaInicio.getAnio() == -1){return;}
    Fecha hoy;
    cout << "INGRESE LA FECHA DE FIN DEL PERIODO"<< endl;
    Fecha fechaFin = leerFechaValida();
    if ( fechaFin > hoy){cout << "ERROR! LA FECHA DE FIN NO PUEDE MAYOR A LA FECHA DE HOY." <<endl;return;}
    if (fechaInicio.getAnio() == -1){return;}
    if (fechaFin < fechaInicio){cout << "ERROR! LA FECHA DE FIN NO PUEDE SER MENOR A LA FECHA DE INICIO." <<endl;
        return;
    }
    bool seEncontroAlMenosUno = false;
    bool titilo = true;
    system("cls");
    // RECORRE TODOS LOS SINIESTROS
    for (int i = 0; i < cantSiniestros; ++i){
        Siniestro s = _siniestroArchivo.leer(i);
        if (s.getEliminado())continue;
        Fecha f = s.getFechaSiniestro();
        if (f >= fechaInicio && f <= fechaFin){
            // BUSCA LA POLIZA RELACIONADA AL SINIESTRO EN CUESTION
            int idPoliza = s.getIdPoliza();
            Poliza poliza;
            bool polizaEncontrada= false;
            for (int j = 0; j < cantPolizas; ++j) {
                Poliza p = _polizasArchivo.leer(j);
                if (!p.getEliminado() && p.getId() == idPoliza){
                    poliza = p;
                    polizaEncontrada = true;
                    break;
                }
            }
            if (!polizaEncontrada)continue;
            // BUSCA EL VEHICULO DE LA POLIZA
            int idVehiculo = poliza.getIdVehiculo();
            Vehiculo vehiculo;
            bool vehiculoEncontrado=false;
            for (int k = 0; k < cantVehiculos; ++k){
                Vehiculo v = _vehiculosArchivo.leer(k);
                if (!v.getEliminado() && v.getIdVehiculo() == idVehiculo){
                    vehiculo = v;
                    vehiculoEncontrado =true;
                    break;
                }
            }
            if (!vehiculoEncontrado)continue;
            // BUSCA EL CLIENTE QUE ESTA ASOCIADO EL VEHICULO
            int idCliente = vehiculo.getIdCliente();
            Cliente cliente;
            bool clienteEncontrado= false;
            for(int l = 0; l < cantClientes; ++l){
                Cliente c = _clientesArchivo.leer(l);
                if (!c.getEliminado() && c.getIdCliente() == idCliente){
                    cliente = c;
                    clienteEncontrado =true;
                    break;
                }
            }
            // SI NO SE ENCONTRO EL CLIENTE (SIGUE)
            if(!clienteEncontrado)continue;
            seEncontroAlMenosUno = true;
            if (seEncontroAlMenosUno && titilo) {
                titilo = false;
                cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
                cout << "  CLIENTES QUE REGISTRARON SINIESTROS ENTRE LAS FECHAS "<<fechaInicio.formatoFecha()<< " Y " <<fechaFin.formatoFecha()<<endl;
                cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<< endl;
            }
            cout <<"CLIENTE: " <<cliente.getNombre()<< " " << cliente.getApellido()<< " | DNI: " <<cliente.getDni()<<endl;
            cout <<"TIPO DE SINIESTRO : " <<_tiposSiniestrosArchivo.leer(_tiposSiniestrosArchivo.buscarID(s.getId())).getDescripcion()<<endl;
            cout <<"FECHA: " <<f.formatoFecha()<< " | PRESUPUESTO: $" <<s.getCostoEstimado()<<endl;
            cout << "---------------------------------------------" << endl;
        }
    }
    if (!seEncontroAlMenosUno) {
        cout << "NO SE REGISTRARON SINIESTROS EN ESE PERIODO."<<endl;
    }
}
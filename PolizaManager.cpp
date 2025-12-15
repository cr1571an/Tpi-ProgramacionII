#include "PolizaManager.h"
#include "utils.h"
#include "Cliente.h"
#include "TipoSeguro.h"
#include <iostream>
#include <iomanip>
using namespace std;

PolizaManager::PolizaManager()
    : _archivo(), _vehiculoManager(), _clienteManager(),_archivoCliente(),_archivoVehiculos(), _archivoTipoSeguros(), _archivoVencimientos(),_archivoPagos(), _pagoManager() {
}

void PolizaManager::mostrar() {
    cout << "============================================" << endl;
    cout << "            LISTADO DE POLIZAS              " << endl;
    cout << "============================================" << endl;
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
    int idSeguro, sumaAsegurada, id = _archivo.getNuevoID();
    Fecha inicio, fin;
    float prima;
    Fecha f;
    idSeguro = mostrarOpcionesDeSeguro();
    if (idSeguro == 0) return;
    system("cls");
    cout << "=============================================" << endl;
    cout << centrar("SEGURO " + _archivoTipoSeguros.leer(idSeguro - 1).getDescripcion(),45)<<endl;
    cout << centrar("NUMERO DE POLIZA " + to_string(id),45)<<endl;
    cout << centrar("FECHA DE ALTA " + f.formatoFecha() ,45)<<endl;
    cout << "============================================" << endl;
    cout << "INGRESE LA PATENTE DEL VEHICULO: ";
    string patente = cargarCadena();
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        int pos = _archivoVehiculos.buscarVehiculo(idVehiculo);
        Vehiculo vehiculo = _archivoVehiculos.leer(pos);
        if (vehiculo.getEliminado()) {
            cout << "EL VEHICULO SE ENCUENTRA ELIMINADO." << endl;
            return;
        }
        if (tienePolizasVigentes(idVehiculo)) {
            cout << "EL VEHICULO YA TIENE UNA POLIZA VIGENTE. NO SE PUEDE CREAR UNA NUEVA POLIZA." << endl;
            return;
        }
        cout << "INGRESA PRIMA MENSUAL: "; cin >> prima;
        cout << "INGRESA EL VALOR ASEGURADO DEL VEHICULO: "; cin >> sumaAsegurada;
        fin = Fecha();
        fin.sumarMes(_plazoPoliza);
        Poliza p(id, idVehiculo, inicio, fin, prima, sumaAsegurada, idSeguro, false);
        cout << (_archivo.guardar(p) ? "POLIZA CREADA." : "NO SE PUDO CREAR LA POLIZA.") << endl;
        generarVencimientos(p,_plazoPoliza);
    } else {
        cout << "NO SE ENCONTRARON VEHICULOS CON ESA PATENTE." << endl;
    }
}


void PolizaManager::eliminar() {
    cout << "============================================" << endl;
    cout << "           ELIMINAR POLIZA POR ID           " << endl;
    cout << "============================================" << endl;


    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        if (poliza.getEliminado()){
            cout<<"LA POLIZA YA SE ENCUENTRA ELIMINADA."<<endl;
            return;
        }
        int idPoliza = poliza.getId();
        int cantidadPagos = _pagoManager.cantidadPagosPorPoliza(idPoliza);

        if (cantidadPagos > 0) {
            cout << "LA POLIZA TIENE PAGOS REGISTRADOS, NO SE PUEDE ELIMINAR." << endl;
            return;
        }

        poliza.setEliminado(true);

        if (_archivo.guardar(poliza, pos)){
            cout<<"POLIZA ELIMINADA CON EXITO."<<endl;
            cout <<(_pagoManager.eliminarVencimientosDePoliza(idPoliza) ? "VENCIMIENTOS ELIMINADOS CON EXITO." : "NO SE PUDO ELIMINAR LOS VENCIMIENTOS.") << endl;
        }
        else cout<< ("NO SE ENCONTRO LA POLIZA.") << endl;
    }
}
void PolizaManager::recuperar() {
    cout << "============================================" << endl;
    cout << "         RECUPERAR POLIZA POR ID            " << endl;
    cout << "============================================" << endl;

    int pos = buscarPorId();
    if (pos != -1 ){
        Poliza poliza = _archivo.leer(pos);
        if (!poliza.getEliminado()) {
            cout << "LA POLIZA YA ESTA RECUPERADA." << endl;
            return;
        }
        poliza.setEliminado(false);

        if (_archivo.guardar(poliza, pos)){
            cout<<"POLIZA RECUPERADA CON EXITO."<<endl;
            generarVencimientos(poliza,_plazoPoliza);
        }
        else
            cout<<"NO SE PUDO RECUPERAR LA POLIZA." << endl;
    }
}

void PolizaManager::buscarPorPatente(){
    cout << "============================================" << endl;
    cout << "   BUSCAR POLIZAS POR PATENTE DE VEHICULO   " << endl;
    cout << "============================================" << endl;

    bool encontrado = false;
    string patente;
    cout << "INGRESE PATENTE DEL VEHICULO: ";
    patente = cargarCadena();
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        int pos = _archivoVehiculos.buscarVehiculo(idVehiculo);
        Vehiculo vehiculo = _archivoVehiculos.leer(pos);
        if (vehiculo.getEliminado()) {
            cout << "EL VEHICULO SE ENCUENTRA ELIMINADO." << endl;
            return;

        }
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
        if (pos == -1){
            cout<<"EL ID INGRESADO NO SE ENCONTRO."<<endl;
            return -1;
        }
        return pos;
    }
    else{
        cout<<"EL ID INGRESADO ES INVALIDO.";
    }

    return -1;
}
void PolizaManager::modificarFechaInicio(){
    cout << "============================================" << endl;
    cout << "     MODIFICAR FECHA DE INICIO DE POLIZA    " << endl;
    cout << "============================================" << endl;

    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        if (poliza.getEliminado()) {
            cout << "LA POLIZA SE ENCUENTRA ELIMINADA." << endl;
            return;
        }
        int idPoliza = poliza.getId();
        if (tienePagosRealizados(idPoliza)){
            return;
        }

        Fecha nuevaFechaInicio, nuevaFechaFin;
        nuevaFechaInicio=leerFechaValida();
        if (nuevaFechaInicio.getAnio() == -1) {
            cout << "SE CANCELA LA MODIFICACION." << endl;
            return;
        }

        if (nuevaFechaInicio.getAnio() <2025 || nuevaFechaInicio.getAnio() > 2026){
            cout << "LA FECHA DE INICIO NO PUEDE SER MENOR A 2025 O MAYOR A 2026" << endl;
            return;
        }

        nuevaFechaFin = nuevaFechaInicio;
        nuevaFechaFin.sumarMes(3);
        poliza.setFechaInicio(nuevaFechaInicio);
        poliza.setFechaFin(nuevaFechaFin);
        if (_archivo.guardar(poliza, pos)){
            cout <<"POLIZA MODIFICADA."<<endl;
            _pagoManager.eliminarVencimientosDePoliza(idPoliza);
            generarVencimientos(poliza, _plazoPoliza);
        }

    }
}
void PolizaManager::modificarPrima(){
    cout << "============================================" << endl;
    cout << "      MODIFICAR PRIMA MENSUAL DE POLIZA     " << endl;
    cout << "============================================" << endl;

    float nuevaPrima;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        if (poliza.getEliminado()) {
            cout << "LA POLIZA SE ENCUENTRA ELIMINADA." << endl;
            return;
        }
        int idPoliza = poliza.getId();
        if (!tienePagosRealizados(idPoliza)){
            cout << "INGRESE LA NUEVA PRIMA MENSUAL: ";
            cin >> nuevaPrima;
            if (nuevaPrima > 0){
                poliza.setPrimaMensual(nuevaPrima);
                cout << (_archivo.guardar(poliza, pos) ? "POLIZA MODIFICADA." : "NO SE PUDO MODIFICAR LA POLIZA.")<<endl;
                _pagoManager.eliminarVencimientosDePoliza(idPoliza);
                generarVencimientos(poliza, _plazoPoliza);
            }
            else
                cout << "EL VALOR INGRESADO ES INVALIDO.";
        }
    }
}
void PolizaManager::modificarTipoSeguro(){
    cout << "============================================" << endl;
    cout << "     MODIFICAR TIPO DE SEGURO DE POLIZA     " << endl;
    cout << "============================================" << endl;

    int nuevoTipo;
    int pos = buscarPorId();
    if (pos != -1){
        Poliza poliza = _archivo.leer(pos);
        if (poliza.getEliminado()) {
            cout << "LA POLIZA SE ENCUENTRA ELIMINADA." << endl;
            return;
        }

        int idPoliza = poliza.getId();
        if (tienePagosRealizados(idPoliza)){
            return;
        }

        cout << "INGRESE EL ID DEL NUEVO TIPO DE SEGURO: ";
        cin >> nuevoTipo;
        if (_archivoTipoSeguros.buscarID(nuevoTipo) != -1){
            poliza.setIdTipoSeguro(nuevoTipo);
            cout << (_archivo.guardar(poliza, pos) ? "POLIZA MODIFICADA." : "NO SE PUDO MODIFICAR LA POLIZA.")<<endl;
        }
        else
            cout<<"EL ID INGRESADO DEL TIPO DE SEGURO NO SE ENCONTRO.";
    }
}

void PolizaManager::listarPolizasVigentes() {
    cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||          LISTADO DE POLIZAS VIGENTES           ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    )";

    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS VIGENTES PARA MOSTRAR." << endl;
        return;
    }

    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (p.estaVigente() && !p.getEliminado())
            mostrarPoliza(p);

    }

    delete[] polizas;
}

void PolizaManager::listarPolizasNoVigentes() {
    cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||          LISTADO DE POLIZAS NO VIGENTES        ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    )";

    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS NO VIGENTES PARA MOSTRAR." << endl;
        return;
    }

    Poliza* polizas = new Poliza[cantidad]{};

    int totalPolizas = _archivo.leerTodos(polizas, cantidad);
    for (int i = 0; i < totalPolizas; i++) {
        Poliza p = polizas[i];
        if (!p.estaVigente() && !p.getEliminado())
            mostrarPoliza(p);
    }

    delete[] polizas;
}

void PolizaManager::listarPorFechaVigencia() {
    cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||  LISTADO DE POLIZAS POR FECHA DE FINALIZACION  ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    )";

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
    cout << "=============================================\n";
    cout << "                POLIZA N° " << poliza.getId() << "\n";
    cout << "=============================================\n";
    cout << "Cliente ID    : " << cliente.getIdCliente() << "\n";
    cout << "Cliente        : " << cliente.getApellido() << " " << cliente.getNombre() << "\n";
    cout << "DNI           : " << cliente.getDni() << "\n";
    cout << "Vehículo ID    : " << poliza.getIdVehiculo() << "\n";
    cout << "Patente        : " << vehiculo.getPatente() << "\n";
    cout << "Tipo Seguro    : " << tipoSeguro.getDescripcion() << "\n";
    cout << "Fecha Inicio   : " << poliza.getfechaInicio().formatoFecha() << "\n";
    cout << "Fecha Fin      : " << poliza.getfechaFin().formatoFecha() << "\n";
    cout << "Prima Mensual  : " << fixed << setprecision(2) << poliza.getPrimaMensual() << "\n";
    cout << "Suma Asegurada : " << poliza.getSumaAsegurada() << "\n";
    cout << "Eliminado      : " << (poliza.getEliminado() ? "SI" : "NO") << "\n";
    cout << "---------------------------------------------\n";

}

void PolizaManager::buscarPorDniCliente(){
    bool encontrado = false;
    string dni;
    cout << "INGRESE DNI DEL CLIENTE: ";
    dni = cargarCadena();
    int posCliente = _clienteManager.posClientePorDNI(dni);

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
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS PARA PODER GENERAR EL REPORTE." << endl;
        return;
    }
    cout << "INGRESE FECHA DE INICIO DEL PERIODO DEL REPORTE:" << endl;
    Fecha fechaDesde= leerFechaValida();
    if (fechaDesde.getAnio() == -1){
        cout << "SE CANCELA LA OPERACION." << endl;
        return;
    }

    cout << "INGRESE FECHA DE FIN DEL PERIODO DEL REPORTE:" << endl;
    Fecha fechaHasta= leerFechaValida();
    if (fechaHasta.getAnio() == -1){
        cout << "SE CANCELA LA OPERACION." << endl;
        return;
    }

    if (fechaDesde > fechaHasta){
        cout << "LA FECHA INICIAL NO PUEDE SER MAYOR A LA FECHA FINAL." << endl;
        return;
    }

    if (fechaDesde.getAnio() <2025 || fechaDesde.getAnio() > 2026 || fechaHasta.getAnio() <2025 || fechaHasta.getAnio() > 2026){
        cout << "LAS FECHAS INGRESADAS DEBEN ESTAR ENTRE 2025 Y 2026." << endl;
        return;
    }

    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);

    int cantidadFiltradas = cantidadPolizasPeriodo(polizas, cantidad, fechaDesde, fechaHasta);
    if (cantidadFiltradas == 0) {
        cout << "NO SE ENCONTRARON POLIZAS VIGENTES Y VENCIDAS A LA FECHA INDICADA." << endl;
        delete [] polizas;
        return;
    }

    int cantidadSeguros = _archivoTipoSeguros.getCantidadRegistros();
    TipoSeguro* tiposSeguros = new TipoSeguro[cantidadSeguros]{};
    _archivoTipoSeguros.leerTodos(tiposSeguros, cantidadSeguros);

    Poliza** polizasFiltradas = new Poliza*[cantidadFiltradas]{};
    filtrarPolizasPorFecha(polizas, polizasFiltradas, cantidad, fechaDesde, fechaHasta);
    Fecha fechaActual;

    system("cls");

     cout << R"(
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    ||  REPORTE DE POLIZAS POR TIPO DE SEGURO         ||
    ||||||||||||||||||||||||||||||||||||||||||||||||||||
    )"<< endl;

    cout << "======================================================"<< endl;
    cout << "REPORTE REALIZADO EL: " << fechaActual.formatoFecha() << endl;
    cout << "REPORTE DE POLIZAS DESDE: " << fechaDesde.formatoFecha() << " HASTA: " << fechaHasta.formatoFecha() << endl;
    cout << "CANTIDAD DE POLIZAS PROCESADAS EN EL PERIODO: " << cantidadFiltradas <<endl;

    cout << left << setw(34) << "TIPO DE SEGURO"
     << right << setw(10) << "VIGENTES"
     << setw(10) << "CON DEUDA" << endl;
    cout << "======================================================"<< endl;
    int totalVigentes = 0;
    int totalVencidas = 0;

    for (int i=0; i < cantidadSeguros; i++) {
        TipoSeguro tipoSeguro = tiposSeguros[i];
        if (tipoSeguro.getEliminado()) {
            continue;
        }
        int contadorVigentes = 0;
        int contadorVencidas = 0;

        for (int j=0; j < cantidadFiltradas; j++) {
            Poliza* poliza = polizasFiltradas[j];
            if (poliza->getIdTipoSeguro() == tipoSeguro.getId() && !poliza->getEliminado()) {
                if (poliza->estaVigente())
                    contadorVigentes++;
                if (!tieneCobertura(*poliza))
                    contadorVencidas++;

            }
        }
        totalVigentes += contadorVigentes;
        totalVencidas += contadorVencidas;

        cout << left  << setw(34) << tipoSeguro.getDescripcion()
         << right << setw(10) << contadorVigentes
         << setw(10) << contadorVencidas << endl;
    }

    cout << "======================================================" << endl;
    cout << left  << setw(34) << "TOTAL"
         << right << setw(10) << totalVigentes
         << setw(10) << totalVencidas << endl;

    delete [] polizas;
    delete [] polizasFiltradas;
    delete [] tiposSeguros;
}

int PolizaManager::cantidadPolizasPeriodo(Poliza polizas[],int cantidadPolizas, Fecha fechaDesde, Fecha fechaHasta){
    int contador = 0;
    for (int i = 0; i < cantidadPolizas; i++) {
        Fecha inicio = polizas[i].getfechaInicio();
        Fecha fin = polizas[i].getfechaFin();
        if (!polizas[i].getEliminado() && fin >= fechaDesde && inicio <= fechaHasta) {
            contador++;
        }
    }
    return contador;
}

void PolizaManager::filtrarPolizasPorFecha(Poliza polizas[], Poliza* polizasFiltradas[], int cantidadPolizas,Fecha fechaDesde, Fecha fechaHasta){
    int indiceFiltrado = 0;
    for (int i = 0; i < cantidadPolizas; i++) {
        Fecha inicio = polizas[i].getfechaInicio();
        Fecha fin = polizas[i].getfechaFin();
        if (!polizas[i].getEliminado() && fin >= fechaDesde && inicio <= fechaHasta) {
            polizasFiltradas[indiceFiltrado] = &polizas[i];
            indiceFiltrado++;
        }
    }
}

void PolizaManager::generarVencimientos(Poliza poliza, int cantidadVencimientos) {
    VencimientosArchivo _archivoVencimientos;

    for (int i = 0; i < cantidadVencimientos; i++) {
        Fecha fechaVencimiento = poliza.getfechaInicio();
        fechaVencimiento.sumarMes(i);

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

bool PolizaManager::tienePolizasVigentes(int idVehiculo) {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        return false;
    }

    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);

    for (int i = 0; i < cantidad; i++) {
        Poliza p = polizas[i];
        if (p.getIdVehiculo() == idVehiculo && p.estaVigente() && !p.getEliminado()) {
            delete[] polizas;
            return true;
        }
    }
    delete[] polizas;
    return false;
}

void PolizaManager::reportePolizasSinCobertura() {
    int cantidad = _archivo.getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY POLIZAS REGISTRADAS, NO ES POSIBLE REALIZAR EL REPORTE." << endl;
        return;
    }
    cout << "INGRESE FECHA DE INICIO DEL PERIODO DEL REPORTE:" << endl;
    Fecha fechaDesde= leerFechaValida();
    if (fechaDesde.getAnio() == -1){
        cout << "SE CANCELA LA OPERACION." << endl;
        return;
    }

    cout << "INGRESE FECHA DE FIN DEL PERIODO DEL REPORTE:" << endl;
    Fecha fechaHasta= leerFechaValida();
    if (fechaHasta.getAnio() == -1){
        cout << "SE CANCELA LA OPERACION." << endl;
        return;
    }

    if (fechaDesde > fechaHasta){
        cout << "LA FECHA INICIAL NO PUEDE SER MAYOR A LA FECHA FINAL." << endl;
        return;
    }

    if (fechaDesde.getAnio() <2025 || fechaDesde.getAnio() > 2026 || fechaHasta.getAnio() <2025 || fechaHasta.getAnio() > 2026){
        cout << "LAS FECHAS INGRESADAS DEBEN ESTAR ENTRE 2025 Y 2026." << endl;
        return;
    }

    int cantidadVencimientos = _archivoVencimientos.getCantidadRegistros();
    if (cantidadVencimientos == 0) {
        cout << "NO HAY VENCIMIENTOS REGISTRADOS, NO ES POSIBLE REALIZAR EL REPORTE." << endl;
        return;
    }

    Poliza* polizas = new Poliza[cantidad]{};
    _archivo.leerTodos(polizas, cantidad);

    int cantidadFiltradas = cantidadPolizasPeriodo(polizas, cantidad, fechaDesde, fechaHasta);
    if (cantidadFiltradas == 0) {
        cout << "NO SE ENCONTRARON POLIZAS EN EL PERIODO INGRESADO." << endl;
        delete [] polizas;
        return;
    }
    Fecha fechaActual;
    system("cls");

    cout << "============================================================" << endl;
    cout << "      REPORTE DE POLIZAS SIN COBERTURA EN UN PERIODO        " << endl;
    cout << "============================================================" << endl;
    cout << "REPORTE REALIZADO EL: " << fechaActual.formatoFecha() << endl;
    cout << "============================================================" << endl;
    cout << "CANTIDAD DE POLIZAS FILTRADAS: " << cantidadFiltradas << endl;
    cout << "============================================================" << endl;
    cout << "REPORTE DE POLIZAS DESDE: " << fechaDesde.formatoFecha() << " HASTA: " << fechaHasta.formatoFecha() << endl;
    cout << "============================================================" << endl;

    Poliza** polizasFiltradas = new Poliza*[cantidadFiltradas]{};
    filtrarPolizasPorFecha(polizas, polizasFiltradas, cantidad, fechaDesde, fechaHasta);


    Vencimiento * vencimientos = new Vencimiento[cantidadVencimientos]{};
    _archivoVencimientos.leerTodos(vencimientos, cantidadVencimientos);

    for (int i = 0; i < cantidadFiltradas; i++) {
        Poliza p = *polizasFiltradas[i];
        if (!p.getEliminado()) {
            for (int j = 0; j < cantidadVencimientos; j++) {
                Vencimiento v = vencimientos[j];
                if (!v.getEliminado() && !v.getPagado() && v.estaVencido() && v.getIdPoliza() == p.getId()) {
                    mostrarPoliza(p);
                    break;
                }
            }
        }
    }

    delete[] vencimientos;
    delete[] polizasFiltradas;
    delete[] polizas;
}


bool PolizaManager::tieneCobertura(Poliza p) {
    int cantidadVencimientos = _archivoVencimientos.getCantidadRegistros();
    if (cantidadVencimientos == 0) {
        cout << "NO HAY VENCIMIENTOS REGISTRADOS." << endl;
        return false;
    }

    Vencimiento* vencimientos = new Vencimiento[cantidadVencimientos]{};
    _archivoVencimientos.leerTodos(vencimientos, cantidadVencimientos);

    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    Pago* pagos = new Pago[cantidadPagos]{};
    _archivoPagos.leerTodos(pagos, cantidadPagos);

    for (int i = 0; i < cantidadVencimientos; i++) {
        Vencimiento v = vencimientos[i];
        if (!v.getEliminado() && v.getIdPoliza() == p.getId()) {
            if (v.estaVencido()) {
                bool tienePago = false;
                for (int j = 0; j < cantidadPagos; j++) {
                    Pago pago = pagos[j];
                    if (pago.getIdVencimiento() == v.getId() && !pago.getEliminado()) {
                        tienePago = true;
                        break;
                    }
                }
                if (!tienePago) {
                    delete[] pagos;
                    delete[] vencimientos;
                    return false;
                }
            }
        }
    }

    delete[] pagos;
    delete[] vencimientos;
    return true;
}

void PolizaManager::consultarVencimientosDePoliza(){
    cout << "============================================" << endl;
    cout << "        VENCIMIENTOS DE POLIZA POR ID       " << endl;
    cout << "============================================" << endl;
    int pos = buscarPorId();
    if (pos != -1 ){
        Poliza poliza = _archivo.leer(pos);
        if (poliza.getEliminado()) {
            cout << "LA POLIZA SE ENCUENTRA ELIMINADA." << endl;
            return;
        }

        int cantidadVencimientos = _archivoVencimientos.getCantidadRegistros();
        if (cantidadVencimientos == 0) {
            cout << "NO HAY VENCIMIENTOS REGISTRADOS." << endl;
            system("pause");
            return;
        }

        Vencimiento* vencimientos = new Vencimiento[cantidadVencimientos]{};
        _archivoVencimientos.leerTodos(vencimientos, cantidadVencimientos);

        for (int i=0; i<cantidadVencimientos; i++){
            Vencimiento vencimiento = vencimientos[i];
            if (!vencimiento.getEliminado() && (vencimiento.getIdPoliza() == poliza.getId())){
                cout << "ID VENCIMIENTO: " << vencimiento.getId() << endl;
                cout << "ID POLIZA: " << vencimiento.getIdPoliza() << endl;
                cout << "FECHA DE VENCIMIENTO: " << vencimiento.getVencimiento().formatoFecha() << endl;
                cout << "MONTO A PAGAR: " << vencimiento.getMonto() << endl;
                cout << "ESTADO: " << (vencimiento.getPagado() ? "PAGADO" : "NO PAGADO") << endl;
                cout << "----------------------------------------" << endl;
            }
        }

        delete[] vencimientos;
    }
}

bool PolizaManager::tienePagosRealizados(int idPoliza) {
    int cantidadPagos = _pagoManager.cantidadPagosPorPoliza(idPoliza);

    if (cantidadPagos > 0) {
        cout << "LA POLIZA TIENE PAGOS REGISTRADOS, DEBE ELIMINARLOS PRIMERO." << endl;
        return true;
    }

    return false;
}

int PolizaManager::mostrarOpcionesDeSeguro() {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||          SELECCIONE UN SEGURO         ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||     1 - BASICO RESPONSABILIDAD CIVIL  ||" << endl;
    cout << "||     2 - CONTRA TERCEROS COMPLETO      ||" << endl;
    cout << "||     3 - TODO RIESGO                   ||" << endl;
    cout << "||     4 - CONTRA ROBO E INCENDIO        ||" << endl;
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

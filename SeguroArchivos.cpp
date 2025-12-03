#include <iostream>
#include "SeguroArchivo.h"
#include "utils.h"

using namespace std;


SeguroArchivo::SeguroArchivo(std::string nombreArchivo)
: nombreArchivo(nombreArchivo) {
    cargarPorcentajes();
}

bool SeguroArchivo::guardar(Seguro registro) {
    FILE *archivo_seguro = fopen(nombreArchivo.c_str(), "ab");
    if (archivo_seguro == nullptr) {
        return false;
    }
    bool guardado = fwrite(&registro, sizeof(Seguro), 1, archivo_seguro);
    fclose(archivo_seguro);
    return guardado;
}

int SeguroArchivo::buscarIdSeguro(int id) {
    FILE *archivo_seguro = fopen(nombreArchivo.c_str(), "rb");
    if (archivo_seguro == nullptr) {
        return -2;
    }
    Seguro registro;
    int posicion = 0;
    while (fread(&registro, sizeof(Seguro), 1, archivo_seguro) == 1) {
        if (registro.getId() == id) {
            fclose(archivo_seguro);
            return posicion;
        }
        posicion++;
    }
    fclose(archivo_seguro);
    return -1;
}

Seguro SeguroArchivo::leer(int pos) {
    FILE *archivo_seguro = fopen(nombreArchivo.c_str(), "rb");
    if (archivo_seguro == nullptr) {
        return Seguro();
    }
    Seguro registro;
    fseek(archivo_seguro, pos * sizeof(Seguro), SEEK_SET);
    fread(&registro, sizeof(Seguro), 1, archivo_seguro);
    fclose(archivo_seguro);
    return registro;
}

int SeguroArchivo::leerTodos(Seguro seguro[], int cantidad) {
    FILE *archivo_seguro = fopen(nombreArchivo.c_str(), "rb");
    if (archivo_seguro == nullptr) {
        return 0;
    }
    int result = fread(seguro, sizeof(Seguro), cantidad, archivo_seguro);
    fclose(archivo_seguro);
    return result;
}

int SeguroArchivo::getCantidadRegistros() {
    int cantidad = 0;
    FILE *archivo_seguro = fopen(nombreArchivo.c_str(), "rb");
    if (archivo_seguro == nullptr) {
        return cantidad;
    }
    fseek(archivo_seguro, 0, SEEK_END);
    cantidad = ftell(archivo_seguro) / sizeof(Seguro);
    fclose(archivo_seguro);
    return cantidad;
}

int SeguroArchivo::getIdSeguroUltimo() {
    return getCantidadRegistros() + 1;
}

bool SeguroArchivo::eliminar(int id) {
    int pos = buscarIdSeguro(id);
    if (pos == -1) {
        return false;
    }
    Seguro registro = leer(pos);
    registro.setEliminado(true);
    return actualizarRegistro(pos, registro);
}

bool SeguroArchivo::actualizarRegistro(int pos, Seguro registro) {
    FILE *archivo_seguro = fopen(nombreArchivo.c_str(), "rb+");
    if (archivo_seguro == nullptr) {
        return false;
    }
    fseek(archivo_seguro, pos * sizeof(Seguro), SEEK_SET);
    bool actualizacion = fwrite(&registro, sizeof(Seguro), 1, archivo_seguro);
    fclose(archivo_seguro);
    return actualizacion;
}

bool SeguroArchivo::recuperar(int id) {
    int pos = buscarIdSeguro(id);
    if (pos == -1) {
        return false;
    }
    Seguro registro = leer(pos);
    registro.setEliminado(false);
    return actualizarRegistro(pos, registro);
}


void SeguroArchivo::cargarSeguro() {
    int id = getIdSeguroUltimo();
    float valorPoliza, sumaAsegurada;
    cout << "ID DEL SEGURO: "<<id<<endl;
    cout << "INGRESE NOMBRE DEL SEGURO: ";
    string nombre = cargarCadena();
    cout << "INGRESE VALOR DE LA POLIZA: ";
    cin >> valorPoliza;
    cout << "INGRESE VALOR DE LA SUMA ASEGURADA MAXIMA: ";
    cin >> sumaAsegurada;
    Seguro nuevoSeguro(id, sumaAsegurada, nombre, valorPoliza, false);
    if (guardar(nuevoSeguro)) {
        cout << "SEGURO CARGADO CORRECTAMENTE." << endl;
    }
    else {cout << "ERROR!." << endl;}
}



void SeguroArchivo::mostrarMenu() {
    int opcion;
    do {
        system("cls");
        cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||             MENU SEGUROS              ||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "||     1 - CARGAR SEGURO                 ||" << endl;
        cout << "||     2 - MOSTRAR TODOS LOS SEGUROS     ||" << endl;
        cout << "||     3 - MODIFICAR NOMBRE DE POLIZA    ||" << endl;
        cout << "||     4 - MODIFICAR VALOR DE POLIZA     ||" << endl;
        cout << "||     5 - MODIFICAR VALOR SUMA ASEGURADA||" << endl;
        cout << "||     6 - CONFIGURAR PORCENTAJES        ||" << endl;
        cout << "||---------------------------------------||" << endl;
        cout << "||     0 - VOLVER                        ||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
        system("cls");
        switch(opcion) {
            case 1: cargarSeguro(); system("pause"); break;
            case 2: mostrarSeguros(); system("pause"); break;
            case 3: modificarNombrePoliza(); system("pause"); break;
            case 4: modificarValorPoliza(); system("pause"); break;
            case 5: modificarSumaAsegurada(); break;
            case 6: configurarPorcentajes(); break;
            case 0: break;
            default: cout << "OPCION INCORRECTA..." << endl; system("pause"); break;
        }
    } while(opcion != 0);
}


void SeguroArchivo::mostrarLista(Seguro seguro, bool mostrar) {
    if (!seguro.getEliminado()) {
        cout << "ID DEL SEGURO: " << seguro.getId() << endl;
        cout << "NOMBRE: " << seguro.getNombre() << endl;
        cout << "VALOR DE POLIZA: $" << seguro.getValorPoliza() << endl;
        if (mostrar) {
            cout << "SUMA ASEGURADA MAXIMA: $" << seguro.getSumaAsegurada() << endl;
        }
        cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    }
}


void SeguroArchivo::mostrarSeguros() {
    int cantidad = getCantidadRegistros();
    Seguro seguro;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" <<endl;
    cout << "||                SEGUROS                ||" <<endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" <<endl;
    for (int i = 0; i < cantidad; ++i) {
        seguro = leer(i);
        if (!seguro.getEliminado()) {
            mostrarLista(seguro, true);
        }
    }
}

void SeguroArchivo::modificarValorPoliza() {
    int id;
    cout << "INGRESE EL ID DEL SEGURO A MODIFICAR: ";
    cin >> id;
    int pos = buscarIdSeguro(id);
    if (pos == -1) {
        cout << "SEGURO NO ENCONTRADO." << endl;
        return;
    }
    Seguro seguro = leer(pos);
    cout << "|||||||||||||||||||||||||||||||||||||||||||" <<endl;
    mostrarLista(seguro, false);
    float nuevoValor;
    cout << "INGRESE NUEVO VALOR DE POLIZA: ";
    cin >> nuevoValor;
    seguro.setValorPoliza(nuevoValor);
    if (actualizarRegistro(pos, seguro)) {
        cout << "VALOR ACTUALIZADO CORRECTAMENTE." << endl;
    }
    else {
        cout << "NO SE PUDO MODIFICAR EL VALOR DE POLIZA." << endl;
    }
}

void SeguroArchivo::modificarNombrePoliza() {
    int id;
    cout << "INGRESE EL ID DEL SEGURO A MODIFICAR: ";
    cin >> id;
    int pos = buscarIdSeguro(id);
    if (pos == -1) {
        cout << "SEGURO NO ENCONTRADO." << endl;
        return;
    }
    Seguro seguro = leer(pos);
    cout << "|||||||||||||||||||||||||||||||||||||||||||" <<endl;
    mostrarLista(seguro, false);
    cout << "INGRESE NUEVO NOMBRE DE POLIZA: ";
    string nuevoNombre = cargarCadena();
    if (cortarSiCero(nuevoNombre)) return;
    seguro.setNombre(nuevoNombre);
    if (actualizarRegistro(pos, seguro)) {
        cout << "NOMBRE ACTUALIZADO CORRECTAMENTE." << endl;
    }
    else {
        cout << "NO SE PUDO MODIFICAR EL NOMBRE DE POLIZA." << endl;
    }
}


void SeguroArchivo::modificarSumaAsegurada() {
    int id;
    cout << "INGRESE EL ID DEL SEGURO A MODIFICAR: ";
    cin >> id;
    int pos = buscarIdSeguro(id);
    if (pos == -1) {
        cout << "SEGURO NO ENCONTRADO." << endl;
        return;
    }
    Seguro seguro = leer(pos);
    cout << "|||||||||||||||||||||||||||||||||||||||||||" <<endl;
    mostrarLista(seguro, true);
    float nuevoValor;
    cout << "INGRESE NUEVO VALOR DE LA SUMA ASEGURADA MAXIMA: ";
    cin>>nuevoValor;
    if (0 == nuevoValor) return;
    seguro.setSumaAsegurada(nuevoValor);
    if (actualizarRegistro(pos, seguro)) {
        cout << "SUMA ASEGURADA ACTUALIZADO CORRECTAMENTE." << endl;
    }
    else {
        cout << "NO SE PUDO MODIFICAR LA SUMA ASEGURADA DE POLIZA." << endl;
    }
}

int SeguroArchivo::seleccionarSeguro() {
    int cantidad = getCantidadRegistros();
    if (cantidad == 0) {
        cout << "NO HAY SEGUROS CARGADOS." << endl;
        return -1;
    }
    cout << "|||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||           SEGUROS DISPONIBLES           ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||" << endl;
    int *pos = new int[cantidad];
    int opcionesMostradas = 0;
    for (int i = 0; i < cantidad; ++i) {
        Seguro seguro = leer(i);
        cout << "|| " << (opcionesMostradas + 1) << " - "<< alinearIzquierda(seguro.getNombre(), 36) << "||" << endl;
        pos[opcionesMostradas] = i;
        opcionesMostradas++;
    }
    cout << "||-----------------------------------------||" << endl;
    cout << "||     0   - CANCELAR                      ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    while (opcion < 0 || opcion > opcionesMostradas) {
        cout << "OPCION INCORRECTA..." << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;
    }
    int resultado;
    if (opcion == 0) {
        resultado = -1;
    }
    else {
        int posicionReal = pos[opcion - 1];
        resultado = leer(posicionReal).getId();
    }

    delete[] pos;
    return resultado;
}



const int CANTIDAD_OPCIONES = 11;
string nombresPorcentaje[CANTIDAD_OPCIONES] = {"MOTO", "AUTOMOVIL", "CAMIONETA", "COLECTIVO", "REMOLQUE",
    "PARTICULAR", "COMERCIAL", "CARGA", "SERVICIO PUBLICO", "EMERGENCIA", "ALQUILER"
};
float porcentajes[CANTIDAD_OPCIONES] = {};


void SeguroArchivo::configurarPorcentajes() {
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||      AJUSTE DE PORCENTAJES SEGUN      ||" << endl;
    cout << "||           CATEGORIA Y USO             ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "---------------------------------------" << endl;
    cout << "       PORCENTAJE POR CATEGORIA        " << endl;
    cout << "---------------------------------------" << endl;
    bool m = true;
    for (int i = 0; i < CANTIDAD_OPCIONES; i++) {
        if (i==5 && m) {
            m=false;
            cout << "---------------------------------------" << endl;
            cout << "          PORCENTAJE POR USO           " << endl;
            cout << "---------------------------------------" << endl;
        }
        cout << (i+1) << ") " << nombresPorcentaje[i] << ": " << porcentajes[i] << "%" << endl;
    }
    cout << "---------------------------------------" << endl;
    cout << "0) CANCELAR" << endl;
    cout << "SELECCIONE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    if (opcion == 0) return;
    if (opcion > 0 && opcion <= CANTIDAD_OPCIONES) {
        cout << "INGRESE EL NUEVO PORCENTAJE PARA " << nombresPorcentaje[opcion-1] << ": ";
        float nuevoPorcentaje;
        cin >> nuevoPorcentaje;
        porcentajes[opcion-1] = nuevoPorcentaje;
        guardarPorcentajes();
        cout << "PORCENTAJE ACTUALIZADO Y GUARDADO." << endl;
    } else {
        cout << "OPCION INCORRECTA." << endl;
    }
    system("pause");
}


float SeguroArchivo::calcularValorPoliza(int idSeguro, Vehiculo vehiculo) {
    int pos = buscarIdSeguro(idSeguro);
    if (pos == -1) {
            cout << "POLIZA NO ENCONTRADA." << endl;
            return 0;
    }
    Seguro seguro = leer(pos);
    float porcentaje = 0;
    bool categoriaEncontrada = false;
    bool usoEncontrado = false;
    for (int i = 0; i < CANTIDAD_OPCIONES; i++) {
        if (nombresPorcentaje[i] == vehiculo.getCategoria()){
            porcentaje += float(porcentajes[i]) /100;
            categoriaEncontrada=true;
            break;
            }
        }
    for (int i = 0; i < CANTIDAD_OPCIONES; i++) {
        if (nombresPorcentaje[i] == vehiculo.getUso()) {
            porcentaje += float(porcentajes[i]) / 100;
            usoEncontrado = true;
            break;
        }
    }
    if (!categoriaEncontrada || !usoEncontrado) {
        cout << "CATEGORIA O USO NO VALIDO." << endl;
        return 0;
    }
    float valorBase = seguro.getValorPoliza();
    return valorBase * (1 + porcentaje);
}



float SeguroArchivo::calcularSumaAsegurada(int idSeguro, Vehiculo vehiculo) {
    int pos = buscarIdSeguro(idSeguro);
    if (pos == -1) {
        cout << "SEGURO NO ENCONTRADO." << endl;
        return 0;
    }
    Seguro seguro = leer(pos);
    return seguro.getSumaAsegurada();
    int indice = -1;
    for (int i = 0; i < CANTIDAD_OPCIONES; i++) {
        if (nombresPorcentaje[i] == vehiculo.getCategoria()) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        for (int i = 0; i < CANTIDAD_OPCIONES; i++) {
            if (nombresPorcentaje[i] == vehiculo.getUso()) {
                indice = i;
                break;
            }
        }
    }
    if (indice == -1) {
        cout << "CATEGORIA O USO NO VALIDO." << endl;
        return 0;
    }
    float porcentaje=porcentajes[indice]/ 100.0;
    float sumaBase=seguro.getSumaAsegurada();
    float sumaFinal=sumaBase *porcentaje;
    if (vehiculo.getAnio() < 2010) {sumaFinal-= 100000;}
    else if (vehiculo.getAnio() < 2015) {sumaFinal -= 50000;}
    else if (vehiculo.getAnio() < 2020) {sumaFinal -= 20000;}
    if (sumaFinal < 0) sumaFinal = 0;
    return sumaFinal;
}


void SeguroArchivo::cargarPorcentajes() {
    FILE* archivo = fopen("Porcentajes.dat", "rb");
    if (archivo == nullptr) {
        for (int i = 0; i < CANTIDAD_OPCIONES; i++) porcentajes[i] = 0.0;
        return;
    }
    fread(porcentajes, sizeof(float), CANTIDAD_OPCIONES, archivo);
    fclose(archivo);
}


void SeguroArchivo::guardarPorcentajes() {
    FILE* archivo = fopen("Porcentajes.dat", "wb");
    if (archivo == nullptr) {
        cout << "NO SE PUDO GUARDAR LOS PORCENTAJES." << endl;
        return;
    }
    fwrite(porcentajes, sizeof(float), CANTIDAD_OPCIONES, archivo);
    fclose(archivo);
}

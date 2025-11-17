#include "LocalidadArchivo.h"
#include <iostream>

#include "utils.h"
using namespace std;

LocalidadArchivo::LocalidadArchivo(): _nombreArchivo("Localidades.dat") {

}

LocalidadArchivo::LocalidadArchivo(string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {
}

bool LocalidadArchivo::guardar(Localidad registro) {
    bool result;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "ab");
    if (pFile == nullptr) {
        return false;
    }
    result = fwrite(&registro, sizeof(Localidad), 1, pFile);

    fclose(pFile);
    return result;
}


Localidad LocalidadArchivo::leer(int pos) {
    Localidad registro;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        registro.getCodigoPostal();
        return registro;
    }
    fseek(pFile, sizeof(Localidad) * pos, SEEK_SET);
    fread(&registro, sizeof(Localidad), 1, pFile);

    fclose(pFile);
    return registro;
}


int LocalidadArchivo::leerTodos(Localidad registros[], int cantidad) {
    int result;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        return 0;
    }
    result = fread(registros, sizeof(Localidad), cantidad, pFile);

    fclose(pFile);
    return result;
}


int LocalidadArchivo::getCantidadRegistros() {
    int cantidad;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        return 0;
    }
    fseek(pFile, 0, SEEK_END);

    cantidad = ftell(pFile) / sizeof(Localidad);
    fclose(pFile);

    return cantidad;
}

int LocalidadArchivo::getUltimoID() {
    return getCantidadRegistros() + 1;
}

int LocalidadArchivo::buscarPorCodigoPostal(int codigoPostal) {
    Localidad registro;
    int pos = -1;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        return pos;
    }
    while (fread(&registro, sizeof(Localidad), 1, pFile)) {
        if (registro.getCodigoPostal() == codigoPostal) {
            pos = ftell(pFile) / sizeof(Localidad) - 1;
            break;
        }
    }

    fclose(pFile);
    return pos;
}

void LocalidadArchivo::mostrarLocalidad(Localidad loc) {
    cout << loc.getIDLocalidad()<< " | "
         << loc.getCodigoPostal()<< " | "
         << loc.getPartido() << " | "
         << loc.getLocalidad() << endl;
}


void LocalidadArchivo::mostrar() {
    const int cantidad = getCantidadRegistros();
    Localidad* vLocalidad = new Localidad[getCantidadRegistros()];

    if (vLocalidad == nullptr) {
        cout << "No se pudo asignar memoria..." << endl;
        exit(1);
    }

    leerTodos(vLocalidad, cantidad);
    cout << "ID |  C.P  |    PARTIDO   |   LOCALIDAD " << endl;
    for (int i = 0; i < cantidad; i++) {
        mostrarLocalidad(vLocalidad[i]);
    }
    delete[] vLocalidad;
}


int LocalidadArchivo::listarPorCodigoPostal(int codigoPostal, Localidad coincidencias[], int max) {
    Localidad reg;
    int c = 0;
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return 0;

    while (fread(&reg, sizeof(Localidad), 1, pFile) && c < max) {
        if (reg.getCodigoPostal() == codigoPostal) {
            coincidencias[c++] = reg;
        }
    }
    fclose(pFile);
    return c;
}


Localidad LocalidadArchivo::pedirLocalidadPorCodigoPostal() {
    int codigoPostal;
    cout << "INGRESE EL CODIGO POSTAL: ";
    cin >> codigoPostal;
    int pos = buscarPorCodigoPostal(codigoPostal);
    if (pos == -1) {
        cout << "NO HAY CORBERTURA CON ESE CODIGO POSTAL." << endl;
        return Localidad();
    }
    return leer(pos);
}

Localidad LocalidadArchivo::pedirLocalidadPorCodigoPostalInteractivo() {
    int codigoPostal;
    cout << "INGRESE EL CODIGO POSTAL: ";
    cin >> codigoPostal;

    Localidad coincidencias[20];
    int cantCoincidencias = buscarCoincidenciasPorCodigoPostal(codigoPostal, coincidencias, 20);

    if (cantCoincidencias == 0) {
        cout << "NO HAY CORBERTURA CON ESE CODIGO POSTAL." << endl;
        return Localidad();
    } else if (cantCoincidencias == 1) {
        return coincidencias[0];
    } else {
        mostrarOpcionesLocalidad(coincidencias, cantCoincidencias);
        int opcion;
        cout << "INGRESE UNA DE LA OPCIONES: ";
        cin >> opcion;
        if (opcion < 1 || opcion > cantCoincidencias) {
            cout << "OPCION INCORRECTA." << endl;
            return Localidad();
        }
        return coincidencias[opcion-1];
    }
}


int LocalidadArchivo::buscarCoincidenciasPorCodigoPostal(int codigoPostal, Localidad coincidencias[], int maxCoincidencias) {
    int cant = getCantidadRegistros();
    Localidad *vecLocalidad = new Localidad[cant];
    leerTodos(vecLocalidad, cant);
    int cantCoincidencias = 0;
    for (int i = 0; i < cant; i++) {
        if (vecLocalidad[i].getCodigoPostal() == codigoPostal) {
            bool esta = false;
            for (int j = 0; j < cantCoincidencias; j++) {
                if (coincidencias[j].getLocalidad() == vecLocalidad[i].getLocalidad() &&
                    coincidencias[j].getPartido() == vecLocalidad[i].getPartido()) {
                    esta = true;
                    break;
                }
            }
            if (!esta && cantCoincidencias < maxCoincidencias) {
                coincidencias[cantCoincidencias++] = vecLocalidad[i];
            }
        }
    }
    delete[] vecLocalidad;
    return cantCoincidencias;
}


void LocalidadArchivo::mostrarOpcionesLocalidad(Localidad coincidencias[], int cantCoincidencias) {
    cout << "ELIJA SU LOCALIDAD: " << endl;
    cout << "OPCION |       PARTIDO       |        LOCALIDAD" << endl;
    for (int i = 0; i < cantCoincidencias; i++) {
        cout << i+1 << "| " << coincidencias[i].getPartido()
                  << " - " << coincidencias[i].getLocalidad() << endl;
    }
}

bool LocalidadArchivo::existeLocalidad( Localidad loc) {
    int cantidad = getCantidadRegistros();
    Localidad* registros = new Localidad[cantidad];
    leerTodos(registros, cantidad);

    for (int i = 0; i < cantidad; i++) {
        if (registros[i] == loc) {
            delete[] registros;
            return true;
        }
    }
    delete[] registros;
    return false;
}

void LocalidadArchivo::cargarLocalidad() {
    int codigoPostal;
    int id = getCantidadRegistros() + 1;

    cout << "|||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||        CARGAR LOCALIDAD         ||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||" << endl;
    cout << "ID: " << id << endl;
    cout << "INGRESE CODIGO POSTAL: ";
    cin >> codigoPostal;
    cin.ignore();
    cout << "INGRESE NOMBRE DE LA LOCALIDAD: ";
    string localidad = cargarCadena();
    cout << "INGRESE PARTIDO: ";
    string partido = cargarCadena();
    Localidad reg(id, codigoPostal, localidad, partido);
    if (existeLocalidad(reg)) {
        cout << "YA EXISTE UN REGISTRO IGUAL." << endl;
        return;
    }
    if (guardar(reg)) {
        cout << "SE GUARDO CORRECTAMENTE" << endl;
    } else {
        cout << "ERROR!" << endl;
    }
}


int LocalidadArchivo::partidosUnicos(string partidos[], int maxPartidos) {
    int cant = getCantidadRegistros();
    Localidad *localidades = new Localidad[cant];
    leerTodos(localidades, cant);
    int partidosUsados = 0;
    for (int i = 0; i < cant; ++i) {
        string partido = localidades[i].getPartido();
        bool existe = false;
        for (int j = 0; j < partidosUsados; ++j) {
            if (partidos[j] == partido) {
                existe = true;
                break;
            }
        }
        if (!existe && partidosUsados < maxPartidos) {
            partidos[partidosUsados++] = partido;
        }
    }
    delete[] localidades;
    return partidosUsados;
}
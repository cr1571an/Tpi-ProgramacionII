#include "PolizaManager.h"
#include "PolizaArchivo.h"
#include "utils.h"
#include <iostream>
using namespace std;

PolizaManager::PolizaManager()
    : _archivo("Polizas.dat"), _vehiculoManager() {
}

void PolizaManager::mostrar() {
    int cantidad = _archivo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Poliza p = _archivo.leer(i);
        if (!p.getEliminado()) {
            cout << "ID: " << p.getId() << ", Cliente: " //TODO: Obtener dato Cliente.
                 << ", Vehiculo: " << p.getIdVehiculo()
                 << ", Seguro: " << p.getTipoSeguro()
                 << ", Vigente: " << (p.getVigente() ? "Sí" : "No") << endl;
        }
    }
}


void PolizaManager::cargar() {
    string patente;
    cout << "Ingrese patente del vehiculo: ";
    cin >> patente;
    int idVehiculo = _vehiculoManager.buscarIdPorPatente(patente);
    if (idVehiculo != -1) {
        int id = _archivo.getNuevoID();
        Fecha inicio, fin;
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


void PolizaManager::eliminar(int id) {
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Poliza p = _archivo.leer(pos);
        p.setEliminado(true);
        FILE* f = fopen("Polizas.dat", "rb+");
        fseek(f, pos * sizeof(Poliza), SEEK_SET);
        fwrite(&p, sizeof(Poliza), 1, f);
        fclose(f);
        cout << "Poliza eliminada." << endl;
    } else {
        cout << "No se encontró la poliza." << endl;
    }
}

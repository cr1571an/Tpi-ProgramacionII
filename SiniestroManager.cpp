#include "SiniestroManager.h"
#include <iostream>
using namespace std;
#include "utils.h"

SiniestroManager::SiniestroManager()
    : _archivo("Siniestros.dat") {
}

void SiniestroManager::mostrar() {
    int cantidad = _archivo.getCantidadRegistros();
    for (int i = 0; i < cantidad; i++) {
        Siniestro s = _archivo.leer(i);
        if (!s.getEliminado()) {
            cout << "ID: " << s.getId() << ", Poliza: " << s.getIdPoliza()
                 << ", Tipo: " << s.getTipoSiniestro()
                 << ", Costo: $" << s.getCostoEstimado() << endl;
        }
    }
}


void SiniestroManager::cargar(int idPoliza) {
    int id = _archivo.getNuevoID();
    Fecha fecha;
    string tipo;
    float costo;
    cout << "Tipo de siniestro: "; tipo = cargarCadena();
    cout << "Costo estimado: "; cin >> costo;

    Siniestro s(id, idPoliza, fecha, tipo, costo, true, false);
    if (_archivo.guardar(s)) cout << "Siniestro registrado." << endl;
    else cout << "Error al guardar." << endl;
}


void SiniestroManager::eliminar(int id) {
    int pos = _archivo.buscarID(id);
    if (pos != -1) {
        Siniestro s = _archivo.leer(pos);
        s.setEliminado(true);
        FILE* f = fopen("Siniestros.dat", "rb+");
        fseek(f, pos * sizeof(Siniestro), SEEK_SET);
        fwrite(&s, sizeof(Siniestro), 1, f);
        fclose(f);
        cout << "Siniestro eliminado." << endl;
    } else {
        cout << "No se encontró el siniestro." << endl;
    }
}

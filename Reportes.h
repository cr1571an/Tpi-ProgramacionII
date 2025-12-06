#pragma once

#include <string>
#include "ClientesArchivo.h"
#include "VehiculosArchivo.h"
#include "PolizaArchivo.h"
#include "SiniestroArchivo.h"
#include "SiniestroManager.h"
#include "TiposSiniestrosArchivo.h"

class Reportes {
public:
    Reportes();
    Reportes(std::string archivoClientes, std::string archivoVehiculos, std::string archivoPolizas,std::string archivoSiniestros);
    void clientesConSiniestrosEntreFecha();

private:
    ClientesArchivo _clientesArchivo;
    VehiculosArchivo _vehiculosArchivo;
    PolizaArchivo _polizasArchivo;
    SiniestroArchivo _siniestroArchivo;
    SiniestroManager _siniestroManager;
    TiposSiniestrosArchivo _tiposSiniestrosArchivo;
};

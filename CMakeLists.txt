cmake_minimum_required(VERSION 3.31)
project(PT)

set(CMAKE_CXX_STANDARD 20)

add_executable(PT
        main.cpp
        App.cpp
        Cliente.cpp
        ClienteManager.cpp
        ClienteMenu.cpp
        ClientesArchivo.cpp
        Fecha.cpp
        Localidad.cpp
        LocalidadArchivo.cpp
        Pago.cpp
        PagoArchivo.cpp
        PagoManager.cpp
        PagoMenu.cpp
        Poliza.cpp
        PolizaArchivo.cpp
        PolizaManager.cpp
        PolizaMenu.cpp
        Siniestro.cpp
        SiniestroArchivo.cpp
        SiniestroManager.cpp
        SiniestroMenu.cpp
        TipoSeguro.cpp
        TiposSegurosArchivo.cpp
        TipoSiniestro.cpp
        TiposSiniestrosArchivo.cpp
        Vehiculo.cpp
        VehiculoManager.cpp
        VehiculoMenu.cpp
        VehiculosArchivo.cpp
        utils.cpp
        Vencimiento.cpp
        VencimientosArchivo.cpp
        SeguroArchivos.cpp
        Seguro.cpp
)


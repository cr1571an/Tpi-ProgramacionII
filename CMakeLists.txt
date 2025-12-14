cmake_minimum_required(VERSION 3.31)
project(PT)

set(CMAKE_CXX_STANDARD 20)

add_executable(PT
        main.cpp

        ClienteManager.cpp
        Cliente.cpp
        ClientesArchivo.cpp

        VehiculoManager.cpp
        Vehiculo.cpp
        VehiculosArchivo.cpp

        PolizaManager.cpp
        Poliza.cpp
        PolizaArchivo.cpp
        PolizaMenu.cpp

        PagoManager.cpp
        Pago.cpp
        PagoArchivo.cpp
        PagoMenu.cpp

        SiniestroManager.cpp
        Siniestro.cpp
        SiniestroArchivo.cpp
        SiniestroMenu.cpp

        TiposSiniestrosArchivo.cpp
        TipoSiniestro.cpp

        TiposSegurosArchivo.cpp
        TipoSeguro.cpp

        Fecha.cpp
        utils.cpp

        ClienteMenu.cpp
        App.cpp
        VehiculoMenu.cpp

        VencimientosArchivo.cpp
        Vencimiento.cpp

        ReporteMenu.cpp
        ReporteMenu.h

)

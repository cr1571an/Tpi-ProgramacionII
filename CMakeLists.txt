cmake_minimum_required(VERSION 3.31)
project(PT)

set(CMAKE_CXX_STANDARD 20)

add_executable(PT main.cpp
        main.cpp
        ClienteManager.cpp
        Clientes.cpp
        ClientesArchivo.cpp
        VehiculoManager.cpp
        Vehiculos.cpp
        VehiculosArchivo.cpp
        PolizaManager.cpp
        Poliza.cpp
        PolizaArchivo.cpp
        PagoManager.cpp
        Pago.cpp
        PagoArchivo.cpp
        SiniestroManager.cpp
        Siniestro.cpp
        SiniestroArchivo.cpp
        Fecha.cpp
        utils.cpp
        ClienteMenu.cpp
        ClienteMenu.h
        App.cpp
        App.h
        VehiculoMenu.cpp
        VehiculoMenu.h
        Localidad.cpp
        Localidad.h
        LocalidadArchivo.cpp
        LocalidadArchivo.h
)

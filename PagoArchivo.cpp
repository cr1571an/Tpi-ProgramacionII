#include "PagoArchivo.h"
#include <iostream>
using namespace std;

PagoArchivo::PagoArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool PagoArchivo::guardar(Pago registro)
{
    bool result;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "ab");

    if (pFile == nullptr)
    {
        return false;
    }

    result = fwrite(&registro, sizeof(Pago), 1, pFile);

    fclose(pFile);

    return result;
}

bool PagoArchivo::guardar(Pago registro, int pos)
{
    bool result;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb+");

    if (pFile == nullptr)
    {
        return false;
    }

    fseek(pFile, sizeof(Pago) * pos, SEEK_SET);

    result = fwrite(&registro, sizeof(Pago), 1, pFile);

    fclose(pFile);

    return result;
}

Pago PagoArchivo::leer(int pos)
{
    Pago registro;
    bool result;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        registro.setId(-1);
        return registro;
    }

    fseek(pFile, sizeof(Pago) * pos, SEEK_SET);

    fread(&registro, sizeof(Pago), 1, pFile);

    fclose(pFile);

    return registro;
}

int PagoArchivo::leerTodos(Pago Pagos[], int cantidad)
{
    int result;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return 0;
    }

    result = fread(Pagos, sizeof(Pago), cantidad, pFile);

    fclose(pFile);

    return result;
}

int PagoArchivo::getCantidadRegistros()
{
    int cantidad;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(Pago);

    fclose(pFile);

    return cantidad;
}

int PagoArchivo::getNuevoID()
{
    return getCantidadRegistros() + 1;
}

int PagoArchivo::buscarID(int id)
{
    Pago registro;
    FILE* pFile;
    int pos = -1;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return pos;
    }

    while (fread(&registro, sizeof(Pago), 1, pFile))
    {
        if (registro.getId() == id)
        {
            pos = ftell(pFile) / sizeof(Pago) - 1;
            break;
        }
    }

    fclose(pFile);

    return pos;
}

bool PagoArchivo::eliminar(int pos)
{
    Pago registro;
    registro = leer(pos);
    registro.setEliminado(true);
    return guardar(registro, pos);
}

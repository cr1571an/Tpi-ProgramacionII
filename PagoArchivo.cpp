#include "PagoArchivo.h"
#include <iostream>
#include <cstdio>
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

    result = (fwrite(&registro, sizeof(Pago), 1, pFile)==1);

    fclose(pFile);

    return result;
}

Pago PagoArchivo::leer(int pos)
{
    Pago registro;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr)
    {
        registro.setId(-1);
        return registro;
    }

    int cant = getCantidadRegistros();
    if (pos < 0 || pos >= cant)
    {
        fclose(pFile);
        registro.setId(-1);
        return registro;
    }

    fseek(pFile, sizeof(Pago) * pos, SEEK_SET);
    size_t leidos = fread(&registro, sizeof(Pago), 1, pFile);

    fclose(pFile);

    if (leidos != 1)
    {
        registro.setId(-1);
    }
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
    cantidad = (ftell(pFile) / sizeof(Pago));

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

    while (fread(&registro, sizeof(Pago), 1, pFile) == 1)
    {
        if (registro.getId() == id)
        {
            pos = (ftell(pFile) / sizeof(Pago)) - 1;
            break;
        }
    }

    fclose(pFile);
    return pos;
}

bool PagoArchivo::eliminar(int id)
{
    int pos = buscarID(id);
    if (pos < 0) return false;

    Pago registro = leer(pos);
    if (registro.getId() == -1) return false;

    registro.setEliminado(true);
    return sobrescribir(registro, pos);
}

bool PagoArchivo::sobrescribir(Pago registro, int pos)
{
    bool result;
    FILE* pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb+");
    if (pFile == nullptr)
    {
        return false;
    }

    fseek(pFile, sizeof(Pago) * pos, SEEK_SET);
    result = (fwrite(&registro, sizeof(Pago), 1, pFile) == 1);

    fclose(pFile);
    return result;
}

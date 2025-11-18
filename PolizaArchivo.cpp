#include "PolizaArchivo.h"

#include <iostream>

using namespace std;

PolizaArchivo::PolizaArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool PolizaArchivo::guardar(Poliza registro) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr) {
    return false;
  }

  result = fwrite(&registro, sizeof(Poliza), 1, pFile);

  fclose(pFile);

  return result;
}

bool PolizaArchivo::guardar(Poliza registro, int pos) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if (pFile == nullptr) {
    return false;
  }

  fseek(pFile, sizeof(Poliza) * pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Poliza), 1, pFile);

  fclose(pFile);

  return result;
}

Poliza PolizaArchivo::leer(int pos) {
  Poliza registro;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    registro.setId(-1);
    return registro;
  }

  fseek(pFile, sizeof(Poliza) * pos, SEEK_SET);

  fread(&registro, sizeof(Poliza), 1, pFile);

  fclose(pFile);

  return registro;
}

int PolizaArchivo::leerTodos(Poliza polizas[], int cantidad) {
  int result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  result = fread(polizas, sizeof(Poliza), cantidad, pFile);

  fclose(pFile);

  return result;
}

int PolizaArchivo::getCantidadRegistros() {
  int cantidad;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Poliza);

  fclose(pFile);

  return cantidad;
}

int PolizaArchivo::getNuevoID() { return getCantidadRegistros() + 1; }

int PolizaArchivo::buscarID(int id) {
  Poliza registro;
  FILE* pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return pos;
  }

  while (fread(&registro, sizeof(Poliza), 1, pFile)) {
    if (registro.getId() == id) {
      pos = ftell(pFile) / sizeof(Poliza) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

bool PolizaArchivo::eliminar(int pos) {
  Poliza registro;
  registro = leer(pos);
  registro.setEliminado(true);
  return guardar(registro, pos);
}

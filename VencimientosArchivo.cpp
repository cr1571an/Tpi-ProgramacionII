#include "VencimientosArchivo.h"

#include <iostream>

using namespace std;

VencimientosArchivo::VencimientosArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool VencimientosArchivo::guardar(Vencimiento registro) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr) {
    return false;
  }

  result = fwrite(&registro, sizeof(Vencimiento), 1, pFile);

  fclose(pFile);

  return result;
}

bool VencimientosArchivo::guardar(Vencimiento registro, int pos) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if (pFile == nullptr) {
    return false;
  }

  fseek(pFile, sizeof(Vencimiento) * pos, SEEK_SET);

  result = fwrite(&registro, sizeof(Vencimiento), 1, pFile);

  fclose(pFile);

  return result;
}

Vencimiento VencimientosArchivo::leer(int pos) {
  Vencimiento registro;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    registro.setId(-1);
    return registro;
  }

  fseek(pFile, sizeof(Vencimiento) * pos, SEEK_SET);

  fread(&registro, sizeof(Vencimiento), 1, pFile);

  fclose(pFile);

  return registro;
}

int VencimientosArchivo::leerTodos(Vencimiento vencimientos[], int cantidad) {
  int result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  result = fread(vencimientos, sizeof(Vencimiento), cantidad, pFile);

  fclose(pFile);

  return result;
}

int VencimientosArchivo::getCantidadRegistros() {
  int cantidad;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Vencimiento);

  fclose(pFile);

  return cantidad;
}

int VencimientosArchivo::getNuevoID() { return getCantidadRegistros() + 1; }

int VencimientosArchivo::buscarID(int id) {
  Vencimiento registro;
  FILE* pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return pos;
  }

  while (fread(&registro, sizeof(Vencimiento), 1, pFile)) {
    if (registro.getId() == id) {
      pos = ftell(pFile) / sizeof(Vencimiento) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

bool VencimientosArchivo::eliminar(int pos) {
  Vencimiento registro;
  registro = leer(pos);
  registro.setEliminado(true);
  return guardar(registro, pos);
}

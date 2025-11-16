#include "TiposSiniestrosArchivo.h"

#include <iostream>

using namespace std;

TiposSiniestrosArchivo::TiposSiniestrosArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool TiposSiniestrosArchivo::guardar(TipoSiniestro registro) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr) {
    return false;
  }

  result = fwrite(&registro, sizeof(TipoSiniestro), 1, pFile);

  fclose(pFile);

  return result;
}

bool TiposSiniestrosArchivo::guardar(TipoSiniestro registro, int pos) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if (pFile == nullptr) {
    return false;
  }

  fseek(pFile, sizeof(TipoSiniestro) * pos, SEEK_SET);

  result = fwrite(&registro, sizeof(TipoSiniestro), 1, pFile);

  fclose(pFile);

  return result;
}

TipoSiniestro TiposSiniestrosArchivo::leer(int pos) {
  TipoSiniestro registro;
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    registro.setId(-1);
    return registro;
  }

  fseek(pFile, sizeof(TipoSiniestro) * pos, SEEK_SET);

  fread(&registro, sizeof(TipoSiniestro), 1, pFile);

  fclose(pFile);

  return registro;
}

int TiposSiniestrosArchivo::leerTodos(TipoSiniestro tiposSiniestros[], int cantidad) {
  int result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  result = fread(tiposSiniestros, sizeof(TipoSiniestro), cantidad, pFile);

  fclose(pFile);

  return result;
}

int TiposSiniestrosArchivo::getCantidadRegistros() {
  int cantidad;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(TipoSiniestro);

  fclose(pFile);

  return cantidad;
}

int TiposSiniestrosArchivo::getNuevoID() { return getCantidadRegistros() + 1; }

int TiposSiniestrosArchivo::buscarID(int id) {
  TipoSiniestro registro;
  FILE* pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return pos;
  }

  while (fread(&registro, sizeof(TipoSiniestro), 1, pFile)) {
    if (registro.getId() == id) {
      pos = ftell(pFile) / sizeof(TipoSiniestro) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

bool TiposSiniestrosArchivo::eliminar(int pos) {
  TipoSiniestro registro;
  registro = leer(pos);
  registro.setEliminado(true);
  return guardar(registro, pos);
}
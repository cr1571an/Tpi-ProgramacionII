#include "SiniestroArchivo.h"

#include <iostream>

using namespace std;

SiniestroArchivo::SiniestroArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool SiniestroArchivo::guardar(Siniestro registro) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr) {
    return false;
  }

  result = fwrite(&registro, sizeof(Siniestro), 1, pFile);

  fclose(pFile);

  return result;
}

Siniestro SiniestroArchivo::leer(int pos) {
  Siniestro registro;
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    registro.setId(-1);
    return registro;
  }

  fseek(pFile, sizeof(Siniestro) * pos, SEEK_SET);

  fread(&registro, sizeof(Siniestro), 1, pFile);

  fclose(pFile);

  return registro;
}

int SiniestroArchivo::leerTodos(Siniestro siniestros[], int cantidad) {
  int result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  result = fread(siniestros, sizeof(Siniestro), cantidad, pFile);

  fclose(pFile);

  return result;
}

int SiniestroArchivo::getCantidadRegistros() {
  int cantidad;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Siniestro);

  fclose(pFile);

  return cantidad;
}

int SiniestroArchivo::getNuevoID() { return getCantidadRegistros() + 1; }

int SiniestroArchivo::buscarID(int id) {
  Siniestro registro;
  FILE* pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return pos;
  }

  while (fread(&registro, sizeof(Siniestro), 1, pFile)) {
    if (registro.getId() == id) {
      pos = ftell(pFile) / sizeof(Siniestro) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}
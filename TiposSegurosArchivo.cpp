#include "TiposSegurosArchivo.h"

#include <iostream>

using namespace std;

TiposSegurosArchivo::TiposSegurosArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool TiposSegurosArchivo::guardar(TipoSeguro registro) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr) {
    return false;
  }

  result = fwrite(&registro, sizeof(TipoSeguro), 1, pFile);

  fclose(pFile);

  return result;
}

bool TiposSegurosArchivo::guardar(TipoSeguro registro, int pos) {
  bool result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb+");

  if (pFile == nullptr) {
    return false;
  }

  fseek(pFile, sizeof(TipoSeguro) * pos, SEEK_SET);

  result = fwrite(&registro, sizeof(TipoSeguro), 1, pFile);

  fclose(pFile);

  return result;
}

TipoSeguro TiposSegurosArchivo::leer(int pos) {
  TipoSeguro registro;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    registro.setId(-1);
    return registro;
  }

  fseek(pFile, sizeof(TipoSeguro) * pos, SEEK_SET);

  fread(&registro, sizeof(TipoSeguro), 1, pFile);

  fclose(pFile);

  return registro;
}

int TiposSegurosArchivo::leerTodos(TipoSeguro tiposSeguros[], int cantidad) {
  int result;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  result = fread(tiposSeguros, sizeof(TipoSeguro), cantidad, pFile);

  fclose(pFile);

  return result;
}

int TiposSegurosArchivo::getCantidadRegistros() {
  int cantidad;
  FILE* pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(TipoSeguro);

  fclose(pFile);

  return cantidad;
}

int TiposSegurosArchivo::getNuevoID() { return getCantidadRegistros() + 1; }

int TiposSegurosArchivo::buscarID(int id) {
  TipoSeguro registro;
  FILE* pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr) {
    return pos;
  }

  while (fread(&registro, sizeof(TipoSeguro), 1, pFile)) {
    if (registro.getId() == id) {
      pos = ftell(pFile) / sizeof(TipoSeguro) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}

bool TiposSegurosArchivo::eliminar(int pos) {
  TipoSeguro registro;
  registro = leer(pos);
  registro.setEliminado(true);
  return guardar(registro, pos);
}

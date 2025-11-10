#include "utils.h"

#include <cctype>
#include <iostream>
#include <string>

std::string cargarCadena() {
  std::string texto;
  if (std::cin.peek() == '\n') {
    std::cin.ignore();
  }
  std::getline(std::cin, texto);
  for (char& c : texto) {
    c = std::toupper(static_cast<unsigned char>(c));
  }
  return texto;
}

int buscarMaximo(int vec[], int cant) {
  int indexMax = 0;
  for (int i = 1; i < cant; i++) {
    if (vec[i] > vec[indexMax]) {
      indexMax = i;
    }
  }
  return indexMax;
}

Fecha procesarFecha(std::string fecha) {
  int anio = std::stoi(fecha.substr(0, 4));
  int mes = std::stoi(fecha.substr(5, 2));
  int dia = std::stoi(fecha.substr(8, 2));
  return Fecha(dia, mes, anio);
}
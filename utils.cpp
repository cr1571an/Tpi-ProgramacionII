#include "utils.h"

#include <cctype>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

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

Fecha leerFechaValida() {
  int d, m, a;
  while (true) {
    cout << "INGRESE FECHA CON ESPACIOS (DD MM AAAA): ";
    if (!(cin >> d >> m >> a)) {
      cout << "ENTRADA INVALIDA." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    int diasMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool bisiesto = (a % 4 == 0) && ((a % 100 != 0) || (a % 400 == 0));
    if (bisiesto) diasMes[2] = 29;

    if (m >= 1 && m <= 12 && d >= 1 && d <= diasMes[m]) {
      return Fecha(d, m, a);
    }
    cout << "FECHA INVALIDA." << endl;
    cout << "QUIERES SEGUIR INTENTANDO? (SI/NO): ";
    string opcion = cargarCadena();
    if (opcion != "SI") {
      return Fecha(-1, -1, -1);
    }
  }
}

Fecha procesarFecha(std::string fecha) {
  int anio = std::stoi(fecha.substr(0, 4));
  int mes = std::stoi(fecha.substr(5, 2));
  int dia = std::stoi(fecha.substr(8, 2));
  return Fecha(dia, mes, anio);
}

bool cortarSiCero(string texto) {
  return texto == "0";
}

string alinearIzquierda(string texto, int ancho) {
  int espacios = ancho - texto.size();
  if (espacios < 0) espacios = 0;
  return texto + string(espacios, ' ');
}

#pragma once
#include <string>
#include "Fecha.h"

std::string cargarCadena();
int buscarMaximo(int vec[], int cant);
Fecha leerFechaValida();
Fecha procesarFecha(std::string fecha);
bool cortarSiCero(std::string texto);
std::string alinearIzquierda(std::string texto, int ancho);

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Fecha.h"

std::string cargarCadena();
int buscarMaximo(int vec[], int cant);
Fecha leerFechaValida();
Fecha procesarFecha(std::string fecha);
bool cortarSiCero(std::string texto);
void mensajeCargaCancelada();
std::string centrar(std::string texto, int ancho);



#endif

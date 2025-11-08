#include <iostream>
#include <string>
#include <cctype>
#include "utils.h"

std::string cargarCadena() {
    std::string texto;
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, texto);
    for (char &c : texto) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return texto;
}

int buscarMaximo(int vec[], int cant){
    int indexMax = 0;
    for(int i=1; i<cant; i++){
        if(vec[i] > vec[indexMax]){
            indexMax = i;
        }
    }
    return indexMax;
}
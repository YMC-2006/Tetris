#ifndef COLAPIEZAS_H
#define COLAPIEZAS_H

#include "NodoPieza.h"

struct ColaPiezas{
	NodoPieza* frenteCola;
	NodoPieza* finalCola;
};

void crearCola(ColaPiezas &cola);
void liberarCola(ColaPiezas &cola);
void encolar(ColaPiezas &cola, TipoPieza tipo);
TipoPieza desencolar(ColaPiezas &cola);
bool colaEstaVacida(ColaPiezas &cola);
int contarPiezas(ColaPiezas &cola);
TipoPieza verPieza(ColaPiezas &cola, int posicion);
void generarBolsa(ColaPiezas &cola);


#endif

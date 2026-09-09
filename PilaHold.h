#ifndef PILAHOLD_H
#define PILAHOLD_H
#include "TipoPieza.h"

struct PilaHold{
	TipoPieza tipo;
	bool ocupada;
};

void crearPila(PilaHold& tope);
void guardarPiezaPila(PilaHold& tope, TipoPieza tipo);
TipoPieza sacarPiezaDePila(PilaHold& tope);
bool pilaVacida(PilaHold& tope);


#endif

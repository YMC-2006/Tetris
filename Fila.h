#ifndef FILA_H
#define FILA_H
#include "TipoPieza.h"

struct Fila{
	TipoPieza celdas[10];
	Fila* siguiente;
	bool marcada;
};

#endif

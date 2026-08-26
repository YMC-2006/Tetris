#ifndef PIEZA_H
#define PIEZA_H
#include "TipoPieza.h"

struct Pieza {
	TipoPieza tipo;
	int x;
	int y;
	int orientacion;
};

#endif

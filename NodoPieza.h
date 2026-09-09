#ifndef NODOPIEZA_H
#define NODOPIEZA_H
#include "TipoPieza.h"


struct NodoPieza{
	TipoPieza tipo;
	NodoPieza* siguiente;
};

#endif

#ifndef NODOEVENT_H
#define NODOEVENT_H
#include "TipoEvento.h"

struct NodoEvento {
	TipoEvento tipo;
	float momentoDisparo;
	NodoEvento* siguiente;
};

#endif

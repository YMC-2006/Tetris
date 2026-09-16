#ifndef NODOREPLAY_H
#define NODOREPLAY_H
#include "TipoMovimiento.h"
#include "Pieza.h"

struct NodoReplay {
	TipoMovimiento tipo;
	Pieza estadoPieza;      // cómo quedó la pieza después de este movimiento
	NodoReplay* anterior;
	NodoReplay* siguiente;
	bool causoLimpieza;
};

#endif

#ifndef PIEZA_H
#define PIEZA_H
#include "TipoPieza.h"
#include "FormasPiezas.h"

struct Pieza {
	TipoPieza tipo;
	int x;
	int y;
	int orientacion;
};

void dibujarPieza(Pieza &pieza);
void obtenerFormaPieza(TipoPieza tipo, int orientacion, Offset bloques[4]);

bool piezaPuedeMoverse(Pieza &pieza, int dx, int dy);
bool piezaPuedeRotar(const Pieza &pieza);
bool posicionValida(int columna, int fila);

#endif

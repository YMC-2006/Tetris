#ifndef LISTAREPLAY_H
#define LISTAREPLAY_H
#include "NodoReplay.h"

struct ListaReplay {
	NodoReplay* primero;
	NodoReplay* ultimo;
	NodoReplay* cursor;
};

void crearListaReplay(ListaReplay &lista);
void liberarListaReplay(ListaReplay &lista);
void registrarMovimiento(ListaReplay &lista, TipoMovimiento tipo, Pieza estado, bool causoLimpieza);


#endif

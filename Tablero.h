#ifndef TABLERO_H
#define TABLERO_H
#include "Fila.h"

struct Tablero{
	Fila* primera;
};

void crearTablero(Tablero &tablero);
void liberarTablero(Tablero &tablero); // preguntar a la profe
void dibujarTablero(Tablero &tablero);

Fila* obtenerFila(Tablero &tablero, int indice);
bool filaEstaCompleta(Fila* nodoActual);
int limpiarFilaCompleta(Tablero &tablero);
#endif

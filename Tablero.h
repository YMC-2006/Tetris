#ifndef TABLERO_H
#define TABLERO_H
#include "Fila.h"
#include "raylib.h"

struct Tablero{
	Fila* primera;
};

void crearTablero(Tablero &tablero);
void liberarTablero(Tablero &tablero); 
void dibujarTablero(Tablero &tablero);

Fila* obtenerFila(Tablero &tablero, int indice);
bool filaEstaCompleta(Fila* nodoActual);
int limpiarFilaCompleta(Tablero &tablero);
int marcarFilasCompletas(Tablero &tablero); // para la animacion
Color colorDePieza(TipoPieza tipo);


#endif

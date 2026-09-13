#ifndef COLAEVENTOS_H
#define COLAEVENTOS_H
#include "TipoEvento.h"
#include "NodoEvento.h"


struct ColaEventos{
	NodoEvento* frente;
};

void crearColaEventos(ColaEventos &cola);
void liberarColaEventos(ColaEventos &cola);
void programarEvento(ColaEventos &cola, TipoEvento tipo, float momentoDisparo);
bool hayEventoListo(ColaEventos &cola, float tiempoActual);
TipoEvento extraerEvento(ColaEventos &cola);

#endif

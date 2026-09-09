#include "PilaHold.h"
#include "raylib.h"

void crearPila(PilaHold& tope){

	tope.ocupada = false;
	tope.tipo = NINGUNA;
	
}
	
	// donde va la logica de presionar la tecla h y que se ponga en hold
void guardarPiezaPila(PilaHold& tope, TipoPieza tipo){
	tope.tipo = tipo;
	tope.ocupada = true;

}
	
TipoPieza sacarPiezaDePila(PilaHold& tope){
	
	if(!tope.ocupada){
		TraceLog(LOG_INFO, "NO SE PUEDE SACAR NADA PORQUE LA PILA ESTA VACIDA");
		return NINGUNA;
	}
	
	TipoPieza tipo = tope.tipo;
	tope.ocupada = false;
	return tipo;
}
	
bool pilaVacida(PilaHold& tope){
	return !tope.ocupada;
}

#include "ColaEventos.h"
#include "NodoEvento.h"
#include "raylib.h"

void crearColaEventos(ColaEventos &cola){
	cola.frente = nullptr;
}
	
void liberarColaEventos(ColaEventos &cola){
	NodoEvento* actual = cola.frente;
	
	while(actual != nullptr){
		NodoEvento* sigNodo = actual->siguiente;
		delete actual;
		actual = sigNodo;
	}
	
	cola.frente = nullptr;
	
}

void programarEvento(ColaEventos &cola, TipoEvento tipo, float momentoDisparo){
	
	NodoEvento* nuevo = new NodoEvento;
	nuevo->tipo = tipo;
	nuevo->momentoDisparo = momentoDisparo;
	nuevo->siguiente = nullptr;
	
	if(cola.frente == nullptr || momentoDisparo < cola.frente->momentoDisparo){
		nuevo->siguiente = cola.frente;
		cola.frente = nuevo;
		return;
	}
	
	//  buscar el lugar correcto recorriendo la lista
	NodoEvento* actual = cola.frente;
	while(actual->siguiente != nullptr && actual->siguiente->momentoDisparo <= momentoDisparo){
		actual = actual->siguiente;
	}
	
	nuevo->siguiente = actual->siguiente;
	actual->siguiente = nuevo;
	
}
bool hayEventoListo(ColaEventos &cola, float tiempoActual){
	
	if(cola.frente != nullptr && cola.frente->momentoDisparo <= tiempoActual){
		
		TraceLog(LOG_INFO, "Evento listo!!!");
		return true;
		
	}
	return false;

}
TipoEvento extraerEvento(ColaEventos &cola){
	NodoEvento* nodoFrente = cola.frente;
	TipoEvento tipo = nodoFrente->tipo;
	cola.frente = cola.frente->siguiente;
	delete nodoFrente;
	return tipo;

}







#include "raylib.h"
#include "ColaPiezas.h"
//cambiar nombre a inicializar
void crearCola(ColaPiezas &cola){
	cola.frenteCola = nullptr;
	cola.finalCola = nullptr;
	
}

void liberarCola(ColaPiezas &cola){
	NodoPieza* actual = cola.frenteCola;
	while(actual != nullptr){
		NodoPieza* siguienteNodo = actual->siguiente;
		delete actual;
		actual = siguienteNodo;
	}
	
	cola.frenteCola = nullptr;
	cola.finalCola = nullptr;
}
	

	// agregar al final
void encolar(ColaPiezas &cola, TipoPieza tipo){
	NodoPieza* nuevo = new NodoPieza;
	nuevo->tipo = tipo;
	nuevo->siguiente = nullptr;
	
	// cuando el final de la cola esta vacido o sea cuando la cola esta aun vacida
	if(cola.finalCola == nullptr){
		cola.frenteCola = nuevo;
		cola.finalCola = nuevo;
	}else{
		cola.finalCola->siguiente = nuevo;
		cola.finalCola = nuevo;
	}
	
}
	



TipoPieza desencolar(ColaPiezas &cola){
	
	if(cola.frenteCola == nullptr){
		return NINGUNA;
	}
	
	NodoPieza* nodoFrente = cola.frenteCola;
	TipoPieza tipo = nodoFrente->tipo;
	cola.frenteCola = cola.frenteCola->siguiente;
	
	if(cola.frenteCola == nullptr){
		cola.finalCola = nullptr; // se vacio
	}
	
	delete nodoFrente;
	return tipo;
	
}
bool colaEstaVacida(ColaPiezas &cola){
	if(cola.frenteCola == nullptr){
		return true;
	}
	return false;
}
	
	
int contarPiezas(ColaPiezas &cola){
	
	int contador = 0;
	NodoPieza* actual = cola.frenteCola;
	while(actual != nullptr){
		contador++;
		actual = actual->siguiente;
	}
	return contador;
}
	
	
TipoPieza verPieza(ColaPiezas &cola, int posicion){
	
	NodoPieza* actual = cola.frenteCola;
	for(int i = 0; i < posicion && actual != nullptr; i++){
		actual = actual->siguiente;
	}
	if(actual != nullptr){
		return actual->tipo;
	}
	return NINGUNA;
	
	
}
	
// para generar la bolsa se utiliza el algoritmo Fishes-Yates
void generarBolsa(ColaPiezas &cola){
	TipoPieza tipos[7] = { I, O, T, S, Z, J, L };
	for(int i = 6; i > 0; i--){
		int j = GetRandomValue(0,i);
		TipoPieza temp = tipos[i];
		tipos[i] = tipos[j];
		tipos[j] = temp;
		
	}
	
	for(int i = 0; i < 7; i++){
		encolar(cola, tipos[i]);
	}
	
	
}

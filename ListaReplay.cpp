#include "ListaReplay.h"

void crearListaReplay(ListaReplay &lista){
	lista.cursor = nullptr;
	lista.primero = nullptr;
	lista.ultimo = nullptr;
}
	
void liberarListaReplay(ListaReplay &lista){
	
	NodoReplay* actual = lista.primero;
	while(actual != nullptr){
		NodoReplay* siguiente = actual->siguiente;
		delete actual;
		actual = siguiente;
		
	}
	lista.cursor = nullptr;
	lista.primero = nullptr;
	lista.ultimo = nullptr;
}

	
// FUNCION POR VER
void registrarMovimiento(ListaReplay &lista, TipoMovimiento tipo, Pieza estado, bool causoLimpieza){
	// si el cursor no está al final, se perdió el "futuro" o sea lo que se había deshecho
	if(lista.cursor != lista.ultimo){
		NodoReplay* sobrante = (lista.cursor == nullptr) ? lista.primero : lista.cursor->siguiente;
		
		// borramos ese path que ya no existe
		while(sobrante != nullptr){
			NodoReplay* siguienteSobrante = sobrante->siguiente;
			delete sobrante;
			sobrante = siguienteSobrante;
		}
		
		if(lista.cursor == nullptr){
			lista.primero = nullptr;
		}else{
			lista.cursor->siguiente = nullptr;
		}
		lista.ultimo = lista.cursor;
	}
	
	NodoReplay* nuevo = new NodoReplay;
	nuevo->tipo = tipo;
	nuevo->estadoPieza = estado;
	nuevo->siguiente = nullptr;
	nuevo->anterior = lista.ultimo;
	nuevo->causoLimpieza = causoLimpieza;
	
	if(lista.ultimo != nullptr){
		lista.ultimo->siguiente = nuevo;
	}else{
		lista.primero = nuevo;
	}
	
	lista.ultimo = nuevo;
	lista.cursor = nuevo;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	





	
	


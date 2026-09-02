#include "Tablero.h"
#include "raylib.h"
#include "Fila.h"
#include "TipoPieza.h"

const int TAM_CELDA = 45;
const int TABLERO_X = 440; // para que quede en el centro
const int TABLERO_Y = 99; // para que quede bien arribita

void crearTablero(Tablero &tablero){
	tablero.primera = nullptr;
	Fila* anterior = nullptr;
	
	for(int i = 0; i < 20; i++){
		Fila* nuevaFila = new Fila;
		for(int c = 0; c < 10; c++){
			nuevaFila->celdas[c] = NINGUNA;
			nuevaFila->marcada = false;
		}
		
		nuevaFila->siguiente = nullptr;
		
		if(tablero.primera == nullptr){
			tablero.primera = nuevaFila;
		}else{
			anterior->siguiente = nuevaFila;
		}
		
		anterior = nuevaFila;
	}
	
}
void liberarTablero(Tablero &tablero){
	
	Fila* actual = tablero.primera;
	while(actual != nullptr){
		Fila* siguienteFila = actual->siguiente;
		delete actual;
		actual = siguienteFila;
	}
	
	tablero.primera = nullptr;
	
}
	

	
Color colorDePieza(TipoPieza tipo){
	
	Color aqua     = {124, 213, 217, 255};  // I
	Color amarillo = {255, 226, 111, 255};  // O
	Color lila     = {232, 192, 252, 255};  // T
	Color verde    = {196, 224, 47,  255};  // S
	Color rosado   = {255, 169, 221, 255};  // Z
	Color azul     = {153, 173, 255, };  // J
	Color naranja  = {254, 183, 0,   255};  // L
	
	
	switch(tipo){
	case I: return aqua;
	case O: return amarillo;
	case T: return lila;
	case S: return verde;
	case Z:	return rosado;
	case J: return RED;
	case L:	return naranja;
	default: return RAYWHITE; // NINGUNA
	}
}

void dibujarTablero(Tablero &tablero){
	
	
	Fila* filaActual = tablero.primera;
	int fila = 0;
	
	while(filaActual != nullptr){
		for(int col = 0; col < 10; col++){
			int px = TABLERO_X + col * TAM_CELDA;
			int py = TABLERO_Y + fila * TAM_CELDA;
			
			Color color;
			if(filaActual->marcada){
				bool destello = ((int)(GetTime() * 12)%2 == 0);
				color = destello ? WHITE : colorDePieza(filaActual->celdas[col]);
			}else{
				color = colorDePieza(filaActual->celdas[col]);
			}
			
			Rectangle celda = {(float)px, (float)py, (float)TAM_CELDA, (float)TAM_CELDA};
			DrawRectangleRec(celda, color);
			DrawRectangleLinesEx(celda, 1, GRAY);
		}
		filaActual = filaActual->siguiente;
		fila++;
	}

	
}
	
	
// hay que recorrer las filas hasta la ultima porque es un lista  ir saltando de nodo en nodo
Fila* obtenerFila(Tablero &tablero, int indice){
	Fila* actual = tablero.primera;
	for(int i = 0; i < indice && actual != nullptr; i++){
		actual = actual->siguiente;
	}
	
	return actual;
}

	
bool filaEstaCompleta(Fila* filaActual){		
	
	for(int i = 0; i < 10; i++){
		if(filaActual->celdas[i] == NINGUNA){
			return false;
		}
	}
	return true;
}
	
int limpiarFilaCompleta(Tablero &tablero){
	
	Fila* filaActual = tablero.primera;
	Fila* anterior = nullptr;
	
	int cantFilasEliminadas = 0;
	
	while(filaActual != nullptr){
		
		
		if(filaEstaCompleta(filaActual)){
			Fila* siguienteFila = filaActual->siguiente;
			
			
			if(anterior == nullptr){
				tablero.primera = siguienteFila;
			}else{
				anterior->siguiente = siguienteFila;
			}
			
			delete filaActual;
			
			//desp de haber eliminado una fila tenemos que insertar una nueva fila vacida al inicio
			Fila *filaVacida = new Fila;
			for(int i = 0; i < 10; i++){
				filaVacida->celdas[i] = NINGUNA;				
			}
			
			filaVacida->marcada = false;
			
			filaVacida->siguiente = tablero.primera;
			tablero.primera = filaVacida;
			
			cantFilasEliminadas++;
			filaActual = siguienteFila;
		}else{
			anterior = filaActual;
			filaActual = filaActual->siguiente;
		}

		
		
	}
	
	return cantFilasEliminadas;
}
	
int marcarFilasCompletas(Tablero &tablero){
	int contador = 0;
	Fila* filaActual = tablero.primera;
	while(filaActual != nullptr){
		if(filaEstaCompleta(filaActual)){
			filaActual->marcada = true;
			contador++;
		}
		filaActual = filaActual->siguiente;
	}
	return contador;
}

	
	
	
	
	

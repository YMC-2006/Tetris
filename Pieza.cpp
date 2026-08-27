#include "Pieza.h"
#include "FormasPiezas.h"
#include "raylib.h"


const int TAM_CELDA = 40;
const int TABLERO_X = 550; // para que quede en el centro
const int TABLERO_Y = 150; // para que quede bien arribita

Color colorDePieza(TipoPieza tipo); // ya la hecha en Tablero.cpp


void obtenerFormaPieza(TipoPieza tipo, int orientacion, Offset bloques[4]){
	switch(tipo){
	case T:
		for(int i = 0; i < 4; i++){
			bloques[i] = FORMA_T[orientacion][i];
		}
		break;
	default: 
		for(int i = 0; i < 4; i++) bloques[i] = {0,0};
		break;
	}
}

void dibujarPieza(Pieza &pieza){
	Offset bloques[4];
	obtenerFormaPieza(pieza.tipo, pieza.orientacion, bloques);
	
	for(int i = 0; i < 4; i++){
		int columna = pieza.x + bloques[i].dx;
		int fila = pieza.y + bloques[i].dy;
		
		int px = TABLERO_X + columna * TAM_CELDA;
		int py = TABLERO_Y + fila * TAM_CELDA;
		
		// para pintar cada cuadrito son 4
		Rectangle celda = {(float)px, (float)py, (float)TAM_CELDA, (float)TAM_CELDA};
		DrawRectangleRec(celda, colorDePieza(pieza.tipo));
		DrawRectangleLinesEx(celda, 1, GRAY);
	}
}


bool posicionValida(int columna, int fila){
	return columna >= 0 && columna < 10 && fila >=0 && fila < 20;
}
	
	
bool piezaPuedeMoverse(Pieza &pieza, int dx, int dy){
	Offset bloques[4];
	
	obtenerFormaPieza(pieza.tipo, pieza.orientacion, bloques);
	
	for(int i = 0; i < 4; i++){
		int columna = pieza.x + dx + bloques[i].dx;
		int fila = pieza.y + dy + bloques[i].dy;
		
		if(!posicionValida(columna, fila)){
			return false;
		}
	}
	
	return true;
	
}
	
bool piezaPuedeRotar(const Pieza &pieza){
	int siguienteOrientacion = (pieza.orientacion + 1) % 4;
	Offset bloques[4];
	obtenerFormaPieza(pieza.tipo, siguienteOrientacion, bloques);
	
	for(int i = 0; i < 4; i++){
		int columna = pieza.x + bloques[i].dx;
		int fila = pieza.y + bloques[i].dy;
		if(!posicionValida(columna, fila)){
			return false;
		}
	}
	
	return true;
}

#include "Juego.h"
#include "raylib.h"
#include "Tablero.h"

Juego::Juego(){
	crearTablero(tablero);
	
}

Juego::~Juego(){
	liberarTablero(tablero);
}
	
void Juego::moverPiezaConTeclado(){
	
	if(IsKeyPressed(KEY_LEFT) && piezaPuedeMoverse(piezaActual, -1, 0, tablero)){
		piezaActual.x--;
	}
	if(IsKeyPressed(KEY_RIGHT) && piezaPuedeMoverse(piezaActual, 1, 0, tablero)){
		piezaActual.x++;
	}
	if(IsKeyPressed(KEY_DOWN) && piezaPuedeMoverse(piezaActual, 0, 1, tablero)){
		piezaActual.y++;
	}
	if(IsKeyPressed(KEY_UP) && piezaPuedeRotar(piezaActual, tablero)){
		piezaActual.orientacion = (piezaActual.orientacion + 1) % 4;
	}
	
}


void Juego::generarPiezaNueva(){
	piezaActual = { O, 4, 1, 0 };
	
}
	
void Juego::actualizar(){
	
	if(!piezaPuedeMoverse(piezaActual, 0, 1, tablero)){
		fijarPiezaEnTablero();
		generarPiezaNueva();
		temporizadorCaida = 0;
		return;
	}
	
	temporizadorCaida += GetFrameTime();
	if(temporizadorCaida >= intervaloCaida){
		temporizadorCaida = 0;
		piezaActual.y++;
	}
}

	
void Juego::dibujarElementosJuego(){
	dibujarTablero(tablero);
	dibujarPieza(piezaActual);
}


void Juego::fijarPiezaEnTablero(){
	Offset bloques[4];
	obtenerFormaPieza(piezaActual.tipo, piezaActual.orientacion, bloques);
	
	for(int i = 0; i < 4; i++){
		int columna = piezaActual.x + bloques[i].dx;
		int fila = piezaActual.y + bloques[i].dy;
		
		Fila* nodoFila = obtenerFila(tablero, fila);
		if(nodoFila != nullptr){
			nodoFila->celdas[columna] = piezaActual.tipo;
		}
	}
}

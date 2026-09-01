#include "Juego.h"
#include "raylib.h"
#include "Tablero.h"
#include <ctime> 

Juego::Juego(){
	
	SetRandomSeed((unsigned int)time(NULL));
	crearTablero(tablero);
	generarPiezaNueva(); 
}

Juego::~Juego(){
	liberarTablero(tablero);
}
	
void Juego::moverPiezaConTeclado(){
	if(juegoTerminado){
		return;
	}
	
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
	
	int aleatorio = GetRandomValue(0, 6);
	TipoPieza tipo;
	if(aleatorio == 0){
		tipo = O;
	}else if(aleatorio == 1){
		tipo = T;
	}else if(aleatorio == 2){
		tipo = L;
	}else if(aleatorio == 3){
		tipo = S;
	}else if(aleatorio == 4){
		tipo = Z;
	}else if(aleatorio == 5){
		tipo = J;
	}else if(aleatorio == 6){
		tipo = I;
	}
	else{
		//cout << "Se genero un numero fuera del rango";
		return;
	}
	
	
	piezaActual = { tipo, 4, 1, 0 };
	
}
	
void Juego::actualizar(){
	if(juegoTerminado){
		return;
	}
	
	if(!piezaPuedeMoverse(piezaActual, 0, 1, tablero)){
		
		fijarPiezaEnTablero();
		generarPiezaNueva();
		
		int lineas = limpiarFilaCompleta(tablero);
		if(lineas > 0){
			puntaje += lineas * 100; 
		}
				
		if(!piezaPuedeMoverse(piezaActual, 0, 0, tablero)){
			juegoTerminado = true; 
		}
		
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

void Juego::reiniciar(){
	liberarTablero(tablero);
	crearTablero(tablero);
	juegoTerminado = false;
	puntaje = 0;
	temporizadorCaida = 0;
	generarPiezaNueva();
}

void Juego::pausar(){
	btnPausa = {100, 100, 50, 20};
	DrawRectangleRec(btnPausa, RED);
	Vector2 mouse = GetMousePosition();
	if(CheckCollisionPointRec(mouse, btnPausa) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "SE PAUSO EL JUEGO");
		
	}
}

bool Juego::haTerminado(){
	return juegoTerminado;
}

int Juego::obtenerPuntaje(){
	return puntaje;
}

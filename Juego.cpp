#include "Juego.h"
#include "raylib.h"
#include "Tablero.h"
#include <ctime> 

Juego::Juego(){
	
	SetRandomSeed((unsigned int)time(NULL));
	crearTablero(tablero);
	crearCola(colaPiezas);
	generarBolsa(colaPiezas);
	generarPiezaNueva(); 
}

Juego::~Juego(){
	liberarTablero(tablero);
	liberarCola(colaPiezas);
}
	
void Juego::moverPiezaConTeclado(){
	if(juegoTerminado || animandoLimpieza){
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
	
	if(contarPiezas(colaPiezas) < 7){
		generarBolsa(colaPiezas);
	}
	TipoPieza tipo = desencolar(colaPiezas);
	piezaActual = { tipo, 4, 1, 0 };
	
}
	
void Juego::actualizar(){
	if(juegoTerminado){
		return;
	}
	
	if(animandoLimpieza){
		temporizadorLimpieza += GetFrameTime();
		if(temporizadorLimpieza  >= duracionLimpieza){
			int lineas = limpiarFilaCompleta(tablero);
			if(lineas > 0){
				puntaje += lineas * 100; 
			}
			animandoLimpieza = false;
			if(!piezaPuedeMoverse(piezaActual, 0, 0, tablero)){
				juegoTerminado = true;
			}
		
		}
		return;   // pase o no el timer, no sigas a la lógica de caída normal
	}
	
	
	if(!piezaPuedeMoverse(piezaActual, 0, 1, tablero)){
		
		fijarPiezaEnTablero();
		generarPiezaNueva();
		
		if(marcarFilasCompletas(tablero) > 0){
			animandoLimpieza = true;
			temporizadorLimpieza = 0;
		}else if(!piezaPuedeMoverse(piezaActual, 0, 0, tablero)){
			juegoTerminado = true;
		}
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
	dibujarTresSiguientesPiezas();
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
	liberarCola(colaPiezas);
	crearCola(colaPiezas);
	generarBolsa(colaPiezas);
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

void Juego::dibujarTresSiguientesPiezas(){
	int tamCeldaPreview = 35;
	
	int slotX[3] = {1111, 1111, 1111};
	int slotY[3] = {360, 580, 790};
	
	//DrawText("Siguientes:", x, y, 20, BLACK);
	
	for(int i = 0; i < 3; i++){
		TipoPieza tipo = verPieza(colaPiezas, i);
		dibujarPiezaEnPosicion(tipo, slotX[i], slotY[i], tamCeldaPreview);
	}
}

bool Juego::haTerminado(){
	return juegoTerminado;
}

int Juego::obtenerPuntaje(){
	return puntaje;
}

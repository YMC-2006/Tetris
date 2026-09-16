#include "Juego.h"
#include "raylib.h"
#include "Tablero.h"
#include <ctime> 
#include "ListaReplay.h"

Juego::Juego(){
	
	SetRandomSeed((unsigned int)time(NULL));
	crearTablero(tablero);
	crearCola(colaPiezas);
	generarBolsa(colaPiezas);
	crearPila(pilaHold);
	programarEventosIniciales();
	crearListaReplay(historialReplay);
	btnDeshacer = { 50, 620, 140, 45 };
	btnRehacer  = { 200, 620, 140, 45 };
	generarPiezaNueva(); 
}

Juego::~Juego(){
	liberarTablero(tablero);
	liberarCola(colaPiezas);
	liberarColaEventos(colaEventos);
	liberarListaReplay(historialReplay);
}

	
void Juego::reiniciar(){
	liberarTablero(tablero);
	crearTablero(tablero);
	liberarCola(colaPiezas);
	crearCola(colaPiezas);
	generarBolsa(colaPiezas);
	crearPila(pilaHold); // :D
	
	// reiniciamos todo lo relacionado con la cola de eventos
	liberarColaEventos(colaEventos);
	programarEventosIniciales();
	intervaloCaida = 0.5f;
	tiempoJuego = 0;
	puntosDoblesActivo = false;
	piezaFacilPendiente = false;
	
	juegoTerminado = false;
	puntaje = 0;
	temporizadorCaida = 0;
	
	liberarListaReplay(historialReplay);
	crearListaReplay(historialReplay);
	
	generarPiezaNueva();
}


void Juego::dibujarElementosJuego(){
	dibujarTablero(tablero);
	dibujarPieza(piezaActual);
	dibujarTresSiguientesPiezas();
	dibujarPiezaEnHold();
	dibujarMensajeEvento();
	dibujarBotonesHistorial();
}


// ayudante para los clicks
static bool clickEn(Rectangle r){
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), r);
}
	
// COLA DE EVENTOOS
void Juego::programarEventosIniciales(){
	crearColaEventos(colaEventos);
	programarEvento(colaEventos, AUMENTAR_VELOCIDAD, 20.0f);
	programarEvento(colaEventos, PUNTOS_DOBLES, 25.0f);
	programarEvento(colaEventos, PIEZA_FACIL, 30.0f);
}
	
void Juego::moverPiezaConTeclado(){
	if(juegoTerminado || animandoLimpieza){
		return;
	}
	
	if( IsKeyPressed(KEY_Z) || clickEn(btnDeshacer)){
		deshacerMovimiento();
		return;
	}
	if(IsKeyPressed(KEY_Y) || clickEn(btnRehacer)){
		rehacerMovimiento();
		return;
	}
	
	if(IsKeyPressed(KEY_LEFT) && piezaPuedeMoverse(piezaActual, -1, 0, tablero)){
		piezaActual.x--;
		registrarMovimiento(historialReplay, MOV_IZQUIERDA, piezaActual, false);
	}
	if(IsKeyPressed(KEY_RIGHT) && piezaPuedeMoverse(piezaActual, 1, 0, tablero)){
		piezaActual.x++;
		registrarMovimiento(historialReplay, MOV_DERECHA, piezaActual, false);
	}
	if(IsKeyPressed(KEY_DOWN) && piezaPuedeMoverse(piezaActual, 0, 1, tablero)){
		piezaActual.y++;
		registrarMovimiento(historialReplay, MOV_BAJAR, piezaActual, false);
	}
	if(IsKeyPressed(KEY_UP) && piezaPuedeRotar(piezaActual, tablero)){
		piezaActual.orientacion = (piezaActual.orientacion + 1) % 4;
		registrarMovimiento(historialReplay, MOV_ROTAR, piezaActual, false);
	}

	
	if(IsKeyPressed(KEY_H)){
		if(pilaVacida(pilaHold)){
			guardarPiezaPila(pilaHold, piezaActual.tipo);
			generarPiezaNueva();
		}else{
			// sacar la pieza de hold y remplazar con la nueva
			TipoPieza piezaGuardadaEnHold = sacarPiezaDePila(pilaHold);
			TipoPieza tipoActual = piezaActual.tipo;
			
			piezaActual = { piezaGuardadaEnHold, 4, 1, 0 };
			guardarPiezaPila(pilaHold, tipoActual);
			
		}
 
	}
	
}


void Juego::generarPiezaNueva(){
	
	if(contarPiezas(colaPiezas) < 7){
		generarBolsa(colaPiezas);
	}
	
	
	TipoPieza tipo;
	
	if(piezaFacilPendiente){
		tipo = T;
		piezaFacilPendiente = false;
	}else{
		tipo = desencolar(colaPiezas);
		
	}
	piezaActual = { tipo, 4, 1, 0 };
	registrarMovimiento(historialReplay, MOV_GENERAR, piezaActual, false);
	
	
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
				
				int puntosGanados = lineas * 50;
				
				if(puntosDoblesActivo){
					puntosGanados = puntosGanados * 2; // para el evento :p
				}
				puntaje += puntosGanados; 
			}
			animandoLimpieza = false;
			if(!piezaPuedeMoverse(piezaActual, 0, 0, tablero)){
				juegoTerminado = true;
			}
		
		}
		return;   // pase o no el timer, no sigas a la lógica de caída normal
	}
	
	// eventos !! :D
	
	tiempoJuego += GetFrameTime();
	
	if(hayEventoListo(colaEventos, tiempoJuego)){
		TipoEvento tipo = extraerEvento(colaEventos);
		aplicarEvento(tipo);
	}
	
	if(puntosDoblesActivo){
		tiempoRestantePuntosDobles -= GetFrameTime();
		if(tiempoRestantePuntosDobles <= 0){
			puntosDoblesActivo = false;
		}
	}
	
	if(mostrandoMensajeEvento){
		tiempoMensajeEvento -= GetFrameTime();
		if(tiempoMensajeEvento <= 0){
			mostrandoMensajeEvento = false;
		}
	}
	
	if(!piezaPuedeMoverse(piezaActual, 0, 1, tablero)){
		
		fijarPiezaEnTablero();
		int lineasCompletas = marcarFilasCompletas(tablero);
		// si al colocar una pieza hay match entonces ese movimiento no puede devolverse
		registrarMovimiento(historialReplay, MOV_COLOCAR, piezaActual, lineasCompletas > 0);
		generarPiezaNueva();
		
		if(lineasCompletas > 0){
			animandoLimpieza = true;
			temporizadorLimpieza = 0;
		}else if(!piezaPuedeMoverse(piezaActual, 0, 0, tablero)){
			juegoTerminado = true;
		}
		return;
	}
	
	float intervalo = IsKeyDown(KEY_DOWN) ? intervaloCaidaRapida : intervaloCaida;
	
	temporizadorCaida += GetFrameTime();
	if(temporizadorCaida >= intervalo){
		temporizadorCaida = 0;
		piezaActual.y++;
	}
}



void Juego::fijarPiezaEnTablero(){
//	Offset bloques[4];
//	obtenerFormaPieza(piezaActual.tipo, piezaActual.orientacion, bloques);
//	
//	for(int i = 0; i < 4; i++){
//		int columna = piezaActual.x + bloques[i].dx;
//		int fila = piezaActual.y + bloques[i].dy;
//		
//		Fila* nodoFila = obtenerFila(tablero, fila);
//		if(nodoFila != nullptr){
//			nodoFila->celdas[columna] = piezaActual.tipo;
//		}
//	}
	
	ponerPiezaEnTablero(tablero, piezaActual);
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
	int tamCelda = 35;
	
	int slotX[3] = {1111, 1111, 1111};
	int slotY[3] = {360, 580, 790};
	
	//DrawText("Siguientes:", x, y, 20, BLACK);
	
	for(int i = 0; i < 3; i++){
		TipoPieza tipo = verPieza(colaPiezas, i);
		dibujarPiezaEnPosicion(tipo, slotX[i], slotY[i], tamCelda);
	}
}

void Juego::dibujarPiezaEnHold(){
	int tamCelda = 35;
	int x = 1111;
	int y = 130;
	
	if(!pilaVacida(pilaHold)){
		dibujarPiezaEnPosicion(pilaHold.tipo, x, y + 40, tamCelda);
	}
	
}

void Juego::aplicarEvento(TipoEvento tipo){
	if(tipo == AUMENTAR_VELOCIDAD){
		mostrandoMensajeEvento = true;
		eventoMostrado = tipo;
		tiempoMensajeEvento = duracionMensajeEvento;
		
		if(intervaloCaida > 0.15f){
			intervaloCaida -= 0.05f;
		}
		programarEvento(colaEventos, AUMENTAR_VELOCIDAD, tiempoJuego + 20.0f);
		
	}else if(tipo == PUNTOS_DOBLES){
		puntosDoblesActivo = true;
		tiempoRestantePuntosDobles = 10.0f;
		programarEvento(colaEventos, PUNTOS_DOBLES, tiempoJuego + 30.0f);
		
		
		
	}else if(tipo == PIEZA_FACIL){
		mostrandoMensajeEvento = true;
		eventoMostrado = tipo;
		tiempoMensajeEvento = duracionMensajeEvento;
		
		piezaFacilPendiente = true;
		programarEvento(colaEventos, PIEZA_FACIL, tiempoJuego + 40.0f);
	}
}


void Juego::dibujarMensajeEvento(){
	if(mostrandoMensajeEvento){
		const char* texto;
		if(eventoMostrado == AUMENTAR_VELOCIDAD){
			texto = "Velocidad aumentada!";
		}else{
			texto = "Pieza facil de regalo!";
		}
		DrawText(texto, 450, 40, 30, PINK);
	}
	
	if(puntosDoblesActivo){
		DrawText("Puntos dobles activos!", 450, 60, 30, ORANGE);
	}
}

void Juego::deshacerMovimiento(){
	NodoReplay* actual = historialReplay.cursor;
	
	if(actual == nullptr){
		return;
		
	}
	
	if(actual->tipo == MOV_GENERAR){
	
		NodoReplay* nodoColocar = actual->anterior;
		if(nodoColocar == nullptr){ return; }
		if(nodoColocar->tipo != MOV_COLOCAR){ return; }
		if(nodoColocar->causoLimpieza){ return; }  // no se revierte una limpieza
		
		borrarPiezaDelTablero(tablero, nodoColocar->estadoPieza);
		piezaActual = nodoColocar->estadoPieza;
		historialReplay.cursor = nodoColocar->anterior;
		temporizadorCaida = 0;
		return;
	}
	
	if(actual->anterior == nullptr){ return; }
	piezaActual = actual->anterior->estadoPieza;
	historialReplay.cursor = actual->anterior;
	temporizadorCaida = 0;
}
	

void Juego::rehacerMovimiento(){
	NodoReplay* siguiente = (historialReplay.cursor == nullptr) ? historialReplay.primero : historialReplay.cursor->siguiente;
	if(siguiente == nullptr){ return; }
	// Rehacer solo aplica a movimientos de la pieza que esta cayendo.
	if(siguiente->tipo == MOV_COLOCAR || siguiente->tipo == MOV_GENERAR){ return; }
	
	piezaActual = siguiente->estadoPieza;
	historialReplay.cursor = siguiente;
	temporizadorCaida = 0;
}

ListaReplay& Juego::obtenerHistorial(){
	return historialReplay;
}

void Juego::dibujarBotonesHistorial(){
	DrawRectangleRec(btnDeshacer, PURPLE);
	DrawText("Deshacer (Z)", (int)btnDeshacer.x + 12, (int)btnDeshacer.y + 13, 18, WHITE);
	DrawRectangleRec(btnRehacer, PURPLE);
	DrawText("Rehacer (Y)", (int)btnRehacer.x + 12, (int)btnRehacer.y + 13, 18, WHITE);
}



bool Juego::haTerminado(){
	return juegoTerminado;
}

int Juego::obtenerPuntaje(){
	return puntaje;
}

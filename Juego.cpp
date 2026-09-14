#include "Juego.h"
#include "raylib.h"
#include "Tablero.h"
#include <ctime> 

Juego::Juego(){
	
	SetRandomSeed((unsigned int)time(NULL));
	crearTablero(tablero);
	crearCola(colaPiezas);
	generarBolsa(colaPiezas);
	crearPila(pilaHold);
	programarEventosIniciales();
	generarPiezaNueva(); 
}

Juego::~Juego(){
	liberarTablero(tablero);
	liberarCola(colaPiezas);
	liberarColaEventos(colaEventos);
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
	generarPiezaNueva();
}


void Juego::dibujarElementosJuego(){
	dibujarTablero(tablero);
	dibujarPieza(piezaActual);
	dibujarTresSiguientesPiezas();
	dibujarPiezaEnHold();
	dibujarMensajeEvento();
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
		generarPiezaNueva();
		
		if(marcarFilasCompletas(tablero) > 0){
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
		programarEvento(colaEventos, PUNTOS_DOBLES, tiempoJuego + 40.0f);
		
	}else if(tipo == PIEZA_FACIL){
		mostrandoMensajeEvento = true;
		eventoMostrado = tipo;
		tiempoMensajeEvento = duracionMensajeEvento;
		
		piezaFacilPendiente = true;
		programarEvento(colaEventos, PIEZA_FACIL, tiempoJuego + 60.0f);
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
		DrawText(texto, 450, 50, 30, RED);
	}
	
	if(puntosDoblesActivo){
		DrawText("Puntos dobles activos!", 450, 50, 30, ORANGE);
	}
}

bool Juego::haTerminado(){
	return juegoTerminado;
}

int Juego::obtenerPuntaje(){
	return puntaje;
}

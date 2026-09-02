#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H
#include "Pantalla.h"
#include "Jugador.h"
#include "raylib.h"
#include "Juego.h"


class InterfazGrafica {
	
private:
	
	Juego juego;
	Jugador jugadorActual;
	int anchoPantalla, altoPantalla;
	Pantalla pantallaActual = REGISTRO_JUGADOR;
	Texture2D fondo;
	Texture2D fondoCreditos;
	Texture2D fondoRegistroJugador;
	Texture2D fondoTopJugadores;
	Texture2D fondoJuego;
	Texture2D fondoPausa;
	Music musica;
	bool musicaActiva = false;
	bool juegoPausado = false;
	
	void cargarAssets();
	void liberarAssets();
	
	void registrarJugador();
	void mostrarMenu();
	void mostrarPuntuaciones();
	void mostrarCreditos();
	void mostrarJuego();
	void mostrarVistaPausa();
	void regresarAlMenu();
	void mostrarFinJuego();
	
public:
	InterfazGrafica(int ancho, int alto,const char* titulo);
	~InterfazGrafica(); // destructor :p
	void ejecutar(); // contiene el bucle while

};

#endif

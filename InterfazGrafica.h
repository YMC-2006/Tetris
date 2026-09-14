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
	Texture2D fondoFinJuego;
	Texture2D fondoElegirOrdenamientos;
	
	bool ordenamientoSimple = false;
	
	// botones
	Texture2D btnHogar; // para regresar al menu
	Texture2D btnJugarDeNuevo;
	Texture2D btnPausarJuego;
	Texture2D musicaON;
	//Texture2D musicaOFF;
	
	Music musica;
	bool musicaActiva = false;
	bool juegoPausado = false;
	
	void cargarAssets();
	void liberarAssets();
	
	void registrarJugador();
	void mostrarMenu();
	void mostrarPantallaElegirOrdenamiento();
	void mostrarPuntuaciones();
	void mostrarCreditos();
	void mostrarJuego();
	void mostrarReglasJuego();
	void mostrarVistaPausa();
	void regresarAlMenu();
	void mostrarFinJuego();
	
public:
	InterfazGrafica(int ancho, int alto,const char* titulo);
	~InterfazGrafica(); // destructor :p
	void ejecutar(); // contiene el bucle while
	
	void compararOrdenamientos();

};

#endif

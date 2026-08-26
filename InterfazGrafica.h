#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H
#include "Pantalla.h"
#include "Jugador.h"
#include "raylib.h"

class InterfazGrafica {
	
private:
	int anchoPantalla, altoPantalla;
	Pantalla pantallaActual = MENU;
	Texture2D fondo;
	Texture2D fondoCreditos;
	Music musica;
	bool musicaActiva = false;
	
	void cargarAssets();
	void liberarAssets();
	
	void mostrarMenu();
	void mostrarPuntuaciones();
	void mostrarCreditos();
	void mostrarJuego();
	void regresarAlMenu();
	
public:
	InterfazGrafica(int ancho, int alto, char* titulo);
	~InterfazGrafica(); // destructor :p
	void ejecutar(); // contiene el bucle while

};

#endif

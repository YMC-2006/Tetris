#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"
#include "Pieza.h"

class Juego{
	
public:
	Juego();
	~Juego();
	
	void moverPiezaConTeclado();
	void actualizar();
	void dibujarElementosJuego();
	int obtenerPuntaje();
	bool haTerminado();
	void reiniciar();
	
private:
	Tablero tablero;
	Pieza piezaActual;
	float temporizadorCaida = 0;
	const float intervaloCaida = 0.5f;
	int puntaje = 0;
	bool juegoTerminado = false;
	
	
	void generarPiezaNueva();
	void fijarPiezaEnTablero();
	
	
	
};
#endif

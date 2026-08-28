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
	
private:
	Tablero tablero;
	Pieza piezaActual;
	//Pieza piezaO;
	float temporizadorCaida = 0;
	const float intervaloCaida = 0.5f;
	
	void generarPiezaNueva();
	void fijarPiezaEnTablero();
	void limpiarLineasCompletas();
	
};
#endif

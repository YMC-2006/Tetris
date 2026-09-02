#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"
#include "Pieza.h"
#include "raylib.h"
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
	void pausar();
	
private:
	Tablero tablero;
	Pieza piezaActual;
	Rectangle btnPausa;
	float temporizadorCaida = 0;
	const float intervaloCaida = 0.5f;
	int puntaje = 0;
	bool juegoTerminado = false;
	
	// atributos para la animación
	bool animandoLimpieza = false;
	float temporizadorLimpieza = 0;
	const float duracionLimpieza = 0.3f;
	
	void generarPiezaNueva();
	void fijarPiezaEnTablero();
	
	
	
};
#endif

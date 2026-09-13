#ifndef JUEGO_H
#define JUEGO_H
#include "Tablero.h"
#include "Pieza.h"
#include "raylib.h"
#include "ColaPiezas.h"
#include "PilaHold.h"
#include "ColaEventos.h"
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
	PilaHold pilaHold;
	ColaPiezas colaPiezas;
	Pieza piezaActual;
	
	Rectangle btnPausa;
	float temporizadorCaida = 0;
	float intervaloCaida = 0.5f;
	const float intervaloCaidaRapida = 0.5f; // en veremos
	int puntaje = 0;
	bool juegoTerminado = false;
	
	
	// eventos especiales cola
	ColaEventos colaEventos;
	float tiempoJuego = 0;
	bool puntosDoblesActivo = false;
	float tiempoRestantePuntosDobles = 0;
	bool piezaFacilPendiente = false;
	
	bool mostrandoMensajeEvento = false;
	TipoEvento eventoMostrado;
	float tiempoMensajeEvento = 0;
	const float duracionMensajeEvento = 2.5f;
	
	void dibujarMensajeEvento();
	void aplicarEvento(TipoEvento tipo);
	void programarEventosIniciales();
	
	
	
	// atributos para la animación
	bool animandoLimpieza = false;
	float temporizadorLimpieza = 0;
	const float duracionLimpieza = 0.3f;
	
	void generarPiezaNueva();
	void fijarPiezaEnTablero();
	void dibujarTresSiguientesPiezas();
	void dibujarPiezaEnHold();
	
};
#endif

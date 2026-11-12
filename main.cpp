#include "raylib.h"
#include "InterfazGrafica.h"
	
int main(void){
	
	InterfazGrafica juego(1200, 850, "Tetris");
	juego.ejecutar();
	//juego.compararOrdenamientos();
	return 0;
}

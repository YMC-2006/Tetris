#include "raylib.h"
#include "InterfazGrafica.h"
	
int main(void){
	
	InterfazGrafica juego(1400, 1000, "Tetris");
	juego.ejecutar();
	
	return 0;
}

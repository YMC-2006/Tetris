#include "raylib.h"
#include "InterfazGrafica.h"
	
int main(void){
	
	InterfazGrafica juego(1400, 1050, "Tetris");
	juego.ejecutar();
	
	return 0;
}

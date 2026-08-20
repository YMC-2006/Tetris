#include "raylib.h"

int main(void)
{
	// 1. Inicializar la ventana
	const int screenWidth = 800;
	const int screenHeight = 850;
	InitWindow(screenWidth, screenHeight, "Ejemplo Basico Raylib 4.0.0");
	
	// 2. Fijar los fotogramas por segundo (FPS)
	SetTargetFPS(60);
	
	// 3. Bucle principal del juego
	while (!WindowShouldClose()) // Detecta si se presiona ESC o el botón de cerrar
	{
		// Actualización (Lógica del juego)
		// Aquí puedes actualizar variables, posiciones, etc.
		
		// Dibujo
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		DrawText("Hola, esto es raylib 4.0.0!", 190, 200, 20, LIGHTGRAY);
		DrawCircle(screenWidth / 2, screenHeight / 2 - 40, 50, MAROON);
		
		EndDrawing();
	}
	
	// 4. Cerrar y liberar recursos de la ventana
	CloseWindow();
	
	return 0;
}

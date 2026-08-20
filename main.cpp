#include "raylib.h"

int main(void){

	const int screenWidth = 1000;
	const int screenHeight = 1000;
	InitWindow(screenWidth, screenHeight, "Ejemplo Basico Raylib 4.0.0");
	

	SetTargetFPS(60);
	
	while (!WindowShouldClose()){

		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		DrawText("Hola, esto es raylib 4.0.0!", 190, 200, 20, LIGHTGRAY);
		DrawCircle(screenWidth / 2, screenHeight / 2 - 40, 50, MAROON);
		
		EndDrawing();
	}
	
	CloseWindow();
	
	return 0;
}

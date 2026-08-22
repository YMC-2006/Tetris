#include "raylib.h"

int main(void){
	
	const int screenWidth = 1400;
	const int screenHeight = 800;
	
	InitWindow(screenWidth, screenHeight, "Inicio Tetris");
	
	Rectangle btnJugar = {600, 500, 200, 60};
	Rectangle btnCreditos = {600, 600, 200, 60};
	Rectangle btnMejoresPts = {570, 700, 290, 60};
	
	while (!WindowShouldClose())
	{
		
		Vector2 mouse = GetMousePosition();
		if(CheckCollisionPointRec(mouse, btnJugar)&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			TraceLog(LOG_INFO, "Jugar Presionado");
		}
		
		if (CheckCollisionPointRec(mouse, btnCreditos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			TraceLog(LOG_INFO, "Creditos presionado");
		}
		
		if(CheckCollisionPointRec(mouse, btnMejoresPts) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			TraceLog(LOG_INFO, "Mejores pts presionado");
		}
		
	
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
		DrawRectangleRec(btnJugar, BLUE);
		DrawRectangleRec(btnCreditos, BLUE);
		DrawRectangleRec(btnMejoresPts, BLUE);
		
		
		if (CheckCollisionPointRec(mouse, btnJugar)){
			DrawRectangleRec(btnJugar, DARKBLUE);
		}
		else{
			DrawRectangleRec(btnJugar, BLUE);
		}
		DrawText("Jugar", 660, 520, 20, WHITE);
		
		
		
		if (CheckCollisionPointRec(mouse, btnCreditos)){
			DrawRectangleRec(btnCreditos, DARKBLUE);
		}
		else{
			DrawRectangleRec(btnCreditos, BLUE);
		}
		DrawText("Creditos", 660, 620, 20, WHITE);
		
		
		if(CheckCollisionPointRec(mouse, btnMejoresPts)){
			DrawRectangleRec(btnMejoresPts, DARKBLUE);
		}else{
			DrawRectangleRec(btnMejoresPts, BLUE);
		}
		DrawText("Mejores Puntuaciones", 600, 720, 20, WHITE);
		//                                x    y   font size
		EndDrawing();
	}
	
	CloseWindow();
	
	return 0;
}

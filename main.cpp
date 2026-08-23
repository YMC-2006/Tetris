#include "raylib.h"
#include "Pantalla.cpp"

Pantalla pantallaActual = MENU;
Texture2D fondo;
void cargarTexturas(){
	
}


void mostrarMenu(){
	
	DrawTexture(fondo, 0, 0, WHITE);
	
	Rectangle btnJugar = {600, 500, 200, 60};
	Rectangle btnCreditos = {600, 600, 200, 60};
	Rectangle btnMejoresPts = {570, 700, 290, 60};
	
	
	Vector2 mouse = GetMousePosition();
	if(CheckCollisionPointRec(mouse, btnJugar)&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Jugar Presionado");
		pantallaActual = JUEGO;
		
	}
	
	if (CheckCollisionPointRec(mouse, btnCreditos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Creditos presionado");
		pantallaActual = CREDITOS;
	}
	
	if(CheckCollisionPointRec(mouse, btnMejoresPts) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Mejores pts presionado");
		pantallaActual = PUNTUACIONES;
	}
	
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
	DrawText("Creditos", 650, 620, 20, WHITE);
	
	
	if(CheckCollisionPointRec(mouse, btnMejoresPts)){
		DrawRectangleRec(btnMejoresPts, DARKBLUE);
	}else{
		DrawRectangleRec(btnMejoresPts, BLUE);
	}
	DrawText("Mejores Puntuaciones", 600, 720, 20, WHITE);
	//                                x    y   font size
	
}

void regresarAlMenu(){
	Rectangle btnRegresar = {300, 200, 20, 20};
	DrawRectangleRec(btnRegresar, BLUE);
	Vector2 mouse = GetMousePosition();
	if(CheckCollisionPointRec(mouse, btnRegresar) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Regresando al menu...");
		pantallaActual = MENU;
	}
}

void mostrarPuntuaciones(){
	regresarAlMenu();
	DrawText("Mejores Puntuaciones", 500, 200, 40, BLUE);
	
}


	
void mostrarCreditos(){
	regresarAlMenu();
	DrawText("Creditos", 500, 200, 40, BLUE);
}


	
void mostrarJuego(){
	
	regresarAlMenu(); // dibuja el boton de regresar y si lo clickeo me tira al menu
	DrawText("TETRIS", 300, 500, 30, BLUE);
}
	
		
		
void iniciarJuego(){
	const int screenWidth = 1400;
	const int screenHeight = 1000;
		
	InitWindow(screenWidth, screenHeight, "Inicio Tetris");
	fondo = LoadTexture("Assets/fondo.png");
		
	// bucle del juego
	while (!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		if(pantallaActual == MENU){
			mostrarMenu();
		}else if(pantallaActual == PUNTUACIONES){
			mostrarPuntuaciones();
		}else if(pantallaActual == JUEGO){
			mostrarJuego();
		}else if(pantallaActual == CREDITOS){
			mostrarCreditos();
		}
		
		
		
		EndDrawing();
	}
		
	CloseWindow();
}

	
int main(void){
	
	
	iniciarJuego();
	
	return 0;
}

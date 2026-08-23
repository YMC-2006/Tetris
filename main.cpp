#include "raylib.h"
#include "Pantalla.cpp"

Pantalla pantallaActual = MENU;
Texture2D fondo;
Texture2D fondoCreditos;
Music musica;
bool musicaActiva = false;

void mostrarMenu(){
	
	DrawTexture(fondo, 0, 0, WHITE);
	
	Rectangle btnJugar = {600, 500, 200, 60};
	Rectangle btnCreditos = {600, 600, 200, 60};
	Rectangle btnMejoresPts = {570, 700, 290, 60};
	Rectangle btnSonidoOn = {100, 100, 30, 30};
	Rectangle btnSonidoOff = {100, 100, 30, 30};
	
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
	
	if(CheckCollisionPointRec(mouse, btnSonidoOn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		DrawRectangleRec(btnSonidoOn, BLUE);
		if(musicaActiva){
			StopMusicStream(musica);
			musicaActiva = false;
		}else{
			PlayMusicStream(musica);
			musicaActiva = true;
		}
	}else{
		DrawRectangleRec(btnSonidoOn, DARKBLUE);
	}
	
	// Hover
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
	DrawText("Mejores Puntuaciones", 500, 50, 40, BLUE);
	
}


	
void mostrarCreditos(){
	DrawTexture(fondoCreditos, 0, 0, WHITE);
	regresarAlMenu();
	DrawText("Creditos", 500, 50, 40, BLUE);
}


	
void mostrarJuego(){
	
	regresarAlMenu(); // dibuja el boton de regresar y si lo clickeo me tira al menu
	DrawText("TETRIS", 500, 50, 30, BLUE);
}

void cargarAssets(){
	fondo = LoadTexture("assets/fondo.png");
	fondoCreditos = LoadTexture("assets/creditosFondo.png");
	musica = LoadMusicStream("assets/FrozenPines.wav");
	
}
		
		
void iniciarJuego(){
	const int screenWidth = 1400;
	const int screenHeight = 1000;
		
	InitWindow(screenWidth, screenHeight, "Inicio Tetris");
	InitAudioDevice();
	cargarAssets();
	musica.looping = true;
	
	
		
	// bucle del juego
	while (!WindowShouldClose()){
		//musica cuando presiono el btn de sound 
		UpdateMusicStream(musica);
		
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
		
	
	// Liberar
	UnloadMusicStream(musica);
	CloseAudioDevice();
	CloseWindow();
}

	
int main(void){
	
	
	iniciarJuego();
	
	return 0;
}

#include "raylib.h"
#include "Pantalla.cpp"
#include "Jugador.h"

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
	
	// SONIDO
	if(CheckCollisionPointRec(mouse, btnSonidoOn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		
		if(musicaActiva){
			StopMusicStream(musica);
			musicaActiva = false;
		}else{
			PlayMusicStream(musica);
			musicaActiva = true;
		}
	}
	
	if(musicaActiva){
		DrawRectangleRec(btnSonidoOn, DARKBLUE);
	}else{
		DrawRectangleRec(btnSonidoOn, BLUE);
	}
	
	// Hover
	if (CheckCollisionPointRec(mouse, btnJugar)){
		DrawRectangleRec(btnJugar, DARKBLUE);
	}
	else{
		DrawRectangleRec(btnJugar, BLUE);
	}
	DrawText("Jugar", 660, 520, 20, WHITE);
	
	
	// Hover
	if (CheckCollisionPointRec(mouse, btnCreditos)){
		DrawRectangleRec(btnCreditos, DARKBLUE);
	}
	else{
		DrawRectangleRec(btnCreditos, BLUE);
	}
	DrawText("Creditos", 650, 620, 20, WHITE);
	
	// Hover
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

	
	void ordenarPuntuaciones(Jugador jugadores[], int cantidad){
		
		for(int i = 0; i < cantidad - 1; i++){
			for(int j = 0; j < cantidad - 1 - i; j++){
				if(jugadores[j].puntaje < jugadores[j+1].puntaje){
					Jugador temp = jugadores[j];
					jugadores[j] = jugadores[j+1];
					jugadores[j+1] = temp;
					
				}
			}
		}
	}
		

void mostrarPuntuaciones(){
	regresarAlMenu();
	DrawText("Mejores Puntuaciones", 500, 50, 40, BLUE);
	
	
	Jugador jugadores[10] = { 
		{"Maria", 1100},{"Luis", 1000},{"Sofia", 900},{"Diego", 800},{"Laura", 700},
		{"Juan", 600},{"Elena", 500},{"Carlos", 1500},{"Ana", 1300},{"Pedro", 1200}
	};
	
	
	ordenarPuntuaciones(jugadores, 10);
	
	DrawText("NOMBRE", 500, 180, 20, BLACK);
	DrawText("PUNTAJE", 800, 180, 20, BLACK);
	
	for(int i = 0; i < 10;i++){
		DrawText(jugadores[i].nombre, 500, 220 + i * 40, 20, BLACK);
		DrawText(TextFormat("%d",jugadores[i].puntaje), 800, 220 + i * 40, 20, BLACK );
	}
	
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
	
	UnloadTexture(fondo);
	UnloadTexture(fondoCreditos);
	
	CloseWindow();
}

	

	
	
int main(void){
	
	
	iniciarJuego();
	
	return 0;
}

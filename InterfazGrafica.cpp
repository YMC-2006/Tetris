#include "InterfazGrafica.h"

InterfazGrafica::InterfazGrafica(int ancho, int alto,const  char* titulo){
	
	anchoPantalla = ancho;
	altoPantalla = alto;
	
	InitWindow(anchoPantalla, altoPantalla, titulo);
	InitAudioDevice();
	cargarAssets();
	musica.looping = true;
}

InterfazGrafica::~InterfazGrafica(){
	liberarAssets();
	CloseAudioDevice();
	CloseWindow();
}
	
void InterfazGrafica::cargarAssets(){
	fondo = LoadTexture("assets/fondo.png");
	fondoCreditos = LoadTexture("assets/creditos.png");
	fondoRegistroJugador = LoadTexture("assets/fondoRegistroJugador.png");
	fondoTopJugadores = LoadTexture("assets/fondoTopJugadores.png");
	//fondoJuego = LoadTexture("assets/JuegoFondo.png");
	musica = LoadMusicStream("assets/FrozenPines.wav");
}
	
void InterfazGrafica::liberarAssets(){
	UnloadMusicStream(musica);
	UnloadTexture(fondo);
	UnloadTexture(fondoCreditos);
	UnloadTexture(fondoRegistroJugador);
	UnloadTexture(fondoTopJugadores);
}
	


void InterfazGrafica::registrarJugador(){
	
	DrawTexture(fondoRegistroJugador, 0, 0, WHITE);
	
	Color rosadoClaro = {255, 182, 193, 255};
	Color rosadoOscuro = {219, 112, 147, 255};
	
	
	Rectangle cajaTexto = {500, 350, 330, 50};
	DrawRectangleRec(cajaTexto, rosadoClaro);
	DrawRectangleLinesEx(cajaTexto, 2, rosadoOscuro);
	
	
	int tecla = GetCharPressed();
	while(tecla > 0){
		if(tecla >= 32 && tecla <= 125 && jugadorActual.nombre.length() < 15){
			jugadorActual.nombre += (char)tecla;
		}
		tecla = GetCharPressed();
	}
	
	if(IsKeyPressed(KEY_BACKSPACE) && !jugadorActual.nombre.empty()){
		jugadorActual.nombre.pop_back();
	}
	
	DrawText(jugadorActual.nombre.c_str(), (int)cajaTexto.x + 10, (int)cajaTexto.y + 12, 20, BLACK);
	DrawText("Presiona ENTER para continuar", 500, 490, 20, rosadoOscuro);
	
	if(IsKeyPressed(KEY_ENTER) && !jugadorActual.nombre.empty()){
		pantallaActual = MENU;
	}

}


void InterfazGrafica::mostrarMenu(){
		
	DrawTexture(fondo, 0, 0, WHITE);
	
	Color rosado = {245, 130, 180, 255};
	Color naranja = {245, 145, 70, 255};
	Color verde = {195, 210, 70, 255};
	Color aqua = {105, 205, 195, 255};
	
	Rectangle btnJugar = {600, 500, 260, 60};
	Rectangle btnCreditos = {605, 600, 250, 60};
	Rectangle btnMejoresPts = {540, 700, 380, 60};
	Rectangle btnSonidoOn = {100, 100, 30, 30};
		
	Vector2 mouse = GetMousePosition();
	if(CheckCollisionPointRec(mouse, btnJugar) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
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
		DrawRectangleRec(btnJugar, verde);
	}else{
		DrawRectangleRec(btnJugar, rosado);
	}
	DrawText("Jugar", 670, 520, 30, WHITE);
	
	// Hover
	if (CheckCollisionPointRec(mouse, btnCreditos)){
		DrawRectangleRec(btnCreditos, verde);
	}else{
		DrawRectangleRec(btnCreditos, naranja);
	}
	DrawText("Creditos", 650, 620, 30, WHITE);

		// Hover
	if(CheckCollisionPointRec(mouse, btnMejoresPts)){
		DrawRectangleRec(btnMejoresPts, verde);
	}else{
		DrawRectangleRec(btnMejoresPts, aqua);
	}
	DrawText("Mejores Puntuaciones", 600, 720, 25, WHITE);
}
	
void InterfazGrafica::regresarAlMenu(){
	Rectangle btnRegresar = {300, 200, 20, 20};
	DrawRectangleRec(btnRegresar, BLUE);
	Vector2 mouse = GetMousePosition();
	if(CheckCollisionPointRec(mouse, btnRegresar) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Regresando al menu...");
		pantallaActual = MENU;
	}
}
	
	// preguntar a la profe si cambiar de ubicacion
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
		
void InterfazGrafica::mostrarPuntuaciones(){
	DrawTexture(fondoTopJugadores, 0, 0, WHITE);
	regresarAlMenu();
		
	Jugador jugadores[10] = {
		{"Maria", 1100},{"Luis", 1000},{"Sofia", 900},{"Diego", 800},{"Laura", 700},
		{"Juan", 600},{"Elena", 500},{"Carlos", 1500},{"Ana", 1300},{"Pedro", 1200}
	};

	ordenarPuntuaciones(jugadores, 10);
	
	
	for(int i = 0; i < 10; i++){
		DrawText(jugadores[i].nombre.c_str(), 500, 410 + i * 50, 25, BLACK);
		DrawText(TextFormat("%d", jugadores[i].puntaje), 850, 410 + i * 50, 25, BLACK);
	}
}

void InterfazGrafica::mostrarCreditos(){
		DrawTexture(fondoCreditos, 0, 0, WHITE);
		regresarAlMenu();
		DrawText("Creditos", 500, 50, 40, BLUE);
}
		
void InterfazGrafica::mostrarJuego(){
	regresarAlMenu();

	
	juego.moverPiezaConTeclado();
	juego.actualizar();
	juego.dibujarElementosJuego();

}
		
void InterfazGrafica::ejecutar(){
		
		
		while (!WindowShouldClose()){
		UpdateMusicStream(musica);
	
		BeginDrawing();
		ClearBackground(RAYWHITE);
	
		
		if(pantallaActual == MENU){
			mostrarMenu();
		}else if(pantallaActual == REGISTRO_JUGADOR){
			registrarJugador();
		}else if(pantallaActual == PUNTUACIONES){
			mostrarPuntuaciones();
		}else if(pantallaActual == JUEGO){
			mostrarJuego();
		}else if(pantallaActual == CREDITOS){
			mostrarCreditos();
		}
		EndDrawing();
	}
}

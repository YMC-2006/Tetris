#include "InterfazGrafica.h"
#include <fstream>
using namespace std;
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
	fondoJuego = LoadTexture("assets/JuegoFondo.png");
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
		jugadorActual.puntaje = 0;
		pantallaActual = MENU;
	}

}


void InterfazGrafica::mostrarFinJuego(){
	DrawText("FIN DEL JUEGO", anchoPantalla/2 - 150, 200, 40, RED);
	DrawText(TextFormat("Puntaje final: %d", juego.obtenerPuntaje()), anchoPantalla/2 - 130, 270, 30, BLACK);
	
	Rectangle botonJugar = {anchoPantalla/2.0f - 100, 350, 200, 50};
	DrawRectangleRec(botonJugar, LIGHTGRAY);
	DrawText("Jugar de nuevo", (int)botonJugar.x + 20, (int)botonJugar.y + 15, 20, BLACK);
	
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botonJugar)){
		juego.reiniciar();
		pantallaActual = JUEGO;
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
	
// PERSISTENCIA USANDO ARCHIVOS .TXT
	
int cargarPuntuaciones(Jugador jugadores[], int maximo){
	ifstream archivoPuntuaciones("tetrisPuntuaciones.txt");
	if(!archivoPuntuaciones.is_open()){
		return 0;
	}
	
	int cantidad = 0;
	string nombre;
	int puntaje;
	
	
	while(cantidad < maximo && archivoPuntuaciones >> nombre >> puntaje){
		jugadores[cantidad].nombre = nombre;
		jugadores[cantidad].puntaje = puntaje;
		cantidad++;
	}
	
	archivoPuntuaciones.close();
	return cantidad;
}
	
void guardarPuntuaciones(Jugador jugadores[], int cantidad){
	ofstream archivoPuntuaciones("tetrisPuntuaciones.txt");
	for(int i = 0; i < cantidad; i++){
		archivoPuntuaciones << jugadores[i].nombre << " " << jugadores[i].puntaje << "\n";
	}
	archivoPuntuaciones.close();
}
	
void guardarSiCalifica(Jugador jugador){
	Jugador jugadores[11];
	int cantidad = cargarPuntuaciones(jugadores, 10);
	jugadores[cantidad] = jugador;
	cantidad++;
	ordenarPuntuaciones(jugadores, cantidad);
	if(cantidad > 10){
		cantidad = 10;
	}
	guardarPuntuaciones(jugadores, cantidad);
}
	
	

		
void InterfazGrafica::mostrarPuntuaciones(){
	DrawTexture(fondoTopJugadores, 0, 0, WHITE);
	regresarAlMenu();
		
	Jugador jugadores[10];
	int cantidad = cargarPuntuaciones(jugadores, 10);
	ordenarPuntuaciones(jugadores, cantidad);
	
	
	for(int i = 0; i < cantidad; i++){
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
	DrawTexture(fondoJuego, 0, 0, WHITE);
	regresarAlMenu();
	juego.pausar();
	
	if(juego.haTerminado()){
		
		jugadorActual.puntaje = juego.obtenerPuntaje();
		guardarSiCalifica(jugadorActual);
		pantallaActual = FIN_JUEGO;
		return;
	}
	
	
	juego.moverPiezaConTeclado();
	juego.actualizar();
	juego.dibujarElementosJuego();
	DrawText(TextFormat("Puntaje: %d", juego.obtenerPuntaje()), 50, 50, 25, BLACK);
	

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
		}else if(pantallaActual == FIN_JUEGO){
			mostrarFinJuego(); 
		}
		EndDrawing();
	}
}

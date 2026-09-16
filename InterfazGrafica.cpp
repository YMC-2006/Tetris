#include "InterfazGrafica.h"
#include <fstream>
#include <ctime>
using namespace std;
InterfazGrafica::InterfazGrafica(int ancho, int alto,const  char* titulo){
	
	anchoPantalla = ancho;
	altoPantalla = alto;
	
	InitWindow(anchoPantalla, altoPantalla, titulo);
	InitAudioDevice();
	cargarAssets();
	musica.looping = true;
	
	
	
	// PARA EL REPLAY
	crearTablero(tableroReplay);
	pasoReplay = 0;
	totalPasosReplay = 0;
	btnVerReplay       = { 400, 500, 250, 60 };
	btnReplayAtras     = { 900, 300, 180, 50 };
	btnReplayAdelante  = { 320, 700, 180, 50 };
	btnReplayRepetir   = { 520, 700, 180, 50 };
	btnReplayVolver    = { 720, 700, 180, 50 };
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
	fondoPausa = LoadTexture("assets/fondoPausa.png");
	fondoFinJuego = LoadTexture("assets/fondoFinJuego.png");
	fondoElegirOrdenamientos = LoadTexture("assets/fondoElegirOrdenamientos.png");
	
	// botones
	btnHogar = 	LoadTexture("assets/btnHogar.png");
	btnJugarDeNuevo = LoadTexture("assets/btnReplay.png");
	btnPausarJuego = LoadTexture("assets/btnPausa.png");
	//btnMusicaON = LoadTexture("assets/musicaON.png");
	
	
	musica = LoadMusicStream("assets/FrozenPines.wav");
	compararOrdenamientos();
}
	
void InterfazGrafica::liberarAssets(){
	UnloadMusicStream(musica);
	UnloadTexture(fondo);
	UnloadTexture(fondoCreditos);
	UnloadTexture(fondoRegistroJugador);
	UnloadTexture(fondoTopJugadores);
	UnloadTexture(fondoPausa);
	UnloadTexture(fondoElegirOrdenamientos);
	
	//liberar btns
	UnloadTexture(btnHogar);
	
	liberarTablero(tableroReplay);
	
	UnloadTexture(fondoFinJuego);
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
	DrawTexture(fondoFinJuego, 0, 0, WHITE);
	DrawText(TextFormat("%d",juego.obtenerPuntaje()), anchoPantalla/2 - 130, 700, 45, BLACK);
	
	// tamaño y posición para el botón
	Rectangle btnHogarRect = { 600, 840, 100, 80 }; // x, y, ancho, alto
	Rectangle origenHogar = { 0, 0, (float)btnHogar.width, (float)btnHogar.height };
	DrawTexturePro(btnHogar, origenHogar, btnHogarRect, {0, 0}, 0.0f, WHITE);
	
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnHogarRect)) {
		pantallaActual = MENU; // o la pantalla que corresponda para "ir al hogar"
		juego.reiniciar();
	}
	
	Rectangle btnJugarRect = {730, 840,  100, 90};
	Rectangle origenJugar = {0, 0, (float)btnJugarDeNuevo.width, (float)btnJugarDeNuevo.height };
	DrawTexturePro(btnJugarDeNuevo, origenJugar, btnJugarRect, {0,0}, 0.0f, WHITE);
	

	
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnJugarRect)){
		juego.reiniciar();
		pantallaActual = JUEGO;
	}
	
	// para el replay
	DrawRectangleRec(btnVerReplay, LIGHTGRAY);
	DrawText("Ver replay", (int)btnVerReplay.x + 45, (int)btnVerReplay.y + 18, 25, BLACK);
	
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
	   CheckCollisionPointRec(GetMousePosition(), btnVerReplay)){
		totalPasosReplay = contarColocaciones();
		pasoReplay = 0;
		reconstruirReplay(0);
		pantallaActual = REPLAY;
	}
}

void InterfazGrafica::mostrarVistaPausa(){

	DrawTexture(fondoPausa, 0, 0, WHITE);
	Rectangle btnReanudar = {500, 400, 300, 80};
	Rectangle btnSalir = {500, 520, 300, 80};
	
	Vector2 mouse = GetMousePosition();
	
	// REANUDAR
	if(CheckCollisionPointRec(mouse, btnReanudar) &&
	   IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		
		TraceLog(LOG_INFO, "Reanudando juego...");
		juegoPausado = false;
	}
	
	   
	  // SALIR
	if(CheckCollisionPointRec(mouse, btnSalir) &&
	  IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
	   
	   TraceLog(LOG_INFO, "Saliendo del juego...");
	   juegoPausado = false;
	   pantallaActual = MENU;
	} 
	  
	Color rosado = {255, 169, 221, 255}; 
	Color lila = {232, 192, 252, 255};  
	  
	DrawRectangleRec(btnReanudar, rosado);
	DrawRectangleRec(btnSalir, lila);
	
	DrawText("REANUDAR", 575, 425, 30, WHITE);
	DrawText("SALIR", 610, 545, 30, WHITE);
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
	Rectangle btnReglas = {590, 800, 270, 60};
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
		pantallaActual = ELEGIR_ORDENAMIENTO;
	}
	
	if(CheckCollisionPointRec(mouse, btnReglas) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Reglas btn presionado");
		pantallaActual = REGLAS_JUEGO;
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
		
	// Hover JUGAR
	if (CheckCollisionPointRec(mouse, btnJugar)){
		DrawRectangleRec(btnJugar, verde);
	}else{
		DrawRectangleRec(btnJugar, rosado);
	}
	DrawText("Jugar", 680, 520, 30, WHITE);
	
	// Hover CREDITOS
	if (CheckCollisionPointRec(mouse, btnCreditos)){
		DrawRectangleRec(btnCreditos, verde);
	}else{
		DrawRectangleRec(btnCreditos, naranja);
	}
	DrawText("Creditos", 660, 610, 30, WHITE);
	
	// Hover MEJORES PUNTUACIONES
	if(CheckCollisionPointRec(mouse, btnMejoresPts)){
		DrawRectangleRec(btnMejoresPts, verde);
	}else{
		DrawRectangleRec(btnMejoresPts, aqua);
	}
	DrawText("Mejores Puntuaciones", 600, 720, 25, WHITE);
	
	if(CheckCollisionPointRec(mouse, btnReglas)){
		DrawRectangleRec(btnReglas, verde);
	}else{
		DrawRectangleRec(btnReglas, rosado);
	}
	DrawText("Reglas Juego", 640, 820, 25, WHITE);
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

	
void mezclar(Jugador jugadores[], int inicio, int medio, int fin){
	
	int tamIzquierda = medio - inicio + 1;
	int tamDerecha = fin - medio;
	
	Jugador* izquierda = new Jugador[tamIzquierda];
	Jugador* derecha = new Jugador[tamDerecha];
	
	for(int i = 0; i < tamIzquierda; i++){
		izquierda[i] = jugadores[inicio + i];
	}
	for(int j = 0; j < tamDerecha; j++){
		derecha[j] = jugadores[medio + 1 + j];
	}
	
	int i = 0, j = 0, k = inicio;
	
	// revisamos la condicion para hacer el merging
	while(i < tamIzquierda && j < tamDerecha){
		if(izquierda[i].puntaje >= derecha[j].puntaje){
			jugadores[k] = izquierda[i];
			i++;
		}else{
			jugadores[k] = derecha[j];
			j++;
		}
		k++;
	}
	
	while(i < tamIzquierda){
		jugadores[k] = izquierda[i];
		i++;
		k++;
	}
	
	while(j < tamDerecha){
		jugadores[k] = derecha[j];
		j++;
		k++;
	}
	
	delete[] izquierda;
	delete[] derecha;
	
}
	
	
void mergeSort(Jugador jugadores[], int inicio, int fin){
	if(inicio >= fin){
		return;   // caso base 0 o 1 elemento, ya está ordenado
	}
	
	int medio = (inicio + fin) / 2;
	
	mergeSort(jugadores, inicio, medio);       // ordena la mitad izquierda
	mergeSort(jugadores, medio + 1, fin);      // ordena la mitad derecha
	mezclar(jugadores, inicio, medio, fin);    // mezcla ambas ya ordenadas
}

void bubbleSort(Jugador jugadores[], int cantidad){
	// bubble sort para ordenar de mayor a menor
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
	//mergeSort(jugadores, 0, cantidad - 1);
	if(cantidad > 10){
		cantidad = 10;
	}
	guardarPuntuaciones(jugadores, cantidad);
}
	
	
void InterfazGrafica::mostrarPantallaElegirOrdenamiento(){
	DrawTexture(fondoElegirOrdenamientos, 0, 0, WHITE);
	Rectangle btnMergeSort = {300, 400, 300, 100};
	DrawRectangleRec(btnMergeSort, PINK);
	DrawText("Merge Sort", 320, 440, 35, WHITE);
	
	Rectangle btnBubbleSort = {700, 400, 300, 100};
	DrawRectangleRec(btnBubbleSort, PURPLE);
	DrawText("Bubble Sort", 720, 440, 35, WHITE);
	
	Vector2 mouse = GetMousePosition();
	
	if(CheckCollisionPointRec(mouse, btnMergeSort)&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Btn merge sort presionado");
		ordenamientoSimple = false;
		pantallaActual = PUNTUACIONES;
	}
	
	if(CheckCollisionPointRec(mouse, btnBubbleSort)&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		TraceLog(LOG_INFO, "Btn bubble sort presionado");
		ordenamientoSimple = true;
		pantallaActual = PUNTUACIONES;
	}
	
	
}
		
void InterfazGrafica::mostrarPuntuaciones(){
	
	DrawTexture(fondoTopJugadores, 0, 0, WHITE);
	regresarAlMenu();
	Jugador jugadores[10];
	int cantidad = cargarPuntuaciones(jugadores, 10);
	if(ordenamientoSimple){
		bubbleSort(jugadores, cantidad);
		//TraceLog(LOG_INFO, "Ordenado con bubble sort");
	}else{
		mergeSort(jugadores, 0 , cantidad -1);
		//TraceLog(LOG_INFO, "Ordenado con merge sort");
	}
	
	for(int i = 0; i < cantidad; i++){
		DrawText(jugadores[i].nombre.c_str(), 500, 410 + i * 50, 25, BLACK);
		DrawText(TextFormat("%d", jugadores[i].puntaje), 850, 410 + i * 50, 25, BLACK);
	}
}

void InterfazGrafica::mostrarCreditos(){
		DrawTexture(fondoCreditos, 0, 0, WHITE);
		regresarAlMenu();
}
		
void InterfazGrafica::mostrarJuego(){
	
	DrawTexture(fondoJuego, 0, 0, WHITE);
	
	Rectangle btnPausa = {100, 100, 50, 20};
	DrawRectangleRec(btnPausa, RED);
	Vector2 mouse = GetMousePosition();
	
	if(CheckCollisionPointRec(mouse, btnPausa) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		juegoPausado = true;
		TraceLog(LOG_INFO, "PAUSANDO EL JUEGO...");
	}
	
	// Si el juego está pausado, mostramos la vista de pausa
	if(juegoPausado){
		mostrarVistaPausa();
		return;
	}
	
	if(juego.haTerminado()){
		
		jugadorActual.puntaje = juego.obtenerPuntaje();
		guardarSiCalifica(jugadorActual);
		pantallaActual = FIN_JUEGO;
		return;
	}
	
	
	juego.dibujarElementosJuego();
	DrawText(TextFormat("Puntaje: %d", juego.obtenerPuntaje()), 50, 50, 25, BLACK);
	DrawText("HOLD", 1090, 90, 35, PINK);
	juego.moverPiezaConTeclado();
	juego.actualizar();

}
	

void InterfazGrafica::mostrarReglasJuego(){
	regresarAlMenu();
	DrawText("Creditos", 500, 50, 40, BLUE);
}



void InterfazGrafica::ejecutar(){
		
		if( !juegoPausado ){
			
			while (!WindowShouldClose()){
				UpdateMusicStream(musica);
				
				BeginDrawing();
				ClearBackground(RAYWHITE);
				
				
				if(pantallaActual == MENU){
					juego.reiniciar();
					mostrarMenu();
				}else if(pantallaActual == REGISTRO_JUGADOR){
					registrarJugador();
				}else if(pantallaActual == ELEGIR_ORDENAMIENTO){
					mostrarPantallaElegirOrdenamiento();
				}else if(pantallaActual == PUNTUACIONES){
					mostrarPuntuaciones();
				}else if(pantallaActual == JUEGO){
					mostrarJuego();
				}else if(pantallaActual == CREDITOS){
					mostrarCreditos();
				}else if(pantallaActual == FIN_JUEGO){
					mostrarFinJuego(); 
				}else if(pantallaActual == REGLAS_JUEGO){
					mostrarReglasJuego();
				}else if(pantallaActual == REPLAY){
					mostrarReplay();
				}
				EndDrawing();
			}
			
			
		}
		
}





void generarDatosPrueba(Jugador jugadores[], int cantidad){
	for(int i = 0; i < cantidad; i++){
		jugadores[i].nombre = "Prueba" + std::to_string(i);
		jugadores[i].puntaje = GetRandomValue(0, 999999);
	}
}
	
void copiarArreglo(Jugador origen[], Jugador destino[], int cantidad){
	for(int i = 0; i < cantidad; i++){
		destino[i] = origen[i];
	}
}
	
	
	
int InterfazGrafica::contarColocaciones(){
	int total = 0;
	NodoReplay* actual = juego.obtenerHistorial().primero;
	// lo importante es recorrer el historial y contar cuando colocamos un pieza
	while(actual != nullptr){
		if(actual->tipo == MOV_COLOCAR){
			total++; 
		}
		actual = actual->siguiente;
	}
	return total;
}

// para reiniciar el replay
void InterfazGrafica::reconstruirReplay(int hastaPaso){
	liberarTablero(tableroReplay);
	crearTablero(tableroReplay);
	
	int colocadas = 0;
	NodoReplay* actual = juego.obtenerHistorial().primero;
	while(actual != nullptr && colocadas < hastaPaso){
		if(actual->tipo == MOV_COLOCAR){
			ponerPiezaEnTablero(tableroReplay, actual->estadoPieza);
			limpiarFilaCompleta(tableroReplay);
			colocadas++;
		}
		actual = actual->siguiente;
	}
}
	
void InterfazGrafica::mostrarReplay(){
	DrawText("REPLAY", 460, 30, 45, PINK);
	dibujarTablero(tableroReplay);
	DrawText(TextFormat("Pieza %d de %d", pasoReplay, totalPasosReplay), 100, 120, 25, BLACK);
	
	DrawRectangleRec(btnReplayAtras, LIGHTGRAY);
	DrawText("<< Atras", (int)btnReplayAtras.x + 35, (int)btnReplayAtras.y + 15, 20, BLACK);
	DrawRectangleRec(btnReplayAdelante, LIGHTGRAY);
	DrawText("Adelante >>", (int)btnReplayAdelante.x + 20, (int)btnReplayAdelante.y + 15, 20, BLACK);
	DrawRectangleRec(btnReplayRepetir, LIGHTGRAY);
	DrawText("Repetir", (int)btnReplayRepetir.x + 45, (int)btnReplayRepetir.y + 15, 20, BLACK);
	DrawRectangleRec(btnReplayVolver, LIGHTGRAY);
	DrawText("Volver", (int)btnReplayVolver.x + 50, (int)btnReplayVolver.y + 15, 20, BLACK);
		
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		Vector2 mouse = GetMousePosition();
		if(CheckCollisionPointRec(mouse, btnReplayAdelante) && pasoReplay < totalPasosReplay){
			pasoReplay++;
			reconstruirReplay(pasoReplay);
		}
		if(CheckCollisionPointRec(mouse, btnReplayAtras) && pasoReplay > 0){
			pasoReplay--;
			reconstruirReplay(pasoReplay);
		}
		if(CheckCollisionPointRec(mouse, btnReplayRepetir)){
			pasoReplay = 0;
			reconstruirReplay(pasoReplay);
		}
		if(CheckCollisionPointRec(mouse, btnReplayVolver)){
			pantallaActual = FIN_JUEGO;
		}
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
void InterfazGrafica::compararOrdenamientos(){
	int tamanos[] = {10, 100, 1000, 10000};

	
	for(int t = 0; t < 4; t++){
		int n = tamanos[t];
		
		Jugador* original = new Jugador[n];
		Jugador* copiaBubble = new Jugador[n];
		Jugador* copiaMerge = new Jugador[n];
		
		generarDatosPrueba(original, n);
		copiarArreglo(original, copiaBubble, n);
		copiarArreglo(original, copiaMerge, n);
	
		clock_t inicioBubble = clock();
		bubbleSort(copiaBubble, n);
		clock_t finBubble = clock();
		double tiempoBubble = (double)(finBubble - inicioBubble) / CLOCKS_PER_SEC;
			
		clock_t inicioMerge = clock();
		mergeSort(copiaMerge, 0, n - 1);
		clock_t finMerge = clock();
		double tiempoMerge = (double)(finMerge - inicioMerge) / CLOCKS_PER_SEC;
			
		TraceLog(LOG_INFO, TextFormat("n=%d | burbuja: %f s | merge: %f s", n, tiempoBubble, tiempoMerge));
			
			delete[] original;
			delete[] copiaBubble;
			delete[] copiaMerge;
		}
}

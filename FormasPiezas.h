#ifndef FORMASPIEZAS_H
#define FORMASPIEZAS_H

struct Offset{
	int dx;
	int dy;
};



const Offset FORMA_T[4][4] = {
	{ {-1,0}, {0,0}, {1,0}, {0,-1} }, // orientacion 0 -> T apuntando arriba
	{ {0,-1}, {0,0}, {0,1}, {1,0}  }, // orientacion 1 -> T apuntando a la derecha
	{ {-1,0}, {0,0}, {1,0}, {0,1}  }, // orientacion 2 -> T apuntando abajo
	{ {0,-1}, {0,0}, {0,1}, {-1,0} }  // orientacion 3 -> T apuntando a la izquierda
};

#endif

#ifndef FORMASPIEZAS_H
#define FORMASPIEZAS_H

struct Offset{
	int dx;
	int dy;
};


// 1
const Offset FORMA_T[4][4] = {
	{ {-1,0}, {0,0}, {1,0}, {0,-1}}, // orientacion 0 -> T apuntando arriba
	{ {0,-1}, {0,0}, {0,1}, {1,0}}, // orientacion 1 -> T apuntando a la derecha
	{ {-1,0}, {0,0}, {1,0}, {0,1}}, // orientacion 2 -> T apuntando abajo
	{ {0,-1}, {0,0}, {0,1}, {-1,0}}  // orientacion 3 -> T apuntando a la izquierda
};

// 2
const Offset FORMA_O[4][4] = {
	{{-1,0}, {0,0}, {-1,-1}, {0,-1}}, // lo mismo para las 4 orientaciones
	{{-1,0}, {0,0}, {-1,-1}, {0,-1}},
	{{-1,0}, {0,0}, {-1,-1}, {0,-1}},
	{{-1,0}, {0,0}, {-1,-1}, {0,-1}}
};

// 3
const Offset FORMA_L[4][4] = {
	{{1,-1}, {1,0}, {0,0}, {-1,0} },   // orientacion 0
	{{1,1}, {0,1}, {0,0}, {0,-1} },    // orientacion 1
	{ {-1,1}, {-1,0}, {0,0}, {1,0} },   // orientacion 2
	{{-1,-1}, {0,-1}, {0,0}, {0,1} }   // orientacion 3
};

// 4 orientaciones distintas
const Offset FORMA_J[4][4] = {
	{ {-1,-1}, {-1,0}, {0,0}, {1,0} },  // orientacion 0
	{{1,-1}, {0,-1}, {0,0}, {0,1} },   // orientacion 1
	{{1,1}, {1,0}, {0,0}, {-1,0} },    // orientacion 2
	{{-1,1}, {0,1}, {0,0}, {0,-1} }    // orientacion 3
};

// 5
const Offset FORMA_S[4][4] = {
	
	{{0,-1}, {1,-1}, {-1,0}, {0,0}},  // orientacion 0
	{{1,0}, {1,1}, {0,-1}, {0,0}},    // orientacion 1
	{{0,-1}, {1,-1}, {-1,0}, {0,0}},  // orientacion 2 -> igual a la 0
	{{1,0}, {1,1}, {0,-1}, {0,0} }     // orientacion 3 -> igual a la 1
	
};

//6
const Offset FORMA_Z[4][4] = {
	{ {0,-1}, {-1,-1}, {1,0}, {0,0} },   // orientacion 0
	{{-1,0}, {-1,1}, {0,-1}, {0,0} },   // orientacion 1
	{ {0,-1}, {-1,-1}, {1,0}, {0,0} },   // orientacion 2 -> igual a la 0
	{{-1,0}, {-1,1}, {0,-1}, {0,0} }    // orientacion 3 -> igual a la 1
};

//7
const Offset FORMA_I[4][4] = {
	{{-1,0}, {0,0}, {1,0}, {2,0} },  // orientacion 0 -> horizontal
	{{0,-1}, {0,0}, {0,1}, {0,2} },  // orientacion 1 -> vertical
	{ {-1,0}, {0,0}, {1,0}, {2,0} },  // orientacion 2 -> igual a la 0
	{{0,-1}, {0,0}, {0,1}, {0,2} }   // orientacion 3 -> igual a la 1
	
};
#endif

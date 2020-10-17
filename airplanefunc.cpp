#include "airplanefunc.h"

struct Info {
	int id ;
	int fuel ;
};

struct Airplane {
	Info inf ;
	Airplane *next ;
};

struct Row {
	int qt ;
	int cod ;
	
	Airplane *first ;
};

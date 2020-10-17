#ifndef AIRPLANEFUNC_H
#define AIRPLANEFUNC_H

struct Info {
	int id ;
	int fuel ;
};

struct Plane {
	Info inf ;
	Plane *next ;
};

struct Row {
	int qt ;
	
	Plane *first ;
};

Plane* createPlane() ;

int generatePlanes() ;



#endif

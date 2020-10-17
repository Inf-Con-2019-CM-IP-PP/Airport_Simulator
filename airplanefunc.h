#ifndef AIRPLANEFUNC_H
#define AIRPLANEFUNC_H

struct Info {
	int id ;
	int fuelStart ;
	int fuelNow ;
};

struct Plane {
	Info inf ;
	Plane *next ;
};

struct Row {
	int qt ;
	Plane *first, *last ;
};

void createRows() ;

Plane* createPlane(char c) ;

void insertPlane(Plane *p, Row *r) ;

void generatePlanes() ;

#endif

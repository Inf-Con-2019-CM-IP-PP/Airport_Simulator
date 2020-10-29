#include "airplanefunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Row at11, at12, at21, at22 ;
Row dec1, dec2, dec3 ;

int lastIDP = 0 ;
int lastIDI = -1 ;

void createRows() {
	Row vazia ;
	vazia.first = NULL ; vazia.last = NULL ; vazia.qt = 0 ;
	
	at11 = vazia ; at12 = vazia ; at21 = vazia ; at22 = vazia ;
	dec1 = vazia ; dec2 = vazia ; dec3 = vazia ;
}

Plane* createPlane(char c) {
	Plane *p ;
	p = (Plane *) malloc(sizeof(Plane)) ;
	
	if (c == 'a') {
		p->inf.id = lastIDP + 2 ;
		p->inf.fuelStart = p->inf.fuelNow = rand()%20 + 1 ;
	} else {
		p->inf.id = lastIDI + 2 ;
		p->inf.fuelStart = p->inf.fuelNow = 20 ;
	}
	
	return p ;
}

void insertPlane(Plane *p, Row *r) {
	if (r->first == NULL) {
		p->next = NULL ;
		r->first = r->last = p ;
	} else {
		p->next = r->last->next ;
		r->last->next = p ;
		r->last = p ;
	}
}

void generatePlanes() {
	Row *menA1, *menA2, *menA ;
	
	int qtA = rand()%4 ;
	Plane *vA[qtA] ;
	
	for (int i=0; i < qtA; i++) {
		vA[i] = createPlane('a') ;
		
		menA1 = at11.qt <= at12.qt ? &at11 : &at12 ;
		menA2 = at21.qt <= at22.qt ? &at21 : &at22 ;
		menA = menA1->qt <= menA2->qt ? menA1 : menA2 ;
		
		insertPlane(vA[i], menA) ;
	}
	
	Row *menD1, *menD ;
	
	int qtD = rand()%4 ;
	Plane *vD[qtD] ;
	
	for (int i=0; i < qtD; i++) {
		vD[i] = createPlane('d') ;
		
		menD1 = dec1.qt <= dec2.qt ? &dec1 : &dec2 ;
		menD = menD1->qt <= dec3.qt ? menD1 : &dec3 ;
		
		insertPlane(vD[i], menD) ;
	}
}

void decreaseFuel() {
	for (Plane *act=at11.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
	for (Plane *act=at12.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
	for (Plane *act=at21.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
	for (Plane *act=at22.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
	
	for (Plane *act=dec1.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
	for (Plane *act=dec2.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
	for (Plane *act=dec3.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
	}
}

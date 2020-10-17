#include "airplanefunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Row at11, at12, at21, at22 ;
Row dec ;

int lastIDP = 0 ;
int lastIDI = -1 ;

void createRows() {
	Row vazia ;
	vazia.first = NULL ; vazia.last = NULL ; vazia.qt = 0 ;
	
	at11 = vazia ; at12 = vazia ; at21 = vazia ; at22 = vazia ;
	dec = vazia ;
}

Plane* createPlane(char c) {
	Plane *p ;
	
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
		p->next = r->last->next ;
		r->first = r->last = p ;
	} else {
		p->next = r->last->next ;
		r->last->next = p ;
		r->last = p ;
	}
}

void generatePlanes() {
	Row *men1, *men2, *men ;
	
	int qtA = rand()%4 ;
	Plane *vA[qtA] ;
	
	for (int i=0; i < qtA; i++) {
		vA[i] = createPlane('a') ;
		
		if (at11.qt <= at12.qt) men1 = &at11 ;
		else men1 = &at12 ;
		if (at21.qt <= at22.qt) men2 = &at21 ;
		else &at22 ;
		if (men1->qt <= men2->qt) men = men1 ;
		else men = men2 ;
		
		insertPlane(vA[i], men) ;
	}
	
	int qtD = rand()%4 ;
	Plane *vD[qtD] ;
	
	for (int i=0; i < qtD; i++) {
		vD[i] = createPlane('d') ;
		
		insertPlane(vD[i], &dec) ;
	}
}





















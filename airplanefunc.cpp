#include "airplanefunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Row at11, at12, at21, at22 ; // Filas de aterrissagem
Row dec1, dec2, dec3 ; // Filas de decolagem

int lastIDP = 0 ; // Ultimo ID par usado
int lastIDI = -1 ; // Ultimo ID impar usado

int qtAt=0, tAt=0 ; // Quantidade de avioes aterrissados e soma total dos tempos
int qtDc=0, tDc=0 ; // Quantidade de avioes decolados e soma total dos tempos

int qtCrash=0 ; // Quantidade de avioes caidos

void createRows() {
	Row vazia ; // Cria um fila vazia
	vazia.first = NULL ; vazia.last = NULL ; vazia.qt = 0 ; // atribui os valores iniciais
	
	// Atribuir a fila inicializada nas outras filas
	at11 = vazia ; at12 = vazia ; at21 = vazia ; at22 = vazia ;
	dec1 = vazia ; dec2 = vazia ; dec3 = vazia ;
}

Plane* createPlane(char c) {
	srand((unsigned) time(NULL)) ;
	
	// Cria um ponteiro de aviao
	Plane *p ;
	p = (Plane *) malloc(sizeof(Plane)) ;
	
	// Verifica qual o tipo de aviao a ser gerado
	if (c == 'a') {
		// Aterrissagem
		p->inf.id = lastIDP + 2 ; // Atribui um avlor de inidice par novo
		p->inf.fuelStart = p->inf.fuelNow = rand()%20 + 1 ; // Gera um combustivel aleatorio
	} else {
		// Decolagem
		p->inf.id = lastIDI + 2 ; // Atribui um avlor de inidice impar novo
		p->inf.fuelStart = p->inf.fuelNow = 20 ; // Atribui o maximo de combustivel
	}
	
	return p ; // Retorna o ponteiro para o aviao criado
}

void insertPlane(Plane *p, Row *r) {
	if (r->first == NULL) { // Se a fila esta vazia realiza tal procedimento
		p->next = NULL ;
		r->first = r->last = p ;
	} else { // Se a fila nao esta vazia, realiza o seguinte
		p->next = r->last->next ;
		r->last->next = p ;
		r->last = p ;
	}
	
	r->qt++ ;
}

void generatePlanes() {
	srand((unsigned) time(NULL)) ;
	
	Row *menA1, *menA2, *menA ;	//variaveis auxiliares criadas para apontar para a fila com menor numero de avioes para aterrissar
	
	int qtA = rand()%4 ;	//gera uma quantidade aleatoria de avioes a serem aterrissados
	
	for (int i=0; i < qtA; i++) {	//gera um loop que cria e insere a quantidade de avioes que foram gerados nas menores filas
		menA1 = at11.qt <= at12.qt ? &at11 : &at12 ;
		menA2 = at21.qt <= at22.qt ? &at21 : &at22 ;
		menA = menA1->qt <= menA2->qt ? menA1 : menA2 ;
		
		insertPlane(createPlane('a'), menA) ;
	}
	
	Row *menD1, *menD ;	//variaveis auxiliares criadas para apontar para a fila com menor numero de avioes para decolar
	
	int qtD = rand()%4 ;	//gera uma quantidade aleatoria de avioes a serem decolados
	
	for (int i=0; i < qtD; i++) {	//gera um loop que cria e insere a quantidade de avioes que foram gerados nas menores filas
		menD1 = dec1.qt <= dec2.qt ? &dec1 : &dec2 ;
		menD = menD1->qt <= dec3.qt ? menD1 : &dec3 ;
		
		insertPlane(createPlane('d'), menD) ;
	}
}

void removePlane(Row *r, char c) {
	Plane *p=r->first ; // Recebe aviao a ser removido
	r->first = p->next ; // Passa o primeiro para o prox
	r->qt-- ; // Dominui a quantidade
	
	// Verifica se e aterrissagem e decolagem
	if (c == 'a') {
		qtAt++ ; // Aumenta a quantidade de avioes aterrissados
		tAt += (p->inf.fuelStart - p->inf.fuelNow) ; // Aumenta o tempo total das aterrissagem
	} else {
		qtDc++ ; // Aumenta a quantidade de avioes decolados
		tDc += (p->inf.fuelStart - p->inf.fuelNow) ; // Aumenta o tempo total das decolagens
	}
	
	free(p) ;
}

void landAndTakeOffPlanes() {
	// Chama as funcoes para aterrisar ou decolar aviao uma vez em cada pista
	
	// Pista 1
	if (at11.qt <= dec1.qt || at12.qt <= dec1.qt) { // Verifica o tipo de lista mais vazia
		if (at11.first == NULL && at12.first == NULL) { // Verifica se alguma pista e vazia
		} else if (at11.first == NULL) {
			removePlane(&at12, 'a') ;
		} else if (at12.first == NULL) {
			removePlane(&at11, 'a') ;
		} else {
			if (at11.first->inf.fuelNow <= at12.first->inf.fuelNow) removePlane(&at11, 'a') ;
			else removePlane(&at12, 'a') ;
		}
	} else {
		removePlane(&dec1, 'd') ;
	}
	
	// Pista 2
	if (at21.qt <= dec2.qt || at22.qt <= dec2.qt) {
		if (at21.first == NULL && at22.first == NULL) {
		} else if (at21.first == NULL) {
			removePlane(&at22, 'a') ;
		} else if (at22.first == NULL) {
			removePlane(&at21, 'a') ;
		} else {
			if (at21.first->inf.fuelNow <= at22.first->inf.fuelNow) removePlane(&at21, 'a') ;
			else removePlane(&at22, 'a') ;
		}
	} else {
		removePlane(&dec2, 'd') ;
	}
	
	// Pista 3
	if (dec3.first != NULL) removePlane(&dec3, 'd') ;
}

void planeCrash(Row *r, Plane *o, bool f) {
	// Verifica se e a primeira cas ou outras, true =  primeira casa
	if (f) {
		r->first = o->next ;
		
		free(o) ;
	} else {
		// Faz a remocao da fila
		Plane *p = o->next ;
		o->next = p->next ;
		
		free(p) ;
	}
	
	r->qt-- ; // Decrementa a quantidade de avioes
	qtCrash++ ; // Soma a quantidade de avioes caidos
}

void decreaseFuel() {
	// Passa em cada fila por todos avioes e decrementa seu combustivel
	// Quando verificar que o aviao seguinte ao atual esta para se decrementado a -1 remove da fila
	
	for (Plane *act=at11.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
		
		if (act == at11.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at11, act, true) ;
		} else {
			if (act->next != NULL) {
				if (act->next->inf.fuelNow <= 0) planeCrash(&at11, act, false) ;
			}
		}
		
		printf ("C: %d\t", act->inf.fuelNow) ;
		
		
	}
	printf ("\n") ;
	for (Plane *act=at12.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
		
		if (act == at12.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at12, act, true) ;
		} else {
			if (act->next != NULL) {
				if (act->next->inf.fuelNow <= 0) planeCrash(&at12, act, false) ;
			}
		}
	}
	for (Plane *act=at21.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
		
		if (act == at21.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at21, act, true) ;
		} else {
			if (act->next != NULL) {
				if (act->next->inf.fuelNow <= 0) planeCrash(&at21, act, false) ;
			}
		}
	}
	for (Plane *act=at22.first; act != NULL; act=act->next) {
		act->inf.fuelNow-- ;
		
		if (act == at22.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at22, act, true) ;
		} else {
			if (act->next != NULL) {
				if (act->next->inf.fuelNow <= 0) planeCrash(&at22, act, false) ;
			}
		}
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

void status() {
	printf ("\n%d\n", qtCrash) ;
}

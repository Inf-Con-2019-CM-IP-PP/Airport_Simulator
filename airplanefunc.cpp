#include "airplanefunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Row at11, at12, at21, at22 ; // Filas de aterrissagem
Row dec1, dec2, dec3 ; // Filas de decolagem

int lastIDP = 0 ; // Ultimo ID par usado
int lastIDI = -1 ; // Ultimo ID impar usado

void createRows() {
	Row vazia ; // Cria um fila vazia
	vazia.first = NULL ; vazia.last = NULL ; vazia.qt = 0 ; // atribui os valores iniciais
	
	// Atribuir a fila inicializada nas outras filas
	at11 = vazia ; at12 = vazia ; at21 = vazia ; at22 = vazia ;
	dec1 = vazia ; dec2 = vazia ; dec3 = vazia ;
}

Plane* createPlane(char c) {
	// Cria um ponteiro de avião
	Plane *p ;
	p = (Plane *) malloc(sizeof(Plane)) ;
	
	// Verifica qual o tipo de avião a ser gerado
	if (c == 'a') {
		// Aterrissagem
		p->inf.id = lastIDP + 2 ; // Atribui um avlor de inidice par novo
		p->inf.fuelStart = p->inf.fuelNow = rand()%20 + 1 ; // Gera um combustivel aleatorio
	} else {
		// Decolagem
		p->inf.id = lastIDI + 2 ; // Atribui um avlor de inidice impar novo
		p->inf.fuelStart = p->inf.fuelNow = 20 ; // Atribui o maximo de combustivel
	}
	
	return p ; // Retorna o ponteiro para o avião criado
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
}

void generatePlanes() {
	Row *menA1, *menA2, *menA ;	//variaveis auxiliares criadas para apontar para a fila com menor numero de avioes para aterrissar
	
	int qtA = rand()%4 ;	//gera uma quantidade aleatória de aviões a serem aterrissados
	Plane *vA[qtA] ;	//cria um vetor de ponteiros que apontam para os avioes a serem criados
	
	for (int i=0; i < qtA; i++) {	//gera um loop que cria e insere a quantidade de avioes que foram gerados nas menores filas
		vA[i] = createPlane('a') ;
		
		menA1 = at11.qt <= at12.qt ? &at11 : &at12 ;
		menA2 = at21.qt <= at22.qt ? &at21 : &at22 ;
		menA = menA1->qt <= menA2->qt ? menA1 : menA2 ;
		
		insertPlane(vA[i], menA) ;
	}
	
	Row *menD1, *menD ;	//variaveis auxiliares criadas para apontar para a fila com menor numero de avioes para decolar
	
	int qtD = rand()%4 ;	//gera uma quantidade aleatoria de avioes a serem decolados
	Plane *vD[qtD] ;	//cria um vetor de ponteiros que apontam para os avioes a serem criados
	
	for (int i=0; i < qtD; i++) {	//gera um loop que cria e insere a quantidade de avioes que foram gerados nas menores filas
		vD[i] = createPlane('d') ;
		
		menD1 = dec1.qt <= dec2.qt ? &dec1 : &dec2 ;
		menD = menD1->qt <= dec3.qt ? menD1 : &dec3 ;
		
		insertPlane(vD[i], menD) ;
	}
}

void decreaseFuel() {
	// Passa em cada fila por todos avioes e decrementa seu combustivel
	
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

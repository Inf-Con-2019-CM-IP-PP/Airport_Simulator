#include "airplanefunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Row at11, at12, at21, at22 ; // Filas de aterrissagem
Row dec1, dec2, dec3 ; // Filas de decolagem

int lastIDP = 2 ; // Ultimo ID par usado
int lastIDI = 1 ; // Ultimo ID impar usado

int qtAt=0, tAt=0 ; // Quantidade de avioes aterrissados e soma total dos tempos
int qtDec=0, tDec=0 ; // Quantidade de avioes decolados e soma total dos tempos

int qtCrash=0 ; // Quantidade de avioes caidos

int qtEme=0 ; // Quantidade de pousos de emergencia

void createRows() {
	Row vazia ; // Cria um fila vazia
	vazia.first = NULL ; vazia.last = NULL ; vazia.qt = 0 ; // atribui os valores iniciais
	
	// Atribuir a fila inicializada nas outras filas
	at11 = vazia ; at12 = vazia ; at21 = vazia ; at22 = vazia ;
	dec1 = vazia ; dec2 = vazia ; dec3 = vazia ;
}

Plane* createPlane(char c) {
	// Cria um ponteiro de aviao
	Plane *p ;
	p = (Plane *) malloc(sizeof(Plane)) ;
	
	// Verifica qual o tipo de aviao a ser gerado
	if (c == 'a') {
		// Aterrissagem
		p->inf.id = lastIDP ; // Atribui um avlor de inidice par novo
		lastIDP += 2 ; // Incrementa o ID
		p->inf.fuelStart = p->inf.fuelNow = rand()%20 + 1 ; // Gera um combustivel aleatorio
	} else {
		// Decolagem
		p->inf.id = lastIDI ; // Atribui um avlor de inidice impar novo
		lastIDI += 2 ; // Incrementa o last ID
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
		menD = menD1->qt < dec3.qt ? menD1 : &dec3 ;
		
		insertPlane(createPlane('d'), menD) ;
	}
}

void removePlane(Plane *o, Row *r, char c) {
	Plane *p ;
	
	if (o == NULL) { // Verifica se ha aviao antes
		p=r->first ; // Recebe aviao a ser removido
		r->first = p->next ; // Passa o primeiro para o prox
	} else {
		p=o->next ; // Recebe o valor a ser removido a partir do anterior
		o->next = p->next ; // Passa o next do anterior para o seguinte
	}
	
	if (p == r->last) r->last = o ; // Se a posicao a ser removida e a final, atualiza o ponteiro final da fila para o anterior
	
	if (c == 'a') {
		qtAt++ ; // Aumenta a quantidade de avioes aterrissados
		tAt += (p->inf.fuelStart - p->inf.fuelNow) ; // Aumenta o tempo total das aterrissagem
	} else {
		qtDec++ ; // Aumenta a quantidade de avioes decolados
		tDec += (p->inf.fuelStart - p->inf.fuelNow) ; // Aumenta o tempo total das decolagens
	}
	r->qt-- ; // Dominui a quantidade
	free(p) ;
}

int fallPlanes(Plane *aO[3], Row *aR[3]) {
	int qt=0 ;
	
	aO[0] = NULL ; aO[1] = NULL ; aO[2] = NULL ;
	Plane *ant11=NULL, *ant12=NULL, *ant21=NULL, *ant22=NULL ; // Guarda a posicao anterior
	Plane *act11=at11.first, *act12=at12.first, *act21=at21.first, *act22=at22.first ; // Guarda a posicao atual
	
	while (qt < 3) { // Procura os tres primeiros avioes em todas as filas prestes a cair
		if (act11 != NULL) {
			if (act11->inf.fuelNow == 0) {
				aR[qt] = &at11 ;
				aO[qt] = ant11 ;
				qt++ ;
			}
			ant11 = act11 ;
			act11 = act11->next ;
		}
		if (qt >= 3) break ;
		if (act12 != NULL) {
			if (act12->inf.fuelNow == 0) {
				aR[qt] = &at12 ;
				aO[qt] = ant12 ;
				qt++ ;
			}
			ant12 = act12 ;
			act12 = act12->next ;
		}
		if (qt >= 3) break ;
		if (act21 != NULL) {
			if (act21->inf.fuelNow == 0) {
				aR[qt] = &at21 ;
				aO[qt] = ant21 ;
				qt++ ;
			}
			ant21 = act21 ;
			act21 = act21->next ;
		}
		if (qt >= 3) break ;
		if (act22 != NULL) {
			if (act22->inf.fuelNow == 0) {
				aR[qt] = &at22 ;
				aO[qt] = ant22 ;
				qt++ ;
			}
			ant22 = act22 ;
			act22 = act22->next ;
		}
		
		if (act11 == NULL && act12 == NULL && act21 == NULL & act22 == NULL) break ;
	}
	
	qtEme += qt ; // Adiciona ao total de pousos de emergencia
	return qt ; // Retorna a quantidade e por referencia o ponteiro do anterior, ponteiro da fila
}

void landAndTakeOffPlanes() {
	// Chama as funcoes para aterrisar ou decolar aviao uma vez em cada pista
	printf ("aaaaaaaaa") ;
	Row *aR[3] ; Plane *aO[3] ;
	int qtF = fallPlanes(aO, aR) ; // Recebe os avioes prestes a cair e suas filas
	printf ("bbbbbbbbbbb") ;
	
	bool p1Free=true, p2Free=true, p3Free=true ; // Marca qual pista foi usada para emergencia e estao livres
	
	if (qtF == 1) { // Verifica a quantidade de avioes a cair e realiza cada caso de emergencia
		// Pista 3
		removePlane(aO[0], aR[0], 'a') ; // Realiza o pouso de emergencia
		p3Free = false ;
		
	} else if (qtF == 2) {
		// Pista 3
		removePlane(aO[1], aR[1], 'a') ; // Realiza o pouso de emergencia
		p3Free = false ;
		
		// Segundo pouso de emergencia
		if (at11.qt+at12.qt < at21.qt+at22.qt) p1Free = false ; // Escolhe a pista mais vazia
		else p2Free = false ;
		removePlane(aO[0], aR[0], 'a') ;
		
	} else if (qtF >= 3) {
		printf ("eeeeeeeeeeeeeeeeeeeee") ;
		// Pista 3
		removePlane(aO[2], aR[2], 'a') ; // Realiza o pouso de emergencia 1
		p3Free = false ; printf ("e1e1ee1e1e1ee1e1ee1e1ee1e1") ;
		// Pista 2
		removePlane(aO[1], aR[1], 'a') ; // Realiza o pouso de emergencia 2
		p2Free = false ; printf ("e2e2e2ee2e2e2ee2e2ee2e2e2") ;
		// Pista 1
		removePlane(aO[0], aR[0], 'a') ; // Realiza o pouso de emergencia 3
		p1Free = false ; printf ("e3e3e3ee3e3ee3e3ee3e3e3ee3e3e3e3") ;
	}
	printf ("yyyyyyyyyyy") ;
	// Pousa ou decola aviao nas pistas que estao livres
	// Pista 1
		if (at11.qt+at12.qt >= dec1.qt && p1Free) { // Verifica o tipo de lista mais vazia
			if (at11.first == NULL && at12.first == NULL) { // Verifica se alguma pista e vazia
			} else if (at11.first == NULL) {
				removePlane(NULL, &at12, 'a') ;
			} else if (at12.first == NULL) {
				removePlane(NULL, &at11, 'a') ;
			} else {
				if (at11.first->inf.fuelNow <= at12.first->inf.fuelNow) removePlane(NULL, &at11, 'a') ;
				else removePlane(NULL, &at12, 'a') ;
			}
		} else if (p1Free) {
			removePlane(NULL, &dec1, 'd') ;
		}
		
		// Pista 2
		if (at21.qt+at22.qt >= dec2.qt && p2Free) {
			if (at21.first == NULL && at22.first == NULL) {
			} else if (at21.first == NULL) {
				removePlane(NULL, &at22, 'a') ;
			} else if (at22.first == NULL) {
				removePlane(NULL, &at21, 'a') ;
			} else {
				if (at21.first->inf.fuelNow <= at22.first->inf.fuelNow) removePlane(NULL, &at21, 'a') ;
				else removePlane(NULL, &at22, 'a') ;
			}
		} else if (p2Free) {
			removePlane(NULL, &dec2, 'd') ;
		}
		printf ("zzzzzzzzzz") ;
		// Pista 3
		if (dec3.first != NULL && p3Free) removePlane(NULL, &dec3, 'd') ;
}

void planeCrash(Row *r, Plane *o, bool first) {
	// Verifica se e a primeira casa ou outras, true =  primeira casa
	if (first) {
		r->first = o->next ;
		
		if (o == r->last) r->last = NULL ; // Se a posicao a ser removida e a final, atualiza o ponteiro final da fila para o anterior
		
		free(o) ;
	} else {
		// Faz a remocao da fila
		Plane *p = o->next ;
		o->next = p->next ;
		
		if (p == r->last) r->last = o ; // Se a posicao a ser removida e a final, atualiza o ponteiro final da fila para o anterior
		
		free(p) ;
	}
	r->qt-- ; // Decrementa a quantidade de avioes
	qtCrash++ ; // Soma a quantidade de avioes caidos
}

void decreaseFuel() {
	// Passa em cada fila por todos avioes e decrementa seu combustivel
	// Quando verificar que o aviao seguinte ao atual esta para se decrementado a -1 remove da fila
	
	for (Plane *act=at11.first; act != NULL; act=act->next) {
		if (act == at11.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at11, act, true) ;
		}
		if (act->next != NULL) {
			if (act->next->inf.fuelNow <= 0) planeCrash(&at11, act, false) ;
		}
		
		act->inf.fuelNow-- ;
	}
	for (Plane *act=at12.first; act != NULL; act=act->next) {
		if (act == at12.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at12, act, true) ;
		}
		if (act->next != NULL) {
			if (act->next->inf.fuelNow <= 0) planeCrash(&at12, act, false) ;
		}
		
		act->inf.fuelNow-- ;
	}
	for (Plane *act=at21.first; act != NULL; act=act->next) {
		if (act == at21.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at21, act, true) ;
		}
		if (act->next != NULL) {
			if (act->next->inf.fuelNow <= 0) planeCrash(&at21, act, false) ;
		}
		
		act->inf.fuelNow-- ;
	}
	for (Plane *act=at22.first; act != NULL; act=act->next) {
		if (act == at22.first) {
			if (act->inf.fuelNow <= 0) planeCrash(&at22, act, true) ;
		}
		if (act->next != NULL) {
			if (act->next->inf.fuelNow <= 0) planeCrash(&at22, act, false) ;
		}
		
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

void showRow(Row *r) {
	printf ("\t") ;
	for (Plane *act=r->first; act != NULL; act=act->next) {
		//printf ("____________________\n") ;
		printf("\t| ID: %d  Fuel: %d |", act->inf.id, act->inf.fuelNow) ;
		//printf ("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45) ;
	}
}

void showAllRows() {
	printf ("Pista 1\n") ;
	printf ("\tAt11:\n") ;
	showRow(&at11) ;
	printf ("\n\tAt12:\n") ;
	showRow(&at12) ;
	printf ("\n\tDec1:\n") ;
	showRow(&dec1) ;
	printf ("\n\nPista 2\n") ;
	printf ("\tAt21:\n") ;
	showRow(&at21) ;
	printf ("\n\tAt22:\n") ;
	showRow(&at22) ;
	printf ("\n\tDec2:\n") ;
	showRow(&dec2) ;
	printf ("\n\nPista 3\n") ;
	printf ("\tDec3:\n") ;
	showRow(&dec3) ;
	printf ("\n") ;
}

void status() {
	printf ("\nQuedas: %d\n", qtCrash) ;
	printf ("Pousos de emergencia: %d\n", qtEme) ;
	float avgAt = (float)tAt/(float)qtAt ;
	printf ("Temp. Med. At.: %d/%d=%.2f\n", tAt, qtAt, avgAt) ;
	float avgDec = (float)tDec/(float)qtDec ;
	printf ("Temp. Med. Dec.: %d/%d=%.2f\n", tDec, qtDec, avgDec) ;
}

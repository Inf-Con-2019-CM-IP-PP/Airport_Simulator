#ifndef AIRPLANEFUNC_H
#define AIRPLANEFUNC_H

// Structs

struct Info { // Informacoes de cada aviao
	int id ; // ID
	int fuelStart ; // Combustivel inicial
	int fuelNow ; // Combustivel atual
};

struct Plane { // Aviao
	Info inf ; // Um conjunto de informações
	Plane *next ; // Ponteiro para o proximo avião
};

struct Row { // Fila
	int qt ; // Quantidade de avioes na fila
	Plane *first, *last ; // Ponteiro para o primeiro e o ultimo
};

// Assinatura funcoes

void createRows() ; // Inicializa as filas

Plane* createPlane(char c) ; // Gera um aviao do tipo determinado e retorna um ponteiro para ele

void insertPlane(Plane *p, Row *r) ; // Insere o avião na fila

void generatePlanes() ; // Gera os aviões e insere-os na menor fila

void removePlane(Row *r, char c) ; // Remove o avi�o de uma fila

void landAndTakeOffPlanes() ; // Pousa os avioes da pista

void planeCrash(Row *r,Plane *o, bool f) ; // Retira o aviao caido da fila

void decreaseFuel() ; // Decrementa o combustivel atual dos avioes nas filas e verifica as quedas

void status() ;

#endif

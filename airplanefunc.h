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

void insertPlane(Plane *p, Row *r) ; // Insere o aviao na fila

void generatePlanes() ; // Gera os aviões e insere-os na menor fila

void removePlane(Plane *o, Row *r, char c) ; // Remove o avi�o de uma fila

int fallPlanes(Plane *aO[3], Row *aR[3]) ; // Avalia os avioes a cair

void landAndTakeOffPlanes() ; // Pousa os avioes da pista

void planeCrash(Row *r, Plane *o, bool first) ; // Retira o aviao caido da fila

Plane* verifyIfPlanesAreGonnaFall(Plane *act, Row *r) ; // Verifica quais avioes estao a cair e retorna para onde a proxima iteracao deve ir

void decreaseFuel() ; // Decrementa o combustivel atual dos avioes nas filas e verifica as quedas

void showRow(Row *r) ; // Mostra em tela uma fila

void showAllRows() ; // Mostra em tela todas as filas

void status() ; // Printa em tela os status atuais observados

#endif

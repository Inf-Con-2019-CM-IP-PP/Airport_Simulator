#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define quantMax_Avioes 3 // Pode gerar de 0 a 3 avi�es

struct DadosAviao {
    int Cod_Aviao; // Indica se o avi�o vai decolar(1) ou pousar(2)
    int Combustivel; // Quantidade de combust�vel
    int Num_pista; // Qual pista que o avi�o usar�

};

struct NodoFila {
    DadosAviao info; // Cont�m os dados de cada avi�o
    NodoFila *proximo; // Aponta para o pr�ximo elemento da fila

};

struct Fila {
    NodoFila *primeiro; // Aponta para o primeiro elemento da fila
    NodoFila *ultimo; // Aponta para o �ltimo elemento da fila

};

void criaFila (Fila *F); // Cria a fila
void geraAvioes_Decolar (Fila *F, int numPista); // Gera avi�es para decolar e atribui dados a eles
void geraAvioes_Pousar (Fila *F, int numPista );  // Gera avi�es para pousar e atribui dados a eles
void listagemAvioes (Fila *F); //Exibe os avi�es em uma determinada fila

int main (int argc, char** argv) {
    // Declara��o de vari�veis
    Fila FilaAvioes_1, FilaAvioes_2,FilaAvioes_3;
    int pista_Decola, pista_Pousa, quant_Decola, quant_Pousa;
    int i; 

    // Cria as tr�s filas
    criaFila(&FilaAvioes_1);
    criaFila(&FilaAvioes_2);
    criaFila(&FilaAvioes_3);

	/* Testa fila de decolagem */
    // Gera e exibe quantos avi�es iram para a fila de decolagem naquele turno
    srand ((unsigned) time (NULL));
    quant_Decola = (rand() % quantMax_Avioes);
    printf("Quantidade de avioes para decolar: %d \n", quant_Decola);
	
	// Insere a quantidade gerada de avi�es na fila
    for(i = 0; i < quant_Decola; i++)
    {
    	// Gera, aleat�riamente, a pista de decolagem do avi�o
        srand ((unsigned) time (NULL));
        pista_Decola = rand() % 3 + 1;

		// Insere o avi�o na sua respectiva pista
        switch(pista_Decola)
        {
        case 1:
            geraAvioes_Decolar(&FilaAvioes_1, pista_Decola);
            break;

        case 2:
            geraAvioes_Decolar(&FilaAvioes_2, pista_Decola);
            break;

        case 3:
            geraAvioes_Decolar(&FilaAvioes_3, pista_Decola);

            break;
        }
    }
    
    /*  Testar avi�es de pouso */
    
    // Gera e exibe quantos avi�es iram para a fila de pouso naquele turno 
    srand ((unsigned) time (NULL));;
    quant_Pousa = (rand() % quantMax_Avioes);
    printf("Quantidade de avioes para pousar: %d \n", quant_Pousa);

	// Insere a quantidade de avi�es gerados na fila
    for(i = 0; i < quant_Pousa; i++)
    {
    	
    	// Gera, automaticamente, a fila de pouso do avi�o
        srand ((unsigned) time (NULL));
        pista_Pousa = rand() % 2 + 1;

		// Insere o avi�o na sua respectiva fila
        switch(pista_Pousa)
        {
        case 1:
            geraAvioes_Pousar(&FilaAvioes_1, pista_Pousa);
            break;

        case 2:
            geraAvioes_Pousar(&FilaAvioes_2, pista_Pousa);
            break;

        }
    }


	// Listagem geral de avi�es; fila por fila
	
    printf("Listagem fila 1: \n");
    listagemAvioes(&FilaAvioes_1);

    printf("\n\n");

    printf("Listagem fila 2: \n");
    listagemAvioes(&FilaAvioes_2);

    printf("\n\n");

    printf("Listagem fila 3: \n");
    listagemAvioes(&FilaAvioes_3);

    printf("\n\n");

    return 0;

}

/* Implementa��o das fun��es*/

// Crria a fila
void criaFila (Fila *F)
{
    F->primeiro = NULL;
    F->ultimo = NULL;

}

void geraAvioes_Decolar (Fila *F, int numPista) {
    // Cria e aloca espa�o para o elemento a ser inserido
    NodoFila *novo;
    novo = (NodoFila *) malloc (sizeof (NodoFila));

    // Caso a mem�ria tenha sido alocada corretamente
    if(novo != NULL) {

        novo-> info.Cod_Aviao = 2; // Indica que o avi�o vai decolar
        // O avi�o iniciar� e decolar� com o combust�vel cheio
        novo->info.Combustivel = 20;
        novo->info.Num_pista = numPista; // Insere o n�mero da pista de decolagem


        novo->proximo = NULL; // O pr�ximo elemento da fila 'novo' aponta para nada

        // Se a fila estiver vazia o primeiro elemento recebe 'novo'
        if(F->primeiro == NULL	) {
            F->primeiro = novo;

        }
        else // Se n�o, o elemento ap�s o �ltimo apontar� para o novo elemento
        {
            F->ultimo->proximo = novo;
        }

        F->ultimo = novo; // O �ltimo elemento da lista aponta para novo

    }

}

void geraAvioes_Pousar (Fila *F, int numPista ) {
    NodoFila *novo	;

	// Cria e aloca espa�o para o elemento a ser inserido
    novo = (NodoFila *) malloc (sizeof (NodoFila));
	
	// Caso a mem�ria tenha sido alocada corretamente
    if(novo != NULL) {
    	
        novo-> info.Cod_Aviao = 1; // Indica que o avi�o vai pousar
		// Gera uma quantidade aleat�ria de combust�vel para o avi�o   	
		srand ((unsigned) time (NULL));
        novo->info.Combustivel = rand () % 20;
        novo->info.Num_pista = numPista; // Insere o n�mero da pista de pouso

        novo->proximo = NULL; // O pr�ximo elemento da fila 'novo' aponta para nada

		// Se a fila estiver vazia o primeiro elemento recebe 'novo'
        if(F->primeiro == NULL	) {
            F->primeiro = novo;

        } else // Se n�o, o elemento ap�s o �ltimo apontar� para o novo elemento
        {
            F->ultimo->proximo = novo; 
        }

        F->ultimo = novo; // O �ltimo elemento da lista aponta para novo

    }

}

// Lista os avi�es da fila e seus dados
void listagemAvioes (Fila *F)
{
    NodoFila *aux;

    aux = F->primeiro; // A vari�vel aux recebe o primeiro elemento da fila

	// Enquanto a fila n�o chegar ao n�mero ap�s o �ltimo (vulgo NULL)
    while (aux != NULL)
    {
    	// Testa se � um avi�o de pouso ou decolagem e exibe seus dados
        if (aux->info.Cod_Aviao == 1) 
        {
            printf ("E um aviao de pouso. Informacoes: \n");
            printf ("Codigo: %d \n", aux->info.Cod_Aviao);
            printf ("Combustivel disponivel: %d \n", aux->info.Combustivel);
            printf ("Pista de pouso: %d\n", aux->info.Num_pista);
            printf("\n\n");
        } else if (aux->info.Cod_Aviao == 2)

        {
            printf ("E um aviao de decolagem. Informacoes: \n");
            printf ("Codigo: %d \n", aux->info.Cod_Aviao);
            printf ("Capacidade de combustivel: %d \n", aux->info.Combustivel);
            printf ("Pista de decolagem: %d\n", aux->info.Num_pista);
            printf("\n\n");
        }

		// Passa para o pr�ximo elemento da fila
        aux = aux->proximo;
    }
}

#include "airplanefunc.h"
#include <stdio.h>

int main() {
	createRows() ; // Inicializa as filas
	
	for (int repet=0; repet < 10000; repet++) { // Faz a repeticao
		generatePlanes() ; // Faz a geracao dos avioes
		printf ("-------------Repet %d-------------\n", repet) ; // Indica a repeticao
		showAllRows() ; // Mostra os estados atuais das filas
		printf ("\n") ;
		
		landAndTakeOffPlanes() ; // Realiza as aterrissagens/decolagens
		status() ; // Mostra os status
		
		decreaseFuel() ; // Faz os procedimentos de fim de cada repeticao
	}
	
	status() ; // Mostra os status finais
	
	return 0 ;
}

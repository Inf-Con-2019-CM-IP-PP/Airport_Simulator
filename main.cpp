#include "airplanefunc.h"
#include <stdio.h>

int main() {
	createRows() ;
	
	for (int repet=0; repet < 100; repet++) {
		generatePlanes() ;
		printf ("-------------Repet %d-------------\n", repet) ;
		showAllRows() ;
		printf ("\n") ;
		
		landAndTakeOffPlanes() ;
		
		decreaseFuel() ;
	}
	
	status() ;
	
	return 0 ;
}

#include "airplanefunc.h"
#include <stdio.h>

int main() {
	createRows() ;
	
	for (int repet=0; repet < 160; repet++) {
		generatePlanes() ;
		printf ("-------------Repet %d-------------\n", repet) ;
		showAllRows() ;
		printf ("\n") ;
		
		landAndTakeOffPlanes() ;
		status() ;
		
		decreaseFuel() ;
	}
	
	status() ;
	
	return 0 ;
}

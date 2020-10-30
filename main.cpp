#include "airplanefunc.h"

int main() {
	createRows() ;
	
	for (int repet=0; repet < 10000; repet++) {
		generatePlanes() ;
		
		landAndTakeOffPlanes() ;
		
		decreaseFuel() ;
	}
	
	status() ;
	
	return 0 ;
}

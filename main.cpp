#include "airplanefunc.h"

int main() {
	createRows() ;
	
	for (int repet=0; repet < 10; repet++) {
		generatePlanes() ;
		
		decreaseFuel() ;
	}
	
	return 0 ;
}

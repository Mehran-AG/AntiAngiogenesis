#include "tc_finder.h"

void tc_finder ( vessel& v, unsigned int& i, unsigned int& j) {

	// printf("\n  TC_FINDER");

	extern unsigned int nx, ny;

	unsigned int counter_i, counter_j;

	for ( counter_i = 0; counter_i < nx; counter_i++ )
		for ( counter_j = 0; counter_j < ny; counter_j++ ) {

			if ( v.old_TEC[counter_i][counter_j] == 1 ) {

				i = counter_i;

				j = counter_j;

			}; // end of if

		}; // end of for

}; // end of function
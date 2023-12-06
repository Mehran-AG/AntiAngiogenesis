#include "lubkcb.h"


void lubksb ( long double** a, int n, int* indx, long double* b ) {

	unsigned int ii, ll;

	double sum;

	ii = 0;

	for ( unsigned int i = 0; i != n; ++i ) { // 12
		
		ll = indx[i];

		sum = b[ll];

		b[ll] = b[i];

		if ( ii != 0 ) {

			for ( unsigned int j = ii; j < i; ++j )
				sum -= a[i][j]*b[j];

		}

		else if ( sum != 0.0 ) {

			ii = i;

		};

		b[i] = sum;

	}; // 12

	for ( unsigned int i = n-1; i > 0; --i ) { // 14

		sum = b[i];

		for ( unsigned int j = i+1; j < n; ++j )
			sum -= a[i][j]*b[j];

		b[i] = sum / a[i][i];

	}; // 14

};
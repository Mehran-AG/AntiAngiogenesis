#include "ludcmp.h"

#include <cmath>

#include <stdexcept>

#include <iostream>

int ludcmp ( long double** a, int n, int* indx) {

	double d = 1.0;

	int imax;

	const int nmax = 10000;

	const double tiny = 1e-20;

	double aamax, dum, sum;

	double vv[nmax];

	for ( unsigned int i = 0; i != n; ++i ) { // 12

		aamax = 0.0;

		for ( unsigned int j = 0; j != n; ++j ) { // 11

			if ( abs(a[i][j]) > aamax ) aamax = abs(a[i][j]);

		};

		try { // t

			if ( aamax == 0.0 ) throw std::runtime_error ( "\nSingular matrix" );

		}

		catch ( std::runtime_error err ) {

			std::cout << err.what() << std::endl;

			system("pause");

			exit(1);

		}; // end of t

		vv[i] = 1.0 / aamax;

	}; // 12

	for ( unsigned int j = 0; j != n; ++j ) { // 19

		for ( unsigned int i = 0; i != j; ++i ) { // 14

			sum = a[i][j];

			for ( unsigned int k = 0; k != i; ++k )
				sum -= a[i][k] * a[k][j];

			a[i][j] = sum;

		}; // 14

		aamax = 0.0;

		for ( unsigned int i = j; i != n; ++i ) { // 16

			sum = a[i][j];

			for ( unsigned int k = 0; k != j; ++k )
				sum -= a[i][k]*a[k][j];

			a[i][j] = sum;

			dum = vv[i] * abs(sum);

			if ( dum >= aamax ) {

				imax = i;

				aamax = dum;

			};

		}; // 16

		if ( j != imax ) {

			for ( unsigned int k = 0; k != n; ++k ) { // 17

				dum = a[imax][k];
				a[imax][k] = a[j][k];
				a[j][k] = dum;

			}; // 17

			d = -d;

			vv[imax] = vv[j];

		};

		indx[j] = imax;

		if ( a[j][j] == 0.0 )
			a[j][j] = tiny;

		if ( j != (n-1) ) {

			dum = 1.0 / a[j][j];

			for ( unsigned int i = j+1; i != n; ++i )
				a[i][j] *= dum;

		};

	}; // 19

	return 0;

}; // end of function
#include "InitialConcentrations.h"

#include "dimension.h"

#include "Endostatin.h"

#include <cmath>

#include <stdio.h>

#pragma warning( disable: 4101 )

void InitialConcentrations() {

	printf("\nINTITAL CONCENTRATIONS STARTED");

	extern double c[a_dim][a_dim];

	extern double f[a_dim][a_dim];

	extern double m[a_dim][a_dim];

	extern double e[a_dim][a_dim];

	extern int nx, ny, x_d;

	double k = 0.75;

	double eps_1 = 0.45;

	double eps_2 = 0.45;

	double eps_3 = 0.0025;

	double x, y, r;

	double nu = 1.1;

	extern double h;

	extern double L;

	extern int steps;

	//for ( int i = 0; i < nx; i++)
	//	for ( int j = 0; j < ny; j++) {

	//		c[i][j] = exp ( - 1 * ( pow (  ( L - ( i * h ) ), 2 ) ) / eps_1 );
	//		//f[i][j] = k * exp ( -1 * ( pow ( (i * h), 2 ) / eps_2 ) );
	//		f[i][j] = 0.5;

	//		//m[i][j] = exp ( -1 * pow( ( i * h ), 2 ) / eps_3 );

	//		//if ( m[i][j] < 1E-3 )
	//			//m[i][j] = 0;

	//	};

	for ( int i = 0; i < nx; ++i )
		for ( int j = 0; j < ny; ++j ) {

			x = i * h;

			y = j * h;

			r = sqrt( pow( (x-1), 2 ) + pow( (y-0.5), 2 ) );

			if ( ( r <= 0.1 ) && ( r > 0 ) )
				c[i][j] = 1;
			else
				c[i][j] = ( pow( (nu-r), 2 ) / (nu-0.1) );

			/*if ( ( r <= 0.1 ) && ( r > 0 ) )
				e[i][j] = 4 * 1;

			else
				e[i][j] = 4 * ( pow( (nu-r), 2 ) / (nu-0.1) );*/

			f[i][j] = 0.5;

		};



	printf("\nINTITAL CONCENTRATIONS ENDED");

};
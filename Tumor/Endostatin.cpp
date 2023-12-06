#include "Endostatin.h"

#include "dimension.h"

#include <cmath>


void Endostatin() {

	extern double e[a_dim][a_dim];

	extern int x_d, y_d, nx, ny;

	double D_e = 66.1; //(micrometer^2/s)

	double alpha_e = 1 / 360; //(M/sec)

	double delta_e = 5.54E-2; //(1/s)

	double dt = 0.01; // (sec)

	double h_e = 20; // (microns)

	for ( int i = 0; i < nx; ++i )
		for ( int j = 0; j < ny; ++j ) {

			e[i][j] = 0;

		};

	for ( int i = 0; i < nx; ++i )
		for ( int j = 0; j < ny; ++j ) {

			x = i * h;

			y = j * h;

			r = sqrt( pow( (x-1), 2 ) + pow( (y-0.5), 2 ) );

			if ( ( r <= 0.1 ) && ( r > 0 ) )
				c[i][j] = 1;
			else
				c[i][j] = ( pow( (nu-r), 2 ) / (nu-0.1) );

		};

	for ( int i = 1; i < x_d; ++i )
		for ( int j = 1; j < y_d; ++j ) {

			if ( cells[i][j] != 0 ) {

				if ( ( cell[cells[i][j]].GetStatus() == 2 ) || ( cell[cells[i][j]].GetStatus() == 3 ) ) { 

					e[i][j] = ( 1 - delta_e - ( 4 * D_e * dt / pow( h_e, 2 ) ) ) * e[i][j] + ( D_e * dt / pow( h_e, 2 ) ) * ( e[i+1][j] + e[i-1][j] + e[i][j+1] + e[i][j-1] ) + alpha_e;

				}

				else {

					e[i][j] = ( 1 - delta_e - ( 4 * D_e * dt / pow( h_e, 2 ) ) ) * e[i][j] + ( D_e * dt / pow( h_e, 2 ) ) * ( e[i+1][j] + e[i-1][j] + e[i][j+1] + e[i][j-1] );

				};

			};

		};

		

};
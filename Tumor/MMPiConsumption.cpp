#include "MMPiConsumption.h"

#include "dimension.h"

#include <vector>

#include "cVessel.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MMPiConsumption() {

	// DECLARATION OF VARIABLES ---------------------------------------------------------------------------------------------------------------------------------------------------------

	double dt = 0.00001; // 0.0001

	extern int nx, ny, x_d, y_d;

	extern double f[a_dim][a_dim];

	extern double m[a_dim][a_dim];

	extern double h;

	double nu = 1.3;

	double eps = 10.4E-3;

	double alpha = 130;

	extern std::vector<cVessel> vessels;

// INITIATION OF THE PROCEDURE ------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < nx; ++i ) {
		
		m[0][i] = m[1][i];
		m[200][i] = m[199][i];
		m[i][0] = m[i][1];
		m[i][200] = m[i][199];

	};

	for ( std::vector<cVessel>::size_type v = 0; v < vessels.size(); ++v ) {

		for ( int i = 1; i < x_d; ++i )
			for ( int j = 1; j < y_d; ++j ) {

				unsigned tec = 0;

				if ( ( vessels[v].Get_X_CoordianteOfTEC() == i ) && ( vessels[v].Get_Y_CoordianteOfTEC() == j ) )
					m[i][j] = m[i][j] * ( 1.0 - ( dt * ( nu + 4 * eps / pow( h, 2 ) ) ) ) + ( alpha * dt ) + ( dt * eps / pow( h, 2 ) ) * ( m[i+1][j] + m[i-1][j] + m[i][j+1] + m[i][j-1] );
				else
					m[i][j] = m[i][j] * ( 1.0 - ( dt * ( nu + 4 * eps / pow( h, 2 ) ) ) ) + ( dt * eps / pow( h, 2 ) ) * ( m[i+1][j] + m[i-1][j] + m[i][j+1] + m[i][j-1] );

			};

	};

};
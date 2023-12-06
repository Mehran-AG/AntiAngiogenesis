#include "FibronectinConsumption.h"

#include "dimension.h"

#include "cVessel.h"

#include <vector>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FibronectinConsumption() {

// DECLARATION OF VARIABLES ---------------------------------------------------------------------------------------------------------------------------------------------------------

	double dt = 0.001;

	extern int nx, ny;

	extern double f[a_dim][a_dim];

	extern double m[a_dim][a_dim];

	double a_gamma = 2.61E-4; // fibronectin consumption constant

	double beta = 0.; // fibronectin production constant // 0.01

	extern std::vector<cVessel> vessels;

// INITIATION OF THE PROCEDURE ------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( std::vector<cVessel>::size_type s = 0; s < vessels.size(); ++s ) {

		for ( int i = 0; i < nx; ++i )
			for ( int j = 0; j < ny; ++j ) {

				if ( ( vessels[s].Get_X_CoordianteOfTEC() == i ) && ( vessels[s].Get_Y_CoordianteOfTEC() == j ) )
					//f[i][j] = f[i][j] * ( 1.0 - ( dt * gamma * m[i][j] ) ) + ( dt * beta );
					f[i][j] = f[i][j] * ( 1.0 - ( dt * a_gamma ) + ( dt * beta ) ) ;

			};

	};


};
// ==================================================================================================================================================================================
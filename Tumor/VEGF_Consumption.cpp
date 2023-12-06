#include "VEGF_Consumption.h"

#include "dimension.h"

#include "cVessel.h"

#include <vector>

#include <iostream>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void VEGF_Consumption() {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	double dt = 0.03;

	extern int nx, ny;

	extern double c[a_dim][a_dim];

	double etha = 0.1; // VEGF consumption rate constant

	extern std::vector<cVessel> vessels;

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( std::vector<cVessel>::size_type s = 0; s < vessels.size(); ++s ) {

		for ( int i = 0; i < nx; ++i )
			for ( int j = 0; j < ny; ++j ) {

				if ( ( vessels[s].Get_X_CoordianteOfTEC() == i ) && ( vessels[s].Get_Y_CoordianteOfTEC() == j ) )
					c[i][j] = c[i][j] * ( 1.0 - ( dt * etha ) );

			};

	};

};
// ==================================================================================================================================================================================
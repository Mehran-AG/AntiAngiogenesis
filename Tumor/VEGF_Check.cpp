#include "VEGF_Check.h"

#include "dimension.h"

#include <cstdlib>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool VEGF_Check( int i, int j ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	bool VEGF_flag = false;

	double VEGF_prob = 0.;

	double r_num_VEGF_check = 0.;

	extern double c[a_dim][a_dim];

	extern double e[a_dim][a_dim];

	double cf = 0.2;

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	if ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.1 ) {

		VEGF_prob = 0;

	}

	else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) > 0.1 ) && ( ( c[i][j]- ( cf * e[i][j] ) ) <= 0.2 ) ) {

		VEGF_prob = 0.2;


	}

	else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) > 0.2 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) <= 0.3 ) ) {

		VEGF_prob = 0.4;

	}

	else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) > 0.3 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) <= 0.4 ) ) {

		VEGF_prob = 0.6;

	}

	else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) > 0.4 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) <= 0.9 ) ) {

		VEGF_prob = 0.8;

	}

	else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) > 0.9 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) <= 1 ) ) {

		VEGF_prob = 1;

	};

	r_num_VEGF_check = (double) rand() / RAND_MAX;

	if ( r_num_VEGF_check <= VEGF_prob ) {

		VEGF_flag = true;

	}

	else {

		VEGF_flag = false;

	};

	return VEGF_flag;

}; // end of function
// ==================================================================================================================================================================================
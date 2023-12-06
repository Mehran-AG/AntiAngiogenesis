#include "MovementPreventer.h"

#include "dimension.h"

#include "RangeCalculator.h"

#include <stdio.h>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MovementPreventer( int i, int j, unsigned char dir ) {
	
	extern double p_0[a_dim][a_dim], p_1[a_dim][a_dim], p_2[a_dim][a_dim], p_3[a_dim][a_dim], p_4[a_dim][a_dim];

	switch ( dir ) {

	case 'r' :

		p_1[i][j] = 0;

		RangeCalculator( i, j );

		break;

	case 'l' :

		p_2[i][j] = 0;

		RangeCalculator( i, j );

		break;

	case 'u' :

		p_3[i][j] = 0;

		RangeCalculator( i, j );

		break;

	case 'd' :

		p_4[i][j] = 0;

		RangeCalculator( i, j );

		break;

	};

};
// ==================================================================================================================================================================================
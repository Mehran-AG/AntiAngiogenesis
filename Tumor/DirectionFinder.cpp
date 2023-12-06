#include "DirectionFinder.h"

#include "dimension.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function finds the previous direction of the vessel -------------------------------------------------------------------------------------------------------------------------

char DirectionFinder ( cVessel& v, int i, int j ) {

	char direction;

	switch ( v.GetPrePathStorer( i, j ) ) {

	case 'r' :

		direction = 'r';
		break;

	case 'l' :

		direction = 'l';
		break;

	case 'u' :

		direction = 'u';
		break;

	case 'd' :

		direction = 'd';
		break;

	default:

		printf( "\nPREVIOUS PATH OF VESSEL DOES NOT MATCH ANY DIRECTION\n");

		system("pause");

	};

	return direction;


}; // end of function
// ==================================================================================================================================================================================
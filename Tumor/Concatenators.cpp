#include "Concatenators.h"

#include "dimension.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION CONCATENATES TWO INLET VESSELS TO A NODE----------------------------------------------------------------------------------------------------------------------------
// THE VESSEL TO BE REMAINED IS PASSED AS MAIN VESSEL, THE REMOVED ONE IS PASSED AS SECONDARY AND THE POSITION OF STARTING THE CONCATENATION IS PASSED AS I AND J AND AN INDICATOR IS
// -> AS THE INDICATOR OF BEING FIRST OR SECOND STEP IN CONCATENATION ---------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InletInletConcatenator( cVessel& main, cVessel& secondary, int i, int j, bool indicator ) {
	
	unsigned char path = secondary.pre_path_storer[i][j];

	switch ( path ) {

	case '\0' :

		break;

	case 's' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		break;

	case 'r' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		++i;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'l' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		--i;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'u' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		++j;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'd' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		--j;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	default:

		printf( "\nNO MATCHES TO THE GIVEN DIRECTION\n" );

		system("pause");

	};

};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION CONCATENATES ONE INLET VESSEL AND ONE OUTLET VESSEL TO A NODE-------------------------------------------------------------------------------------------------------
// THE VESSEL TO BE REMAINED IS PASSED AS MAIN VESSEL, THE REMOVED ONE IS PASSED AS SECONDARY AND THE POSITION OF STARTING THE CONCATENATION IS PASSED AS I AND J AND AN INDICATOR IS
// -> AS THE INDICATOR OF BEING FIRST OR SECOND STEP IN CONCATENATION ---------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InletOutletConcatenator( cVessel& main, cVessel& secondary, int i, int j, bool indicator ) {

	unsigned char path = secondary.path_storer[i][j];

	switch ( path ) {

	case '\0' :
		
		main.pre_path_storer[i][j] = secondary.pre_path_storer[i][j];

		main.path[i][j] = 1;

		break;

	case 's' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.pre_path_storer[i][j];

		};

		main.path[i][j] = 1;

		break;

	case 'r' :
		
		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.pre_path_storer[i][j];

		};

		main.path[i][j] = 1;

		++i;

		InletOutletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'l' :
		
		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.pre_path_storer[i][j];

		};

		main.path[i][j] = 1;

		--i;

		InletOutletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'u' :
		
		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.pre_path_storer[i][j];

		};

		main.path[i][j] = 1;

		++j;

		InletOutletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'd' :
		
		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.pre_path_storer[i][j];

		};

		main.path[i][j] = 1;

		--j;

		InletOutletConcatenator( main, secondary, i, j, indicator );

		break;

	default:

		printf( "\nNO MATCHES TO THE GIVEN DIRECTION\n" );

		system("pause");

	};


};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION CONCATENATES TWO OUTLET VESSELS TO A NODE----------------------------------------------------------------------------------------------------------------------------
// THE VESSEL TO BE REMAINED IS PASSED AS MAIN VESSEL, THE REMOVED ONE IS PASSED AS SECONDARY AND THE POSITION OF STARTING THE CONCATENATION IS PASSED AS I AND J AND AN INDICATOR IS
// -> AS THE INDICATOR OF BEING FIRST OR SECOND STEP IN CONCATENATION ---------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void OutletOutletConcatenator( cVessel& main, cVessel& secondary, int i, int j, bool indicator ) {

	unsigned char path = secondary.path_storer[i][j];

	switch ( path ) {

	case '\0' :

		break;

	case 's' :

		if ( indicator == true ) {

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		break;

	case 'r' :

		if ( indicator == true ) {

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		++i;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'l' :

		if ( indicator == true ) {

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		--i;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'u' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		++j;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	case 'd' :

		if ( indicator == true ) {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			indicator = false;

		}

		else {

			main.path_storer[i][j] = secondary.pre_path_storer[i][j];

			main.pre_path_storer[i][j] = secondary.path_storer[i][j];

		};

		main.path[i][j] = 1;

		--j;

		InletInletConcatenator( main, secondary, i, j, indicator );

		break;

	default:

		printf( "\nNO MATCHES TO THE GIVEN DIRECTION\n" );

		system("pause");

	};

};
// ==================================================================================================================================================================================
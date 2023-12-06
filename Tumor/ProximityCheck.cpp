#include "ProximityCheck.h"

#include "dimension.h"


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ProximityCheck( cVessel& v, int i, int j, bool& proximity_flag ) {

	extern int nx;

	extern int neighbor_checker;

	if ( ( i < ( nx - neighbor_checker ) ) && ( i > neighbor_checker ) ) { // if1

		int i_s = i - neighbor_checker;
		int i_e = i + neighbor_checker;

		int j_s = j - neighbor_checker;
		int j_e = j + neighbor_checker;

		for ( int ii = i_s; ii <= i_e; ii++ )
			for ( int jj = j_s; jj <= j_e; jj++ ) { // for1

				if ( v.GetPath( ii, jj ) == 1 )
					proximity_flag = true;

			}; // end of for1


	} // if1

	else {

		proximity_flag = false;

	}; // end of if1


}; // end of function
// ==================================================================================================================================================================================
#include "MigrationOfVessels.h"

#include "dimension.h"

#include "cVessel.h"

#include <vector>

#include "MigrationOfImmatureVessel.h"

#include "MigrationOfMatureVessel.h"


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MigrationOfVessels() {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	int stopper = 8;

	extern std::vector<cVessel> vessels;

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( size_t migrating_vessel_num = 0; migrating_vessel_num < vessels.size(); ++migrating_vessel_num ) {

		if ( vessels[migrating_vessel_num].GetOutletStatus() == 1 ) {
			
			if ( vessels[migrating_vessel_num].GetUnitLength() < stopper ) {

				MigrationOfImmatureVessel( migrating_vessel_num );

			}

			else {

				MigrationOfMatureVessel( migrating_vessel_num );

			};

		};

	};

};
// ==================================================================================================================================================================================
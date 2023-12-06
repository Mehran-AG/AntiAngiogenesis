#include "ChangeProhibitedVessels.h"

#include "dimension.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION SEARCHES THE VECTOR TO CHANGE ANY VESSEL WHOSE MOTHER VESSEL IS SECONDARY TO MAIN ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ChangeProhibitedVessels( std::vector<cVessel>& vec, cVessel& main, cVessel& secondary ) {

	for( unsigned i = 0; i < vec.size(); ++i ) {

		for ( size_t j = 0; j < vec[i].prohibiteds.size(); ++j ) {

			if ( vec[i].prohibiteds[j] == secondary.GetIDNumber() ) {

				vec[i].prohibiteds.erase( vec[i].prohibiteds.begin() + j );

				vec[i].AddToProhibiteds( main.GetIDNumber() );

				break;

			};

		};

	};

};
// ==================================================================================================================================================================================

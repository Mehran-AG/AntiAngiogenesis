#include "AddToProhibitedVessels.h"

#include "dimension.h"

void AddToProhibitedVessels( std::vector<cVessel>& vec, cVessel& main, cVessel& secondary ) {

	for( unsigned i = 0; i < vec.size(); ++i ) {

		for ( size_t j = 0; j < vec[i].prohibiteds.size(); ++j ) {

			if ( vec[i].prohibiteds[j] == secondary.GetIDNumber() ) {

				vec[i].AddToProhibiteds( main.GetIDNumber() );

				break;

			};

		};

	};

};
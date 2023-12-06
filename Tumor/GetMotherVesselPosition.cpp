#include "GetMotherVesselPosition.h"

#include "dimension.h"

#include <iostream>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int GetMotherVesselPosition( std::vector<cVessel>& vec, int v, int i, int j ) {

	int mother = vec[v].GetMother();

	int mother_position;

	try {

		mother_position = PositionFinder( vec, mother );

	}

	catch ( double ) {

		std::cerr << "\nNO MATCHES IN MOTHER VESSEL\n";

		system("pause");

	};


	return vec[mother_position].GetPath( i, j );

};
// ==================================================================================================================================================================================
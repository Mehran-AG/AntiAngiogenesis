#include "VesselRemover.h"

#include "dimension.h"

#include "PositionFinder.h"

#include "cNode.h"

#include "ConcatenateVessels.h"


// Declaration of the function -----------------------------------------------------------------------------------------------------------------------------------------------------
void RemoveFromMotherVessels( std::vector<cVessel>&, cVessel& );
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void VesselRemover( std::vector<cVessel>& vec, cVessel& v ) {

	extern std::vector<cNode> nodes;

	if ( v.GetOutletStatus() == 1 ) {

		int node_number;
		
		try {

			node_number = PositionFinder ( nodes, v.GetStartNode() );

		}

		catch ( int wrong ) {

			printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER AND NO. IS %d\n", wrong );

			system("pause");

		};
		
		nodes[node_number].RemoveOutletVessel( v.GetPlaceOnStartingNode() );

		int pos;

		try {

			pos = PositionFinder( vec, v.GetIDNumber() );

		}

		catch ( int wrong ) {

			printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER AND NO. IS %d\n", wrong );

			system("pause");

		};
		
		RemoveFromMotherVessels( vec, vec[pos] );
		
		vec.erase( vec.begin() + pos );

		if ( nodes[node_number].GetNumberOfBranches() == 1 ) {

			RemoveLastVessel( vec, nodes[node_number], node_number );

			nodes[node_number].RemoveAllBranches();

		}

		else if ( nodes[node_number].GetNumberOfBranches() == 2 ) {

			ConcatenateVessels( nodes[node_number] );

		};

	}

	else if ( v.GetInletStatus() == 1 ) {

		int node_number;

		try {

			node_number = PositionFinder ( nodes, v.GetEndNode() );

		}

		catch ( int wrong ) {

			printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER AND NO. IS %d\n", wrong );

			system("pause");

		};

		nodes[node_number].RemoveInletVessel( v.GetPlaceOnEndingNode() );

		int pos;

		try {

			pos = PositionFinder( vec, v.GetIDNumber() );

		}

		catch ( int wrong ) {

			printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER AND NO. IS %d\n", wrong );

			system("pause");

		};

		vec.erase( vec.begin() + pos );

		if ( nodes[node_number].GetNumberOfBranches() == 1 ) {

			RemoveLastVessel( vec, nodes[node_number], node_number );

			nodes[node_number].RemoveAllBranches();

		}

		else if ( nodes[node_number].GetNumberOfBranches() == 2 ) {

			ConcatenateVessels( nodes[node_number] );

		};

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITION OF THE FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RemoveFromMotherVessels( std::vector<cVessel>& vec, cVessel& v ) {

	for( unsigned i = 0; i < vec.size(); ++i ) {

		for ( size_t j = 0; j < vec[i].prohibiteds.size(); ++j ) {

			if ( vec[i].prohibiteds[j] == v.GetIDNumber() ) {

				vec[i].prohibiteds.erase( vec[i].prohibiteds.begin() + j );

				break;

			};

		};

	};

};
// ==================================================================================================================================================================================
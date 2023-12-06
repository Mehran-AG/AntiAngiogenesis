#include "Initials.h"

#include "dimension.h"

#include "OutputWriter.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//HERE I SCHEMATICALLY DRAW THE INITIAL MAIN VESSEL AND IMAGINARY SPROUTS AND NUMBERING PROCEDURE ---------------------------------------------------------------------------------------------
//
//               |
//               |  Pressure = DeltaP
//               |
//               v
//        NODE 4 o----> SPROUT 8
//               v
//               |
//             3 |
//               |
//               v
//        NODE 3 o----> SPROUT 7
//               v
//               |
//             2 |
//               |
//               v
//        NODE 2 o----> SPROUT 6
//               v
//               |
//             1 |
//               |
//               v
//        NODE 1 o----> SPROUT 5
//               v
//               |
//             0 |
//               |
//               v
//        NODE 0 o----> SPROUT 4
//               v
//               |
//               |  Pressure = 0
//               |
//               v
//           MAIN VESSEL
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Initials() {

	printf("\nINITIALS STARTED");

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cVessel> vessels;

	extern std::vector<int> sprouts;

// INITIATION OF THE PROCEDURE ------------------------------------------------------------------------------------------------------------------------------------------------------
	
	int parent_num = sprouts.size() - 1; // NUMBER OF INITIAL SEGMENTS OF PARENT VESSEL

	int sprouts_num = sprouts.size(); // NUMBER OF INITIAL SPROUTS ON PARENT VESSEL

// CREATING INITIAL SEGMENTS OF PARENT VESSEL ---------------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < parent_num; ++i ) {

		cVessel parent_vessel( i );

		vessels.push_back( parent_vessel );

	};

// CREATING INITIAL SPROUTS ---------------------------------------------------------------------------------------------------------------------------------------------------------

	int total_initial_vessels = parent_num + sprouts_num;

	for ( int i = parent_num; i < total_initial_vessels; ++i ) {

		cVessel daughter_vessel( i );

		vessels.push_back( daughter_vessel );

	};

// DEFINING SPECIFICATIONS OF SEGMENTS ON PARENT VESSEL -----------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < parent_num; ++i ) {

		int length = sprouts[i+1] - sprouts[i];

		vessels[i].SetVesselUnitLength( length );

		vessels[i].SetInletStatus( 0 );

		vessels[i].SetOutletStatus( 0 );

		vessels[i].AssignStartingNode( i+1 );

		vessels[i].AssignPlaceOnStartingNode( 1 );

		vessels[i].AssignEndingNode( i );

		vessels[i].AssignPlaceOnEndingNode( 1 );

		vessels[i].SetDiameter( 14 );

	};

// DEFINING SPECIFICATIONS OF SPROUTS -----------------------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < sprouts_num; ++i ) {

		int num = i + parent_num;

		vessels[num].SetPath( 1, sprouts[i] );

		vessels[num].SetTipCellPosition( 1, sprouts[i] );

		vessels[num].SetStartingPoint( 1, sprouts[i] );

		vessels[num].SetInletStatus( 0 );

		vessels[num].SetOutletStatus( 1 );

		vessels[num].AssignStartingNode( i );

		vessels[num].AssignPlaceOnStartingNode( 2 );

	};


// PRESCRIBE INLET & OUTLET VESSELS FOR EACH INITIAL NODE ---------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cNode> nodes;

	int nodes_num = sprouts_num;

// CREATING THE INITIAL NODES -------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < nodes_num; ++i ){

		cNode new_node( i );

		nodes.push_back( new_node );

	};

// SETTING X AND Y POSITION OF THE INITIAL NODES ------------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < nodes_num; ++i ) {

		nodes[i].SetXPosition( 1 );

		nodes[i].SetYPosition( sprouts[i] );

	};

// ASSIGNING INLETS AND OUTLETS TO THE INTIAL NODES ---------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 0; i < nodes_num; ++i ) {

		int diff = nodes_num - 1;

		int inlet1 = i;

		int outlet1 = i - 1;

		int outlet2 = i + diff;

		// first node's inlet and outlets are different
		if ( i == 0 ) {

			nodes[i].AssignInletsAndOutlets( i, -1, -1, outlet2 );

			continue;

		}

		// last node's inlet and outlets are different
		else if ( i == diff ) {

			nodes[i].AssignInletsAndOutlets( -1, -1, outlet1, outlet2 );

			continue;

		}

		else {

			nodes[i].AssignInletsAndOutlets( inlet1, -1, outlet1, outlet2 );

		};

	};


};
// ==================================================================================================================================================================================
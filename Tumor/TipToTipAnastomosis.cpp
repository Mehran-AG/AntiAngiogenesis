#include "TipToTipAnastomosis.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

#include "VesselRemover.h"

#include <vector>

#include <conio.h>

#include <iostream>

#include <fstream>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TipToTipAnastomosis( int i, int j, size_t& migrating_vessel_num ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern int shorest_vessel_length;

	extern std::ofstream printer;

	bool a_indicator = false;

	extern int loop_indicator;

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// asigning new name for the migrating vessel
	cVessel& ttt_migrating_vessel = vessels[migrating_vessel_num];

	for ( size_t stationary_vessel_num = 0; stationary_vessel_num < vessels.size(); ++stationary_vessel_num ) {  // for1

		cVessel& stationary_vessel = vessels[stationary_vessel_num];

		if ( stationary_vessel_num == migrating_vessel_num ) continue;

		if ( ( ttt_migrating_vessel.Get_X_CoordianteOfTEC() > 0 ) && ( ttt_migrating_vessel.Get_Y_CoordianteOfTEC() > 0 ) ) { // if2

			if ( ( ttt_migrating_vessel.Get_X_CoordianteOfTEC() == stationary_vessel.Get_X_CoordianteOfTEC() ) && ( ttt_migrating_vessel.Get_Y_CoordianteOfTEC() == stationary_vessel.Get_Y_CoordianteOfTEC() ) ) { // if1

				try {

					if ( ttt_migrating_vessel.GetUnitLength() < shorest_vessel_length ) throw 20;

					if ( stationary_vessel.GetUnitLength() < shorest_vessel_length ) throw 20;

				}

				catch ( int ) {

					VesselRemover( vessels, ttt_migrating_vessel );

					a_indicator = true;

					--migrating_vessel_num;

					goto end;

				};

				printer << "TIP ANASTOMOSIS OCCURED" << std::endl;

				printf( "\nTIP ANASTOMOSIS OCCURED" );

				// when two tip sprouts meet each other, their boolean functions must be zero in order to stop their growth
				ttt_migrating_vessel.StopGrowing( i, j );
				stationary_vessel.StopGrowing( i, j );

				// when new sprout emerged, number of tip cells must increase by 1
				int v_number = vessels[0].GetQuantity();

				cVessel new_vessel( v_number );

				printer << "VESSEL " << ttt_migrating_vessel.GetIDNumber() << " AND " << stationary_vessel.GetIDNumber() << " ENCOUNTERED AND VESSEL " << v_number << " IS CREATED" << std::endl;

				printf ( "\nVESSEL %u AND %u ENCOUNTERED AND VESSEL %u IS CREATED", ttt_migrating_vessel.GetIDNumber(), stationary_vessel.GetIDNumber(), v_number );

				// adding the ID numbers of stationary and migrating vessel in order not to have self anastomosis
				new_vessel.AddToProhibiteds( ttt_migrating_vessel.GetIDNumber() );
				new_vessel.AddToProhibiteds( stationary_vessel.GetIDNumber() );

				new_vessel.StartVessel( i, j );

				// anastomosis occurred, so the number of nodes must be increased by 1
				int n_number = nodes[0].GetQuantity();

				cNode new_node( n_number );

				// defining the position of the node (it is needed in concatenating vessels)
				new_node.SetXPosition( i );

				new_node.SetYPosition( j );

				// specifying end node number for each ending capillaries
				ttt_migrating_vessel.AssignEndingNode( n_number );
				stationary_vessel.AssignEndingNode( n_number );

				// specifying start node number for new capillary
				new_vessel.AssignStartingNode( n_number );

				// Assigning the number of inlets to the node and also inlet and outlet capillaries number to the node
				new_node.AssignInletsAndOutlets ( ttt_migrating_vessel.GetIDNumber(), stationary_vessel.GetIDNumber(), v_number, -1 );

				ttt_migrating_vessel.AssignPlaceOnEndingNode ( 1 );
				stationary_vessel.AssignPlaceOnEndingNode ( 2 );
				new_vessel.AssignPlaceOnStartingNode ( 1 );

				vessels.push_back( new_vessel );

				nodes.push_back( new_node );

				a_indicator = true;

				return a_indicator;

			}; // end of if1

		}; // end of if2

	}; // end of for1

	end:

	return a_indicator;

};
// ==================================================================================================================================================================================
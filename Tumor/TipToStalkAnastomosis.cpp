#include "TipToStalkAnastomosis.h"

#include "dimension.h"

#include <iostream>

#include <vector>

#include <conio.h>

#include <cstdlib>

#include "cVessel.h"

#include "cNode.h"

#include "BranchTracker.h"

#include "OutputWriter.h"

#include "PositionFinder.h"

#include "VesselRemover.h"

#include "ChangeProhibitedVessels.h"

#include "AddToProhibitedVessels.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function decieds if the tip has encountered any stalk cells or not ----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool TipToStalkCollision ( cVessel& v1, cVessel& v2 ) {

		if ( v1.GetPath( v2.Get_X_CoordianteOfTEC(), v2.Get_Y_CoordianteOfTEC() ) == 1 ) return true;
		else return false;

};
//===================================================================================================================================================================================


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function creates distinct vessels if the TEC has encountered a stalk cell ---------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool TipToStalkAnastomosis ( int i, int j, size_t& migrating_vessel_num ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern int nx, ny;

	extern int loop_indicator;

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern int shorest_vessel_length;

	extern std::ofstream printer;

	bool a_indicator = false;

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	cVessel& tts_migrating_vessel = vessels[migrating_vessel_num];

	for ( size_t stationary_vessel_num = 0; stationary_vessel_num < vessels.size(); ++stationary_vessel_num ) {

		cVessel& stationary_vessel = vessels[stationary_vessel_num];

		if ( stationary_vessel_num == migrating_vessel_num ) continue;

		if ( TipToStalkCollision ( stationary_vessel, tts_migrating_vessel ) ) { // if1

			int unit_length_tracked = 0;

			BranchTracker( i, j, stationary_vessel, unit_length_tracked );

			try {

				if ( tts_migrating_vessel.GetUnitLength() < shorest_vessel_length ) throw 20;

				int unit_length_tracked = 0;

				BranchTracker( i, j, stationary_vessel, unit_length_tracked );

				if ( ( unit_length_tracked < shorest_vessel_length ) || ( ( stationary_vessel.GetUnitLength() - unit_length_tracked ) < shorest_vessel_length ) ) throw 20;

			}

			catch ( int ) {

				VesselRemover( vessels, tts_migrating_vessel );

				--migrating_vessel_num;

				goto end;

			};

			printer << "TSC ANASTOMOSIS OCCURED" << std::endl;

			printf("\nTSC ANASTOMOSIS OCCURED");

			// when tip-stalk cell anastomosis occurs, i stop the growth of colliding tip cell(i must stop the one that has collided by this sprout)
			tts_migrating_vessel.StopGrowing( i, j );

			int v_number = vessels[0].GetQuantity();

			cVessel new_vessel( v_number );

			printer << "VESSELS " << tts_migrating_vessel.GetIDNumber() << " and " << stationary_vessel.GetIDNumber() << " ANASTOMOSED AND VESSEL " << v_number << " EMERGED" << std::endl;

			printf( "\nVESSELS %u and %u ANASTOMOSED AND VESSEL %u EMERGED", tts_migrating_vessel.GetIDNumber(), stationary_vessel.GetIDNumber(), v_number );

			int n_number = nodes[0].GetQuantity();

			cNode new_node( n_number );

			// defining the position of the node (it is needed in concatenating vessels)
			new_node.SetXPosition( i );

			new_node.SetYPosition( j );

			new_vessel.SetStartingPoint( i, j );

			BranchTracker( i, j, stationary_vessel, new_vessel );

			new_vessel.SetTipCellPosition ( stationary_vessel );
		
			stationary_vessel.SetTipCellPosition ( 0, 0 );

			AddToProhibitedVessels( vessels, new_vessel, stationary_vessel );

			if ( stationary_vessel.GetOutletStatus() == 0 ) {

				new_vessel.CopyEndNode( stationary_vessel );

				int enode = stationary_vessel.GetEndNode();

				int place = stationary_vessel.GetPlaceOnEndingNode();

				int position;

				try {

					position = PositionFinder( nodes, enode );

				}

				catch ( int wrong ) {

					printf( "\nNO MATCHES IN THE NODE VECTOR IN TIP TO STALK ANASTOMOSIS AND NO. IS %d\n", wrong );

					system("pause");

				};

				nodes[position].ReplaceInletVessel( v_number, place );

				stationary_vessel.AssignEndingNode( n_number );

				// specifying end node number for colliding capillary
				tts_migrating_vessel.AssignEndingNode( n_number );

				new_vessel.AssignStartingNode( n_number );

				new_vessel.SetInletStatus( 0 );

				new_vessel.SetOutletStatus( 0 );

			}

			else {

				stationary_vessel.AssignEndingNode( n_number );

				// specifying end node number for colliding capillary
				tts_migrating_vessel.AssignEndingNode( n_number );

				new_vessel.AssignStartingNode( n_number );

				new_vessel.SetInletStatus( 0 );

			};

			// specifying end indicator of collided capillary
			tts_migrating_vessel.SetOutletStatus( 0 );

			stationary_vessel.SetOutletStatus( 0 );

			new_node.AssignInletsAndOutlets( tts_migrating_vessel.GetIDNumber(), stationary_vessel.GetIDNumber(), v_number, -1 );

			tts_migrating_vessel.AssignPlaceOnEndingNode ( 1 );
			stationary_vessel.AssignPlaceOnEndingNode ( 2 );
			new_vessel.AssignPlaceOnStartingNode ( 1 );

			tts_migrating_vessel.SetPathStorer( i, j, 's' );
			stationary_vessel.SetPathStorer( i, j, 's' );

			// adding the ID numbers of stationary and migrating vessel in order not to have self anastomosis
			new_vessel.AddToProhibiteds( tts_migrating_vessel.GetIDNumber() );
			new_vessel.AddToProhibiteds( stationary_vessel.GetIDNumber() );

			vessels.push_back( new_vessel );

			nodes.push_back( new_node );

			a_indicator = true;

			return a_indicator;

			}; // end of if1

		}; // end of for

		end:

	return a_indicator;

};
// ==================================================================================================================================================================================
#include "Branching.h"

#include "dimension.h"

#include "BranchTracker.h"

#include "cVessel.h"

#include "cNode.h"

#include "ProximityCheck.h"

#include "VEGF_Check.h"

#include "DirectionFinder.h"

#include "OutputWriter.h"

#include <vector>

#include <conio.h>

#include <cstdlib>

#include <fstream>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Branching() {

	printf("\nBRANCHING STARTED");

// declaration of variables ---------------------------------------------------------------------------------------------------------------------------------------------------------
	int i = 0, j = 0;

	bool proximity_flag = false;

	bool VEGF_flag = false;

	unsigned char direction;

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern int shorest_vessel_length;

	extern std::ofstream printer;

	extern int maturity_time; // This is the time needed for the new daughter capillaries to mature and be allowed to branch

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// INITIATION OF PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( size_t counter = 0; counter < vessels.size(); ++counter ) {

		cVessel& mother_vessel = vessels[counter];

		if ( mother_vessel.GetOutletStatus() == 1 )  {

			if ( ( mother_vessel.GetAge() > maturity_time ) && ( mother_vessel.GetUnitLength() > shorest_vessel_length ) ) {

				int i = mother_vessel.Get_X_CoordianteOfTEC();
				int j = mother_vessel.Get_Y_CoordianteOfTEC(); // locate the tip cell if the age requirement is met

				proximity_flag = false; // Before letting a capillary to branch, it should be checked to see if there is enough empty space around it or not
										// So we seek to see if there is any capillaries around this capillary or not

				for ( size_t searching_vessel = 0; searching_vessel < vessels.size(); ++searching_vessel ) {

					if ( searching_vessel == counter ) continue;

					ProximityCheck( vessels[searching_vessel], i, j, proximity_flag );

				};

				direction = DirectionFinder( mother_vessel, i, j); // this function determines which neighboring grids are empty for the newly formed tip cell to posses

				if ( direction == 'r' || direction == 'l' ) {

					if ( mother_vessel.GetPath( i, j+1 ) || mother_vessel.GetPath( i, j-1 ) )
						proximity_flag = true;

				}

				else {

					if ( mother_vessel.GetPath( i+1, j ) || mother_vessel.GetPath( i-1, j ) )
						proximity_flag = true;

				};

// ----------------------- If proximity flag is false (Which means that there is no capillaries next to the capillary), it can branch --------------------------------------------

				if ( proximity_flag == false ) {

// ----------------------- The probability of branching is checked to see if the vessel can branchbased on VEGF concentration --------------------------------------

					VEGF_flag = VEGF_Check( i, j );

					if ( VEGF_flag == true ) {

						int nb1 = mother_vessel.GetQuantity();

						int nb2 = nb1 + 1;

						cVessel daughter_vessel_1( nb1 );

						cVessel daughter_vessel_2( nb2 );

						printer << "BRANCHING OCCURED" << std::endl; 

						printer << "VESSEL NO. " << mother_vessel.GetIDNumber() << " BRANCHED AND VESSELS " << nb1 << " AND " << nb2 << " EMERGED" << std::endl;

						printf ( "\nBRANCHING OCCURED" );

						printf( "\nVESSEL NO. %u BRANCHED AND VESSELS %u AND %u EMERGED", mother_vessel.GetIDNumber(), nb1, nb2 );

						// when two new sprouts emerges, stop growth of the branched tip cell
						mother_vessel.StopGrowing( i, j );

						int n_number = nodes[0].GetQuantity();

						cNode new_node( n_number );

						// defining the position of the node (it is needed in concatenating vessels)
						new_node.SetXPosition( i );

						new_node.SetYPosition( j );

						// specifying the end node_r number for capillary
						mother_vessel.AssignEndingNode( n_number );

						// specifying start node number for new capillaries
						daughter_vessel_1.AssignStartingNode( n_number );
						daughter_vessel_2.AssignStartingNode( n_number );

						new_node.AssignInletsAndOutlets ( mother_vessel.GetIDNumber(), -1 , nb1, nb2 );

						mother_vessel.AssignPlaceOnEndingNode( 1 );
						daughter_vessel_1.AssignPlaceOnStartingNode ( 1 );
						daughter_vessel_2.AssignPlaceOnStartingNode ( 2 );

						// in this step, I store the number of branched capillary to prevent new capillaries from colliding with it
						daughter_vessel_1.SetMotherVessel( mother_vessel.GetIDNumber() );
						daughter_vessel_2.SetMotherVessel( mother_vessel.GetIDNumber() );

						// adding the mother vessel to prohibiteds vector of the daughter vessel in order to prevent them from encountering to avoid self looping
						daughter_vessel_1.AddToProhibiteds( mother_vessel.GetIDNumber() );
						daughter_vessel_2.AddToProhibiteds( mother_vessel.GetIDNumber() );

						//----------- determine the position of the newly formed tip cell ----------------------   

						if ( direction == 'r' || direction == 'l' ) {

							daughter_vessel_1.StartVessel( i, j, 'u' );

							daughter_vessel_2.StartVessel( i, j, 'd' );

						}

						else {

							daughter_vessel_1.StartVessel( i, j, 'l' );

							daughter_vessel_2.StartVessel( i, j, 'r' );

						};

						vessels.push_back( daughter_vessel_1 );

						vessels.push_back( daughter_vessel_2 );

						nodes.push_back( new_node );

					}; // VEGF_flag

				}; // proximity_flag

			}; // end of 2nd if

		}; // end of 1st if

	}; // end of for

	printf("\nBRANCHING ENDED");

};
// ==================================================================================================================================================================================
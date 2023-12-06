#include <fstream>

#include <iostream>

#include "UnendedCapillaryRemover.h"

#include "dimension.h"

#include "PositionFinder.h"

#include "RemoveLastVessel.h"

#include "RemoveNodeVessel.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UnendedCapillaryRemover() {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	//printf( "\nCap Remover Started" );

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::vector<int> sprouts;

	extern std::ofstream printer;

	bool search_finish = false;

	int node_number;


	//printer <<"\n1 CAP NODE REMOVER NODES\n"<<std::endl;

// SEARCHING FOR THE UNENDED CAPILLARIES --------------------------------------------------------------------------------------------------------------------------------------------

	while ( search_finish != true ) {

		search_finish = true;

		for ( auto i = vessels.begin(); i < vessels.end(); ++i ) { // for1
			
			if ( ( i->GetOutletStatus() == 1 ) || ( i->GetInletStatus() == 1 ) ) { // if1

				search_finish = false;

				if ( i->GetOutletStatus() == 1 ) { // If the vessels OUTLET part is open, so it must be removed

					try {

						node_number = PositionFinder ( nodes, i->GetStartNode() );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN NODES VECTOR IN UNENDED CAPILLARY REMOVER AND NODE NO. IS %d\n", wrong );

						system("pause");

					};

					nodes[node_number].RemoveOutletVessel( i->GetPlaceOnStartingNode() );

					//printf( "\nVESSEL NO. %d IS BEING REMOVED", i->GetIDNumber() );

					i = vessels.erase ( i );

					if ( i != vessels.begin() )
						--i;

				}

				else if ( i->GetInletStatus() == 1 ) { // If the vessels INLET part is open, so it must be removed

					try {

						node_number = PositionFinder ( nodes, i->GetEndNode() );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN NODES VECTOR IN UNENDED CAPILLARY REMOVER AND NODE NO. IS %d\n", wrong );

						system("pause");

					};

					nodes[node_number].RemoveInletVessel( i->GetPlaceOnEndingNode() );

					i = vessels.erase ( i );

					--i;

				};
				
			}; // end of if1

		}; // end of for1

// SEARCHING FOR nodes TO SEE IF THEY ARE NEEDED TO DELETE OR NOT -------------------------------------------------------------------------------------------------------------------

		for ( size_t i = 0; i < nodes.size(); ) { // for2

			if ( i < sprouts.size() ) {

				if ( sprouts.size() == 1 ) {

					++i;

					continue;

				};

				if ( i == 0 ) {

					if ( nodes[i].GetNumberOfBranches() == 1 ) {

						RemoveNodeVessel( nodes[0] );

						sprouts.erase( sprouts.begin() );

					}

					else
						++i;

				}

				else if ( i == (sprouts.size()-1) ) {

					if ( nodes[i].GetNumberOfBranches() == 1 ) {

						RemoveNodeVessel( nodes[sprouts.size()-1] );

						sprouts.erase( sprouts.begin() + sprouts.size() - 1 );

					}

					else
						++i;

				}
				
				else if ( nodes[i].GetNumberOfBranches() == 2  ) {

					// outlet vessel's identity
					int outlet;

					if ( nodes[i].GetOutletVesselNumber( 1 ) >= 0 ) {

						outlet = nodes[i].GetOutletVesselNumber( 1 );

					}

					else if ( nodes[i].GetOutletVesselNumber( 2 ) >= 0 ) {

						outlet = nodes[i].GetOutletVesselNumber( 2 );

					}

					else if ( nodes[i].GetOutletVesselNumber( 3 ) >= 0 ) {

						outlet = nodes[i].GetOutletVesselNumber( 3 );

					};

					// inlet vessel's identity
					int inlet;

					if ( nodes[i].GetInletVesselNumber( 1 ) >= 0 ) {

						inlet = nodes[i].GetInletVesselNumber( 1 );

					}

					else if ( nodes[i].GetInletVesselNumber( 2 ) >= 0 ) {

						inlet = nodes[i].GetInletVesselNumber( 2 );

					}

					else if ( nodes[i].GetInletVesselNumber( 3 ) >= 0 ) {

						inlet = nodes[i].GetInletVesselNumber( 3 );

					};

					int inlet_num, outlet_num;

					try {

						// outlet vessel's position in the vector
						outlet_num = PositionFinder( vessels, outlet );

						// inlet vessel's position in the vector
						inlet_num = PositionFinder( vessels, inlet );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND VESSEL NO. IS %d\n", wrong );

						system("pause");

					};

					// assigning new names for the vessels
					cVessel& main = vessels[inlet_num];

					cVessel& secondary = vessels[outlet_num];

					// identity of end node is get to remove secondary vessel from it
					int e_node_identity = secondary.GetEndNode();

					int e_node_pos;
				
					try {
				
						e_node_pos = PositionFinder( nodes, e_node_identity );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND VESSEL NO. IS %d\n", wrong );

						system("pause");

					};

					// specifications of the secondary vessel is copied to main vessel
					main.CopyEndNode( secondary );

					int place = secondary.GetPlaceOnEndingNode();

					nodes[e_node_pos].ReplaceInletVessel( main.GetIDNumber(), place );

					// length and age of the concatenated vessel is assigned
					int total_unit_length = main.GetUnitLength() + secondary.GetUnitLength();

					int age = main.GetAge() + secondary.GetAge();

					main.SetVesselUnitLength( total_unit_length );

					main.SetAge( age );

					size_t c;

					for ( c = 0; c < sprouts.size(); ++c ) {

						if ( nodes[i].GetYPosition() == sprouts[c] ) break;

					};

					sprouts.erase( sprouts.begin() + c );

					int removed_position;
			
					try {
			
						removed_position = PositionFinder( nodes, nodes[i].GetIDNumber() );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND VESSEL NO. IS %d\n", wrong );

						system("pause");

					};

					nodes.erase( nodes.begin() + removed_position );

					vessels.erase( vessels.begin() + outlet_num );

				}

				else {

					++i;

				};

			}

			else {

				if ( nodes[i].GetNumberOfBranches() == 1 ) {

					nodes[i].RemoveAllBranches();

					search_finish = false;

					RemoveLastVessel( vessels, nodes[i] );

					nodes.erase ( nodes.begin() + i );

					/*if ( i != 0 )
						--i;*/

				}

				else {

					++i;

				};

			};

		}; // end of for2

	}; // end of while


	//printf( "\nCap Remover Ended" );

};
// ==================================================================================================================================================================================
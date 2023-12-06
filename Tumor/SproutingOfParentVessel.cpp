#include "SproutingOfParentVessel.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

#include "PositionFinder.h"

#include <cstdlib>

#include <vector>

#include <iostream>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION REMOVES DEFINED NUMBER OF NEARBY POINTS AROUND A NEWLY EMERGED POINT THAT MUST BE REMOVED WHEN A NEW SPORUT EMERGES IN A POINT -------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ClearSurrounding( int, int, bool*, bool* );

int Place( int );
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS STRUCTURE STORES THE POINTS WHICH ARE NOMINIZED FOR SPROUTING, BUT AS PROBABILITY OF THE SPROUTING NEEDS TO DETERMINE THE NEW SPROUT FORMATION, IT MUST KEEP THE PROBABILITY
// FOR THE POINT, SO IF THE PRBABILITY IS NOT SATISFIED, IT WILL BE EXCLUDED FROM THE POINTS ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct points {

	int i;

	double p;

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION RANDOMLY DEFINES THE LOCATION OF SPROUTS ON PARENT VESSEL "DURING THE SIMULATION PROCESS" --------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void SproutingOfParentVessel() {

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern double dt;

	extern double k_p;

	extern double l_seg;

	extern double dim_t;

	extern double c_th;

	extern double c_th_50;

	extern double c_ref;

	extern double c[a_dim][a_dim];

	double cd[a_dim]; // dimensional VEGF concentration

	extern std::vector<int> sprouts;

	extern int ny;

	extern bool uncheckedVEGF[a_dim];

	extern bool available_spots[a_dim];

	extern int distance;

	int first = distance;

	int last = ny - distance;

	extern double coef; 

	// since concentration of VEGF was normalized, here it will be denormalized with the reference value of concentration for normalization of the gradient
	for ( int i = 0; i < ny; ++i ) {

		cd[i] = c[1][i] * c_ref * coef; // 1500 is added to obey the rules imposed by the paper, I added it heuristically

	};

	// concentration in different points are checked to see if the points are eligible for sprouting or not based on the threshold value
	for( int i = first; i < last; ++i ) {

		if ( cd[i] > c_th ) {

			uncheckedVEGF[i] = 0;

			available_spots[i] = 1;

		};

	};

	// since on the parent vessel, some sprouts had emerged prior to calling this function, the sprouts surroundings must be cleared after checking for available spots
	for ( size_t i = 0; i < sprouts.size(); ++i ) {

		ClearSurrounding( sprouts[i], distance, available_spots, uncheckedVEGF );

	};

	// a vector is defined to store the spots (points) which are nominized, because I want to generate a random number based on the number of spots to choose them randomly
	std::vector<points> spots;

	for( int i = first; i < last; ++i ) {

		if ( available_spots[i] != 0 ) {

			points new_p;

			new_p.i = i;

			new_p.p = k_p * l_seg * dt * dim_t * ( ( cd[i] - c_th ) / ( cd[i] - c_th + c_th_50 ) );

			spots.push_back(new_p);

		};

	};

	while ( spots.size() ) {

		int sprouted = 0;

		while ( !sprouted ) { // this loop will iterate until the value for sprouted which shows the y coordiante of sprout is not equal to zero

			int r_num = rand() % spots.size();

			double r_num_p = (double) rand() / RAND_MAX;

			if ( r_num_p <= spots[r_num].p ) {

				sprouted = spots[r_num].i;

				int place = Place( sprouted );

				// since this function will be called during simulation, there will be some sprouts initiated earlier, so we have to put the new sprout where it is needed, between old ones
				if ( place == 0 ) {

// ---------------- When the spot for sprouting is under the lowest existing sprout, we just create a new node and vessel and put them under the existing one -----------------------
// ---------------- New node is placed at the beginning of the nodes and vessels vectors --------------------------------------------------------------------------------------------

					// any sprout's y position must be kept in the sprouts vector, this way we can know the number of sprouts and also put new ones in the right place
					sprouts.insert( sprouts.begin(), sprouted );

					int nb1 = vessels[0].GetQuantity();

					int nb2 = nb1 + 1;

					cVessel new_p_vessel( nb1 );

					cVessel new_d_vessel( nb2 );

					new_p_vessel.SetOutletStatus( 0 );

					new_p_vessel.SetDiameter( 14 );

					int s_node = vessels[0].GetEndNode();

					new_p_vessel.AssignStartingNode( s_node );

					new_p_vessel.AssignPlaceOnStartingNode( nodes[0].AssignOutletVesselGetPlace( nb1 ) );

					int nn = nodes[0].GetQuantity();

					cNode new_node( nn );

					new_node.SetXPosition( 1 );

					new_node.SetYPosition( sprouts[0] );

					new_p_vessel.AssignEndingNode( nn );

					new_p_vessel.AssignPlaceOnEndingNode( new_node.AssignInletVesselGetPlace( nb1 ) );

					new_p_vessel.SetVesselUnitLength( abs( sprouts[1] - sprouts[0]) );

					new_d_vessel.AssignStartingNode( nn );

					new_d_vessel.AssignPlaceOnStartingNode( new_node.AssignOutletVesselGetPlace( nb2 ) );

					new_d_vessel.StartVessel( 1, sprouts[0] );

					vessels.insert( vessels.begin(), new_p_vessel );

					vessels.push_back( new_d_vessel );

					std::cout << "VESSEL NO. " << nb2 << " EMERGED FROM PARENT VESSEL" << std::endl;

					nodes.insert( nodes.begin(), new_node );

				}

				else if ( place == sprouts.size() ) {

// ----------------- When the spot for sprouting is above the highest existing sprout, we just create a new node and vessel and put them above the existing ones --------------------
// ----------------- New node is placed at the place in nodes and vectors vectors where the place is the same as last place in sprouts vector ---------------------------------------

					sprouts.push_back( sprouted );

					int nb1 = vessels[0].GetQuantity();

					int nb2 = nb1 + 1;

					cVessel new_p_vessel( nb1 );

					cVessel new_d_vessel( nb2 );

					new_p_vessel.SetOutletStatus( 0 );

					new_p_vessel.SetDiameter( 14 );

					int v_place =sprouts.size() - 3;

					int n_place = sprouts.size() - 2;

					int e_node = vessels[v_place].GetStartNode();

					new_p_vessel.AssignEndingNode( e_node );

					new_p_vessel.AssignPlaceOnEndingNode( nodes[n_place].AssignInletVesselGetPlace( nb1 ) );

					int nn = nodes[0].GetQuantity();

					cNode new_node( nn );

					new_node.SetXPosition( 1 );

					new_node.SetYPosition( sprouts[place] );

					new_p_vessel.AssignStartingNode( nn );

					new_p_vessel.AssignPlaceOnStartingNode( new_node.AssignOutletVesselGetPlace( nb1 ) );

					new_p_vessel.SetVesselUnitLength( abs( sprouts[place] - sprouts[place-1]) );

					new_d_vessel.AssignStartingNode( nn );

					new_d_vessel.AssignPlaceOnStartingNode( new_node.AssignOutletVesselGetPlace( nb2 ) );

					new_d_vessel.StartVessel( 1, sprouts[place] );

					vessels.insert( vessels.begin() + v_place + 1, new_p_vessel );

					vessels.push_back( new_d_vessel );

					std::cout << "VESSEL NO. " << nb2 << " EMERGED FROM PARENT VESSEL" << std::endl;

					nodes.insert( nodes.begin() + n_place + 1, new_node );

				}

				else {

// ----------------- When the emerging sprout is between the existing ones, the upper node and vessel will be moved forward in the correspondant vectors ----------------------------

					sprouts.insert( sprouts.begin() + place, sprouted );

					int node_pos = place;

					int vessel_pos = place - 1;

					cVessel& vessel = vessels[vessel_pos];

					int n_q = nodes[0].GetQuantity();

					cNode new_node( n_q );

					new_node.SetXPosition( 1 );

					new_node.SetYPosition( sprouts[place] );

					int nb1 = vessels[0].GetQuantity();

					int nb2 = nb1 + 1;

					cVessel new_p_vessel( nb1 );

					cVessel new_d_vessel( nb2 );

					new_p_vessel.SetOutletStatus( 0 );

					new_p_vessel.SetDiameter( 14 );

					new_p_vessel.CopyStartNode( vessel );

					int s_node_pos = PositionFinder( nodes, vessel.GetStartNode() );

					int s_place = vessel.GetPlaceOnStartingNode();

					nodes[s_node_pos].ReplaceOutletVessel( nb1, s_place );

					vessel.SetVesselUnitLength( sprouts[place] - sprouts[place-1] );

					new_p_vessel.SetVesselUnitLength( sprouts[place+1] - sprouts[place] );

					new_node.AssignInletsAndOutlets( nb1, -1, vessel.GetIDNumber(), nb2 );

					new_p_vessel.AssignEndingNode( n_q );

					vessel.AssignStartingNode( n_q );

					new_d_vessel.AssignStartingNode( n_q );

					new_p_vessel.AssignPlaceOnEndingNode( 1 );

					vessel.AssignPlaceOnStartingNode( 1 );

					new_d_vessel.AssignPlaceOnStartingNode( 2 );

					new_d_vessel.StartVessel( 1, sprouts[place] );

					vessels.insert( vessels.begin() + place, new_p_vessel );

					vessels.push_back( new_d_vessel );

					std::cout << "VESSEL NO. " << nb2 << " EMERGED FROM PARENT VESSEL" << std::endl;

					nodes.insert( nodes.begin() + place, new_node );

				}; // ===============================================================================================================================================================

			}; // end of probability if

		}; // end of while

		// after a sprout emerges, its surrounding must be cleaned in case there are any other nominated spots
		ClearSurrounding( sprouted, distance, available_spots, uncheckedVEGF );

		// Then the vector of nominated points are cleared to start filling it again in case some spots are removed due to emergence of a nearby sprout
		spots.clear();

		// the spots vector is filled with nominated points to start the loop again
		for( int i = first; i < last; ++i ) {

			if ( available_spots[i] != 0 ) {

				points new_p;

				new_p.i = i;

				new_p.p = k_p * l_seg * dt * dim_t * ( ( cd[i] - c_th ) / ( cd[i] - c_th + c_th_50 ) );

				spots.push_back(new_p);

			};

		};
	};

	std::cout << "\nNO. OF SPROUTS ARE: " << sprouts.size();

	// When the sprouts vector is defined, it should be sorted from the lowest value starting the vector to the highest value at the end of the vector
	for( size_t i = 0; i < sprouts.size(); ++i ) {

		for( size_t j = i+1; j < sprouts.size(); ++j ) {

			if ( sprouts[i] > sprouts[j] ) {

				int temp = sprouts[i];
				sprouts[i] = sprouts[j];
				sprouts[j] = temp;

			};

		};	

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION THE PLACE IN THE SPROUTS VECTOR WHERE NEW SPROUT MUST BE STORED ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Place( int s ) {

	extern std::vector<int> sprouts;

	size_t i = 0;

	for ( i = 0; i < sprouts.size(); ++i ) {

		if ( s < sprouts[i] ) {

			return i;

		};

	};

	return i;

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITION OF FUNCTION -----------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//void ClearSurrounding( int sprout, int distance, bool* a, bool* b ) {
//
//	int lower = sprout - distance;
//
//	int upper = sprout + distance;
//
//	for ( int i = lower; i < upper; ++i ) {
//
//		a[i] = 0;
//
//		b[i] = 0;
//
//	};
//
//};
// ==================================================================================================================================================================================
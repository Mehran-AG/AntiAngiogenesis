#include "EmptyCapillaryRemover.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

#include "PositionFinder.h"

#include <cmath>

#include <vector>

#include <iostream>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RemoveNodeVessel( cNode& );
// ==================================================================================================================================================================================

void EmptyCapillaryRemover() {

	//printf( "\nEmpty Remover Started" );

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::vector<int> sprouts;

	extern bool uncheckedVEGF[a_dim];

	extern bool available_spots[a_dim];

	extern int distance;

	// capillaries which are void of flow are removed from the network
	for ( size_t i = 0; i < vessels.size(); ++i ) {

		if ( ( !( abs( vessels[i].GetFlowRate() ) > 0 ) )  || ( abs( vessels[i].GetFlowRate() ) < 1E-18 ) ) {

			int s_node, e_node, s_place, e_place;

			s_place = vessels[i].GetPlaceOnStartingNode();

			e_place = vessels[i].GetPlaceOnEndingNode();

			s_node = PositionFinder( nodes, vessels[i].GetStartNode() );

			e_node = PositionFinder( nodes, vessels[i].GetEndNode() );

			nodes[s_node].RemoveOutletVessel( s_place );

			nodes[e_node].RemoveInletVessel( e_place );

			vessels.erase( vessels.begin() + i );

			--i;

		};

	};

	for ( size_t i = 0; i < nodes.size(); ) {

		if ( i == 0 ) {

			if ( nodes[i].GetNumberOfBranches() == 1 ) {

				RemoveNodeVessel( nodes[0] );

				int point = sprouts[0];

				for ( int counter = (point - distance); counter < (point + distance); ++counter ) {

					uncheckedVEGF[counter] = 1;

					available_spots[counter] = 0;

				};

				sprouts.erase( sprouts.begin() );

			}

			else
				++i;

		}

		else if ( i == ( sprouts.size() - 1 ) ) {

			if ( nodes[i].GetNumberOfBranches() == 1 ) {

				RemoveNodeVessel( nodes[sprouts.size()-1] );

				int point = sprouts[sprouts.size()-1];

				for ( int counter = (point - distance); counter < (point + distance); ++counter ) {

					uncheckedVEGF[counter] = 1;

					available_spots[counter] = 0;

				};

				sprouts.erase( sprouts.begin() + sprouts.size() - 1 );

				--i;

			}

			else
				++i;

		}

		else {

			if ( nodes[i].GetNumberOfBranches() == 0 ) {

				nodes.erase( nodes.begin() + i );

			}

			else
				++i;

		};

	};


	//printf( "\nEmpty Remover Ended" );

};
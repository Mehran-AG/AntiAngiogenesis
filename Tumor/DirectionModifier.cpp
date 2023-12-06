#include "DirectionModifier.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

#include "PositionFinder.h"

#include "ConcatenateVessels.h"

#include <vector>

#include <fstream>

#include <iostream>


void DirectionModifier() {

	//printf( "\nDir Modif Started" );

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::vector<int> sprouts;

	extern std::ofstream printer;

	for ( size_t v = 0; v < vessels.size(); ++v ) {

		if ( vessels[v].GetFlowRate() < 0 ) {

			int s_node_id, e_node_id, s_node_pos, e_node_pos, e_place, s_place;

			unsigned char temp[a_dim][a_dim] = {'\0'};

			for ( size_t i = 0; i < a_dim; ++i ) {
				for ( size_t j = 0; j < a_dim; ++j ) {

					temp[i][j] = vessels[v].path_storer[i][j];

					vessels[v].path_storer[i][j] = vessels[v].pre_path_storer[i][j];

					vessels[v].pre_path_storer[i][j] = temp[i][j];

				};

			};

			s_node_id = vessels[v].GetStartNode();

			e_node_id = vessels[v].GetEndNode();

			s_node_pos = PositionFinder( nodes, s_node_id );

			e_node_pos = PositionFinder( nodes, e_node_id );

			nodes[s_node_pos].RemoveOutletVessel( vessels[v].GetPlaceOnStartingNode() );

			e_place = nodes[s_node_pos].AssignInletVesselGetPlace( vessels[v].GetIDNumber() );

			nodes[e_node_pos].RemoveInletVessel( vessels[v].GetPlaceOnEndingNode() );

			s_place = nodes[e_node_pos].AssignOutletVesselGetPlace( vessels[v].GetIDNumber() );

			vessels[v].AssignEndingNode( s_node_id );

			vessels[v].AssignPlaceOnEndingNode( e_place );

			vessels[v].AssignStartingNode( e_node_id );

			vessels[v].AssignPlaceOnStartingNode( s_place );

			vessels[v].ChangeFlowDirection();

		};

	};


	//printf( "\nDir Modif Ended" );

};
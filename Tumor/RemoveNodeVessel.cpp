#include "RemoveNodeVessel.h"

#include "dimension.h"

#include "PositionFinder.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITION OF THE FUNCTION -------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RemoveNodeVessel( cNode& n ) {

	extern std::vector<cNode> nodes;

	extern std::vector<cVessel> vessels;

	if ( n.GetNumberOfInletVessels() == 1 ) {

		if ( n.GetInletVesselNumber( 1 ) >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vessels, n.GetInletVesselNumber( 1 ) );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			int s_node = vessels[vv].GetStartNode();

			int s_node_pos;

			try {

				s_node_pos = PositionFinder ( nodes, s_node );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes[s_node_pos].RemoveOutletVessel( vessels[vv].GetPlaceOnStartingNode() );

			vessels.erase( vessels.begin() + vv );

			int node_position;

			try {

				node_position = PositionFinder ( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes.erase ( nodes.begin() + node_position );

		}

		else if ( n.GetInletVesselNumber( 2 ) >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vessels, n.GetInletVesselNumber( 2 ) );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			int s_node = vessels[vv].GetStartNode();

			int s_node_pos;

			try {

				s_node_pos = PositionFinder ( nodes, s_node );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes[s_node_pos].RemoveOutletVessel( vessels[vv].GetPlaceOnStartingNode() );

			vessels.erase( vessels.begin() + vv );

			int node_position;

			try {

				node_position = PositionFinder ( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes.erase ( nodes.begin() + node_position );

		}

		else if ( n.GetInletVesselNumber( 3 ) >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vessels, n.GetInletVesselNumber( 3 ) );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			int s_node = vessels[vv].GetStartNode();

			int s_node_pos;

			try {

				s_node_pos = PositionFinder ( nodes, s_node );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes[s_node_pos].RemoveOutletVessel( vessels[vv].GetPlaceOnStartingNode() );

			vessels.erase( vessels.begin() + vv );

			int node_position;

			try {

				node_position = PositionFinder ( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes.erase ( nodes.begin() + node_position );

		};

	}

	else if ( n.GetNumberOfOutletVessels() == 1 ) {

		if ( n.GetOutletVesselNumber( 1 ) >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vessels, n.GetOutletVesselNumber( 1 ) );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			int e_node = vessels[vv].GetEndNode();

			int e_node_pos;

			try {

				e_node_pos = PositionFinder ( nodes, e_node );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes[e_node_pos].RemoveInletVessel( vessels[vv].GetPlaceOnEndingNode() );

			vessels.erase( vessels.begin() + vv );

			int node_position;

			try {

				node_position = PositionFinder ( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes.erase ( nodes.begin() + node_position );

		}

		else if ( n.GetOutletVesselNumber( 2 ) >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vessels, n.GetOutletVesselNumber( 2 ) );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			int e_node = vessels[vv].GetEndNode();

			int e_node_pos;

			try {

				e_node_pos = PositionFinder ( nodes, e_node );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes[e_node_pos].RemoveInletVessel( vessels[vv].GetPlaceOnEndingNode() );

			vessels.erase( vessels.begin() + vv );

			int node_position;

			try {

				node_position = PositionFinder ( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes.erase ( nodes.begin() + node_position );

		}

		else if ( n.GetOutletVesselNumber( 3 ) >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vessels, n.GetOutletVesselNumber( 2 ) );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			int e_node = vessels[vv].GetEndNode();

			int e_node_pos;

			try {

				e_node_pos = PositionFinder ( nodes, e_node );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes[e_node_pos].RemoveInletVessel( vessels[vv].GetPlaceOnEndingNode() );

			vessels.erase( vessels.begin() + vv );

			int node_position;

			try {

				node_position = PositionFinder ( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN NODES VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			nodes.erase ( nodes.begin() + node_position );

		};

	};

};
// ==================================================================================================================================================================================
#include "Brancher.h"

#include "dimension.h"

#include <fstream>

#include <iostream>

#include "cNode.h"

#include "PositionFinder.h"

#include "BranchTracker.h"

void Brancher( cVessel& v, int i, int j, char dir ) {

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::ofstream printer;

	int v_number = vessels[0].GetQuantity();

	cVessel new_vessel( v_number );

	cVessel new_branch( v_number+1 );

	new_vessel.SetOutletStatus( false );

	int n_number = nodes[0].GetQuantity();

	cNode new_node( n_number );

	new_node.SetXPosition( i );

	new_node.SetYPosition( j );

	new_vessel.SetStartingPoint( i, j );

	new_branch.SetStartingPoint( i, j );

	new_branch.StartVesselB( i, j, dir );

	BranchTracker( i, j, v, new_vessel );

	new_vessel.CopyEndNode( v );

	int enode = v.GetEndNode();

	int place = v.GetPlaceOnEndingNode();

	int position;

	try {

		position = PositionFinder( nodes, enode );

	}

	catch ( double ) {

		printf( "\nNO MATCHES IN THE NODE VECTOR IN TIP TO STALK ANASTOMOSIS\n" );

		system("pause");

	};

	nodes[position].ReplaceInletVessel( v_number, place );

	// specifying end node number for colliding capillary
	new_branch.AssignStartingNode( n_number );

	new_vessel.AssignStartingNode( n_number );

	v.AssignEndingNode( n_number );

	new_node.AssignInletsAndOutlets( v.GetIDNumber(), -1, v_number, v_number+1 );

	v.AssignPlaceOnEndingNode ( 1 );
	new_vessel.AssignPlaceOnStartingNode ( 1 );
	new_branch.AssignPlaceOnStartingNode ( 2 );

	// adding the ID numbers of stationary and migrating vessel in order not to have self anastomosis
	new_branch.AddToProhibiteds( v.GetIDNumber() );
	new_branch.AddToProhibiteds( v_number );

	printer << "VESSEL NO. " << v.GetIDNumber() << " SHEAR BRANCHED AND VESSELS " << v_number << " AND " << v_number+1 << " EMERGED" << std::endl;

	printf( "\nVESSEL NO. %u BRANCHED AND VESSELS %u AND %u EMERGED", v.GetIDNumber(), v_number, v_number+1 );

	printer << "NODE NO. IS " << n_number << std::endl;

	printf( "\nNODE NO. IS %u", n_number );

	vessels.push_back( new_vessel );

	vessels.push_back( new_branch );

	nodes.push_back( new_node );

};
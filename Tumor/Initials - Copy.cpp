#include "Initials.h"

#include "OutputWriter.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//HERE I SCHEMATICALLY DRAW THE INITIAL MAIN VESSEL AND SPROUTS AND NUMBERING PROCEDURE ---------------------------------------------------------------------------------------------
//
//               ^
//             1 |
//               |
//        NODE 1 |-> SPROUT 10
//               |
//             5 |
//               |
//        NODE 4 |-> SPROUT 9
//               |
//             4 |
//               |
//        NODE 3 |-> SPROUT 8
//               |
//             3 |
//               |
//        NODE 2 |-> SPROUT 7
//               |
//             2 |
//               |
//        NODE 0 |-> SPROUT 6
//               |
//             0 |
//               ^
//           MAIN VESSEL
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Initials() {

	printf("\nINITIALS STARTED");

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cVessel> vessels;

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( unsigned int i = 0; i != 11; i++ ) {

		cVessel v_i( i );

		vessels.push_back( v_i );

	};

	// initial location of Tip Endothelial Cells
	vessels[6].SetPath( 2, 33 );
	vessels[6].SetTipCellPosition( 2, 33 );

	vessels[7].SetPath( 2, 66 );
	vessels[7].SetTipCellPosition( 2, 66 );

	vessels[8].SetPath( 2, 99 );
	vessels[8].SetTipCellPosition( 2, 99 );

	vessels[9].SetPath( 2, 132 );
	vessels[9].SetTipCellPosition( 2, 132 );

	vessels[10].SetPath( 2, 165 );
	vessels[10].SetTipCellPosition( 2, 165 );

	// this step marks each root vessel with a number which will be passed to other child vessels
	vessels[6].branch_mark = 7;
	vessels[7].branch_mark = 8;
	vessels[8].branch_mark = 9;
	vessels[9].branch_mark = 10;
	vessels[10].branch_mark = 11;

	// initial unit lengths for existing sprouts
	vessels[2].SetVesselUnitLength( 33 );
	vessels[3].SetVesselUnitLength( 33 );
	vessels[4].SetVesselUnitLength( 33 );
	vessels[5].SetVesselUnitLength( 33 );
	vessels[6].SetVesselUnitLength( 0 );
	vessels[7].SetVesselUnitLength( 0 );
	vessels[8].SetVesselUnitLength( 0 );
	vessels[9].SetVesselUnitLength( 0 );
	vessels[10].SetVesselUnitLength( 0 );

	vessels[0].SetInletStatus( 0 );
	vessels[0].SetOutletStatus( 0 );
	vessels[1].SetInletStatus( 0 );
	vessels[1].SetOutletStatus( 0 );
	vessels[2].SetInletStatus( 0 );
	vessels[2].SetOutletStatus( 0 );
	vessels[3].SetInletStatus( 0 );
	vessels[3].SetOutletStatus( 0 );
	vessels[4].SetInletStatus( 0 );
	vessels[4].SetOutletStatus( 0 );
	vessels[5].SetInletStatus( 0 );
	vessels[5].SetOutletStatus( 0 );

	vessels[6].SetInletStatus( 0 );
	vessels[7].SetInletStatus( 0 );
	vessels[8].SetInletStatus( 0 );
	vessels[9].SetInletStatus( 0 );
	vessels[10].SetInletStatus( 0 );

	vessels[6].SetOutletStatus( 1 );
	vessels[7].SetOutletStatus( 1 );
	vessels[8].SetOutletStatus( 1 );
	vessels[9].SetOutletStatus( 1 );
	vessels[10].SetOutletStatus( 1 );

	// prescribe inlet & outlet vessels for each initial node

	extern std::vector<cNode> nodes;

	for ( unsigned int i = 0; i != 5; i++){

		cNode n_i( i );

		nodes.push_back( n_i );

	};

	nodes[0].AssignInletsAndOutlets( 0, -1, 2, 6 );

	nodes[1].AssignInletsAndOutlets( 5, -1, 1, 10 );

	nodes[2].AssignInletsAndOutlets( 2, -1, 3, 7 );

	nodes[3].AssignInletsAndOutlets( 3, -1, 4, 8 );

	nodes[4].AssignInletsAndOutlets( 4, -1, 5, 9 );

	// prescribe the start and end nodes for each capilary
	vessels[2].AssignStartingNode( 0 );
	vessels[2].AssignEndingNode( 2 );

	vessels[3].AssignStartingNode( 2 );
	vessels[3].AssignEndingNode( 3 );

	vessels[4].AssignStartingNode( 3 );
	vessels[4].AssignEndingNode( 4 );

	vessels[5].AssignStartingNode( 4 );
	vessels[5].AssignEndingNode( 1 );

	vessels[6].AssignStartingNode( 0 );

	vessels[7].AssignStartingNode( 2 );

	vessels[8].AssignStartingNode( 3 );

	vessels[9].AssignStartingNode( 4 );

	vessels[10].AssignStartingNode( 1 );

// INITIAL TAF AND FIBRONECTIN CONCENTRATIONA ---------------------------------------------------------------------------------------------------------------------------------------

	extern double c[201][201];
	extern double f[201][201];

	extern unsigned int nx, ny, x_d;

	double k = 0.75;

	double eps_1 = 0.45;

	double eps_2 = 0.45;

	extern double h;

	for ( unsigned int i = 0; i < nx; i++)
		for ( unsigned int j = 0; j < ny; j++) {

			c[i][j] = exp ( - 1 * ( pow (  ( 1 - ( i * h ) ), 2 ) ) / eps_1 );
			f[i][j] = k * exp ( -1 * ( pow ( (i * h), 2 ) / eps_2 ) );

		};

		printf("\nINTITALS ENDED");

};
// ==================================================================================================================================================================================
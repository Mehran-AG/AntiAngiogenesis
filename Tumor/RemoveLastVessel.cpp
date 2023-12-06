#include "RemoveLastVessel.h"

#include "dimension.h"

#include "PositionFinder.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITION OF THE FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void RemoveLastVessel( std::vector<cVessel>& vec, cNode& n, int node_number ) {

	extern std::vector<cNode> nodes;

	if ( n.inlets == 1 ) {

		if ( n.inlet1 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vec, n.inlet1 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			vec[vv].SetOutletStatus( 1 );

			n.inlet1 = -1;

			n.inlets --;

			nodes.erase ( nodes.begin() + node_number );

			VesselRemover( vec, vec[vv] );

		}

		else if ( n.inlet2 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vec, n.inlet2 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			vec[vv].SetOutletStatus( 1 );

			n.inlet2 = -1;

			n.inlets --;

			nodes.erase ( nodes.begin() + node_number );

			VesselRemover( vec, vec[vv] );

		}

		else if ( n.inlet3 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vec, n.inlet3 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			vec[vv].SetOutletStatus( 1 );

			n.inlet3 = -1;

			n.inlets --;

			nodes.erase ( nodes.begin() + node_number );

			VesselRemover( vec, vec[vv] );

		};

	}

	else if ( n.outlets == 1 ) {

		if ( n.outlet1 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vec, n.outlet1 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			vec[vv].SetInletStatus( 1 );

			nodes.erase ( nodes.begin() + node_number );

			VesselRemover( vec, vec[vv] );

		}

		else if ( n.outlet2 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vec, n.outlet2 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			vec[vv].SetInletStatus( 1 );

			nodes.erase ( nodes.begin() + node_number );

			VesselRemover( vec, vec[vv] );

		}

		else if ( n.outlet3 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( vec, n.outlet3 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN VESSEL REMOVER & REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			vec[vv].SetInletStatus( 1 );

			nodes.erase ( nodes.begin() + node_number );

			VesselRemover( vec, vec[vv] );

		};

	};

};
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function is only used in this file, so it is written here -------------------------------------------------------------------------------------------------------------------
// This file removes the last cVessel from node --------------------------------------------------------------------------------------------------------------------------------------
void RemoveLastVessel( std::vector<cVessel>& v, cNode& n ) {

	if ( n.inlets == 1 ) {

		if ( n.inlet1 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( v, n.inlet1 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN UNENDEDCAPILLARYREMOVER AND REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			v[vv].SetOutletStatus( 1 );

			n.inlet1 = -1;

			n.inlets --;

		}

		else if ( n.inlet2 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( v, n.inlet2 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN UNENDEDCAPILLARYREMOVER AND REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			v[vv].SetOutletStatus( 1 );

			n.inlet2 = -1;

			n.inlets --;

		}

		else if ( n.inlet3 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( v, n.inlet3 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN UNENDEDCAPILLARYREMOVER AND REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			v[vv].SetOutletStatus( 1 );

			n.inlet3 = -1;

			n.inlets --;

		};

	}

	else if ( n.outlets == 1 ) {

		if ( n.outlet1 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( v, n.outlet1 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN UNENDEDCAPILLARYREMOVER AND REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			v[vv].SetInletStatus( 1 );

		}

		else if ( n.outlet2 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( v, n.outlet2 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN UNENDEDCAPILLARYREMOVER AND REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			v[vv].SetInletStatus( 1 );

		}

		else if ( n.outlet3 >= 0 ) {

			int vv;

			try {

				vv = PositionFinder ( v, n.outlet3 );

			}

			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN UNENDEDCAPILLARYREMOVER AND REMOVELASTVESSEL AND NO. IS %d\n", wrong );

				system("pause");

			};

			v[vv].SetInletStatus( 1 );

		};

	};

};
// ==================================================================================================================================================================================
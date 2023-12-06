#include "cNode.h"

#include "dimension.h"

#include <iostream>

#include <fstream>

#pragma warning( disable: 4715 )

int cNode::quantity = 0;

cNode::cNode( int num ) {

	++quantity; // Quantity is the  number of created vessels, This number is used to assign an identity number to each vessel to have as its innate identity
				// this number is used when we want to call the vessel by number

	identity = num;

	inlets = 0;
	outlets = 0;
	inlet1 = -1;
	inlet2 = -1;
	inlet3 = -1;
	outlet1 = -1;
	outlet2 = -1;
	outlet3 = -1;

	p = 0.;

	branches = 0;

	x = 0;
	y = 0;

};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Gets one integer to determine the place of the vessel in the node, then returns the number based on the place---------------------------------------------------------------------
int cNode::GetInletVesselNumber( int n ) {

	switch ( n ) {

	case 1 :

		return inlet1;

		break;

	case 2 :

		return inlet2;

		break;

	case 3 :

		return inlet3;

		break;

	default:

		printf( "\nNO PLACE IN NODE MATCHED THE ENTERED PLACE\n" );

		system("pause");

	};

};
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Gets one integer to determine the place of the vessel in the node, then returns the identity number of vessel based on the place -------------------------------------------------
int cNode::GetOutletVesselNumber( int n ) {

	switch ( n ) {

	case 1 :

		return outlet1;

		break;

	case 2 :

		return outlet2;

		break;

	case 3 :

		return outlet3;

		break;

	default:

		printf( "\nNO PLACE IN NODE MATCHED THE ENTERED PLACE\n" );

		system("pause");

	};

};
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets identity number of inlet and outet vessels, the default is minus number to show that the inlet or outlet does not exist, then decides the number of inlets and outlets-------
// to the node and total number of branches
void cNode::AssignInletsAndOutlets( int i1 = -1, int i2 = -1, int o1 = -1, int o2 = -1 ) {

	int i_counter = 0;
	int o_counter = 0;

	if ( i1 >= 0 ) {

		++ i_counter;
		inlet1 = i1;

	};

	if ( i2 >= 0 ) {
		
		++ i_counter;
		inlet2 = i2;

	};

	if ( o1 >= 0 ) {
		
		++ o_counter;
		outlet1 = o1;

	};

	if ( o2 >= 0 ) {
		
		++ o_counter;
		outlet2 = o2;

	};

	inlets = i_counter;
	outlets = o_counter;

	branches = inlets + outlets;

};
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// geta pace of the inlet vessel and its identity number and assigns it to the node -------------------------------------------------------------------------------------------------
void cNode::AssignInletVessel( int pnum, int num ) {

	switch ( pnum ) {

	case 1 :

		inlet1 = num;

		++inlets;

		++branches;

		break;

	case 2 :

		inlet2 = num;

		++inlets;

		++branches;

		break;

	case 3 :

		inlet3 = num;

		++inlets;

		++branches;

	default:

		printf( "\nNO PLACE IN NODE MATCHED THE ENTERED PLACE" );

		printf( "\n" );
		system("pause");

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets an integer showing the place of the inlet vessel in the node and removes it -------------------------------------------------------------------------------------------------
int cNode::AssignInletVesselGetPlace( int identity ) {

	if ( inlet1 < 0 ) {

		inlet1 = identity;

		++inlets;

		++branches;

		return 1;

	}

	else if ( inlet2 < 0 ) {

		inlet2 = identity;

		++inlets;

		++branches;

		return 2;

	}

	else if ( inlet3 < 0 ) {

		inlet3 = identity;

		++inlets;

		++branches;

		return 3;

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets an integer showing the place of the inlet vessel in the node and removes it -------------------------------------------------------------------------------------------------
int cNode::AssignOutletVesselGetPlace( int identity ) {

	if ( outlet1 < 0 ) {

		outlet1 = identity;

		++outlets;

		++branches;

		return 1;

	}

	else if ( outlet2 < 0 ) {

		outlet2 = identity;

		++outlets;

		++branches;

		return 2;

	}

	else if ( outlet3 < 0 ) {

		outlet3 = identity;

		++outlets;

		++branches;

		return 3;

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets an integer showing the place of the inlet vessel in the node and removes it -------------------------------------------------------------------------------------------------
void cNode::RemoveInletVessel( int place ) {

	switch ( place ) {

	case 1 :

		inlet1 = -1;

		--inlets;

		--branches;

		break;

	case 2 :

		inlet2 = -1;

		--inlets;

		--branches;

		break;

	case 3 :

		inlet3 = -1;

		--inlets;

		--branches;

		break;

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets an integer showing the place of the outlet vessel in the node and removes it ------------------------------------------------------------------------------------------------
void cNode::RemoveOutletVessel( int place ) {

	switch ( place ) {

	case 1 :

		outlet1 = -1;

		--outlets;

		--branches;

		break;

	case 2 :

		outlet2 = -1;

		--outlets;

		--branches;

		break;

	case 3 :

		outlet3 = -1;

		--outlets;

		--branches;

		break;

	default:

		printf( "\nNO PLACE IN NODE MATCHED THE ENTERED PLACE\n" );

		system("pause");

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets an integer showing the place of the outlet vessel in the node and removes it ------------------------------------------------------------------------------------------------
void cNode::ReplaceInletVessel( int num, int place ) {

	switch ( place ) {

	case 1 :

		if ( inlet1 < 0 ) {

			printf( "\nYOU ARE REPLACING IN THE WRONG PLACE\n" );

			system("pause");

		};

		inlet1 = num;

		break;

	case 2 :

		if ( inlet2 < 0 ) {

			printf( "\nYOU ARE REPLACING IN THE WRONG PLACE\n" );

			system("pause");

		};

		inlet2 = num;

		break;

	case 3 :

		if ( inlet3 < 0 ) {

			printf( "\nYOU ARE REPLACING IN THE WRONG PLACE\n" );

			system("pause");

		};

		inlet3 = num;

		break;

	default:

		printf( "\nPLACE ID %d AND NO PLACE IN NODE MATCHED THE ENTERED PLACE\n", place );

		system("pause");

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// gets an integer showing the place of the outlet vessel in the node and removes it ------------------------------------------------------------------------------------------------
void cNode::ReplaceOutletVessel( int num, int place ) {

	switch ( place ) {

	case 1 :

		if ( outlet1 < 0 ) {

			printf( "\nYOU ARE REPLACING IN THE WRONG PLACE\n" );

			system("pause");

		};

		outlet1 = num;

		break;

	case 2 :

		if ( outlet2 < 0 ) {

			printf( "\nYOU ARE REPLACING IN THE WRONG PLACE\n" );

			system("pause");

		};

		outlet2 = num;

		break;

	case 3 :

		if ( outlet3 < 0 ) {

			printf( "\nYOU ARE REPLACING IN THE WRONG PLACE\n" );

			system("pause");

		};

		outlet3 = num;

		break;

	default:

		printf( "\nPLACE ID %d AND NO PLACE IN NODE MATCHED THE ENTERED PLACE\n", place );

		system("pause");

	};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// prints all the information of the node to the outsream that user defines ---------------------------------------------------------------------------------------------------------
void cNode::CopyNode( cNode& nd ) {

	this->p = nd.p;

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// prints all the information of the node to the outsream that user defines ---------------------------------------------------------------------------------------------------------
void cNode::Print( std::ofstream& writer ) {

	writer << "\nIdentity number of the node is " << identity << std::endl;

	writer << "Number of inlets to the node are " << inlets << std::endl;

	writer << "Number of outlets to the node are " << outlets << std::endl;

	writer << "Identity number of first inlet to the node is " << inlet1 << std::endl;

	writer << "Identity number of second inlet to the node is " << inlet2 << std::endl;

	writer << "Identity number of third inlet to the node is " << inlet3 << std::endl;

	writer << "Identity number of first outlet to the node is " << outlet1 << std::endl;

	writer << "Identity number of second outlet to the node is " << outlet2 << std::endl;

	writer << "Identity number of third outlet to the node is " << outlet3 << std::endl;

};
// ==================================================================================================================================================================================


// ***************************************************************************** FINISH *********************************************************************************************
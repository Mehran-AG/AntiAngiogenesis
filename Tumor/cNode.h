#pragma once

#include "cVessel.h"

#include <vector>

class cNode
{

//************************************************************ PUBLIC METHODS AND VARIABLES *****************************************************************************************

public:

// Constructor ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	cNode( int );

// ==================================================================================================================================================================================

// STATIC METHOD --------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int GetQuantity() { return quantity; };

// ==================================================================================================================================================================================

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// METHODS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int GetIDNumber() { return identity; }; // Returns the identity number of the node

	int GetNumberOfBranches() { return branches; }; // returns the number of branches that enters and leaves the node

	int GetInletVesselNumber( int ); // returns the identity number of inlet vessel to the node based on its place in the inlet vessels

	int GetOutletVesselNumber( int ); // returns the identity number of outlet vessel to the node based on its place in the inlet vessels

	int GetNumberOfInletVessels() { return inlets; }; // returns the number of inlet vessels to the node

	int GetNumberOfOutletVessels() { return outlets; }; // returns the number of outlet vessels to the node

	int GetXPosition() { return x; }; // returns X position of the node in the domain

	int GetYPosition() { return y; }; // returns Y position of the node in the domain

	double GetPressure() { return p; };

	void SetXPosition( int num ) { x = num; }; // sets X position of the node in the domain

	void SetYPosition( int num ) { y = num; }; // sets Y position of the node in the domain

	void SetPressure( double pre ) { p = pre; };

	void AssignInletsAndOutlets( int i1, int i2 , int o1, int o2 ); // assigns inlet and outlet vessels to the node

	void AssignInletVessel( int, int ); // gets two integers as place of vessel and its identity number and asigns it to the node

	int AssignInletVesselGetPlace( int ); // gets one integer as vessel identity number and assigns it to the node

	int AssignOutletVesselGetPlace( int ); // gets one integer as vessel identity number and assigns it to the node

	void RemoveInletVessel( int ); // gets an integer showing the place of the vessel and removes it from the node

	void RemoveOutletVessel( int ); // // gets an integer showing the place of the vessel and removes it from the node

	void RemoveAllBranches() { branches = 0; }; // removes all the inlet and outlet vessels to the node

	void RemoveLastVessel(); // removes the last vessel remained in the node after removing all the other vessels

	void ReplaceInletVessel( int, int );

	void ReplaceOutletVessel( int, int );


	void CopyNode( cNode& );


	void Print( std::ofstream& ); // prints all the information of the vessel to the out stream defined by the user

// ==================================================================================================================================================================================


//************************************************************ PRIVATE METHODS AND VARIABLES ****************************************************************************************

private:

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VARIABLES ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	static int quantity; // the number of all nodes created from the beginning of the process

	int identity; // the identity number of the node

	int inlets; // number of inlets to the node
	int outlets; // number of outlets to the node

	int inlet1; // identity number of inlet number 1
	int inlet2; // identity number of inlet number 2
	int inlet3; // identity number of inlet number 3
	int outlet1; // identity number of outlet number 1
	int outlet2; // identity number of outlet number 2
	int outlet3; // identity number of outlet number 3

	double p; // pressure in nodes

	int x, y; // position of the node in the domain by indices

	int branches; // total number of inlets and outlets to the node

// ==================================================================================================================================================================================

// FRIEND METHODS AND CLASSES -------------------------------------------------------------------------------------------------------------------------------------------------------

	friend void RemoveLastVessel( std::vector<cVessel>&, cNode& ); // this function removes the last vessel remained attached to the node

	friend void RemoveLastVessel( std::vector<cVessel>&, cNode&, int ); // overloading of the function to have node number

	friend void VesselRemover( std::vector<cVessel>&, cVessel& ); // removes the vessels

// ==================================================================================================================================================================================

};
#pragma once

#include "dimension.h"

#include <vector>

class cVessel
{

//************************************************************ PUBLIC METHODS AND VARIABLES *****************************************************************************************

public:

// CONSTRUCTOR(S) -------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	cVessel( int );

// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// STATIC METHOD(S) -----------------------------------------------------------------------------------------------------------------------------------------------------------------

	int GetQuantity() { return quantity; };

// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int GetIDNumber() { return identity; };

	int Get_X_CoordianteOfTEC() { return TEC_x; }; // returns X coordinate of Tip Endothelial Cell

	int Get_Y_CoordianteOfTEC() { return TEC_y; }; // returns Y coordinate of Tip Endothelial Cell

	bool GetPath ( int i, int j ) { return path[i][j]; }; // returns 1 if the vessel has sweeped that point

	int GetAge() { return age; }; // returns the age of the vessel

	int GetUnitLength() { return unit_length; }; // returns the number of steps moved by the vessel which is used to calculate the length of the vessel

	double GetLength() { return l; }; // returns the actual length of the vessel

	int GetMother() { return mother_vessel; }; // returns the mother vessel of the daughter vessel

	int GetStartNode() { return s_node; }; // returns starting node of the vessel

	int GetEndNode() { return e_node; }; // returns ending node of the vessel

	double GetVesselLength() { return l; }; // returns vessel length

	int GetPlaceOnStartingNode() { return place_on_s_node; }; // returns the vessel's place on the beginning part of the vessel

	int GetPlaceOnEndingNode() { return place_on_e_node; }; // returns the vessel's place on the finishing part of the vessel

	bool GetInletStatus() { return inlet_status; };

	bool GetOutletStatus() { return outlet_status; };

	unsigned char GetPathStorer( int i, int j ) { return path_storer[i][j]; }; // returns the direction which the vessel has moved from current point

	unsigned char GetPrePathStorer( int i, int j ) { return pre_path_storer[i][j]; }; // returns the direction which the vessel was before coming to the current point

	unsigned char GetProhibitedDirection() { return prohibited_direction; }; // returns the direction which the vessel is not allowed to move

	unsigned char GetForcedDirection() { return forced_direction; };  // returns the direction which the vessel is forced to move in order not to encounter its mother and daughter vessels

	double GetFlowRate() { return q; }; // returns blood flow rate in the capillary

	double GetHemaetocrit() { return hemaetocrit; };

	void ChangeFlowDirection() { q = -q; };

	double GetMuRel() { return mu_rel; };

	double GetC();

	double GetMu45() { return mu_45; };

	double GetMu() { return mu; };

	double GetResistance() { return r; };

	double GetDiameter() { return d; };

	double GetRadius() { return (d/2); };

	double GetDeltaR() { return delta_r; };

	double GetTotalStimulus() { return (s_wss + s_m + s_p ); };

	double GetWallShear() { return taw_w; };

	double GetNormShear() { return norm_shear; };

	int GetStartingI() { return x_st; };

	int GetStartingJ() { return y_st; };

	

	double GetPrln() { return prln; };

	void SetPrln( double );

	void AddToStationary() { stationary_time++; };

	int GetStationary() { return stationary_time; };

	void MakeStationaryZero() { stationary_time = 0; };



	void SetInletStatus( bool b ) { inlet_status = b; }; // sets the beginning status of the vessel which is open or not

	void SetOutletStatus( bool b ) { outlet_status = b; }; // sets the beginning status of the vessel which is open or not

	void SetVesselUnitLength( int l ) { unit_length = l; }; // sets the unit length of the vessel

	void SetMotherVessel( int v ) { mother_vessel = v; }; // defines the mother vessel of the daughter vessels in order to prevent their collision with it

	void SetPath( int i, int j ) { path[i][j] = 1; }; // sets the path of the vessel

	void SetTipCellPosition( int, int );

	void SetTipCellPosition( cVessel& );

	void SetLength( double );

	void SetPathStorer( int, int, unsigned char ); // defines the direction which the vessel will move from the current point

	void SetPrePathStorer( int, int, unsigned char ); // defines the direction which the vessel has moved to current position from that point

	void SetAge( int a ) { age = a; }; // defines age of the vessel

	void SetStartingPoint( int i, int j ) { x_st = i; y_st = j; }; // setting starting point of the vessel to use it in shear branching

	void SetFlowRate( double flow ) { q = flow; }; // assigns flow of the capillary

	void SetHemaetocrit( double h ) { hemaetocrit = h; };

	void SetDiameter( double diam ) { d = diam; };

	void SetMuRel(double );

	void SetC();

	void SetMu45();

	double HemaetocritFunction();

	void SetMu();

	void SetMuPlasma( double m ) { mu_plasma = m; };

	void SetResistance();

	void SetDeltaT( double t ) { dt = t; };

	void SetPressure( double pre ) { p = pre; };



	void MoveRight( int i, int j ); // moves the vessel right from the current position

	void MoveLeft( int i, int j ); // moves the vessel left from the current position

	void MoveUp( int i, int j ); // moves the vessel up from the current position

	void MoveDown( int i,int j ); // moves the vessel down from the current position

	void StartVessel( int, int, unsigned char ); // defines the starting point of the vessel from the position which is given

	void StartVessel( int, int ); // just starts the vessel from the defined position

	void StopGrowing( int, int ); // stops the vessel from growing and assigns 's' to the path storer in the defined point

	void StopGrowing(); // stops the vessel from growing



	void IncreaseAge() { ++age; }; // increases the age of the vessel

	void IncreaseLength() { ++unit_length; }; // increases unit length

	void DecreaseLength() { --unit_length; }; // decreases unit length
	


	void AssignStartingNode( int num ) { s_node = num; }; // assigns the node at starting part of the vessel

	void AssignEndingNode( int num ) { e_node = num; }; // assigns the node at the finishing part of the vessel

	void AssignPlaceOnStartingNode( int num ) { place_on_s_node = num; }; // assigns place of the vessel in the node at the starting part of the vessel

	void AssignPlaceOnEndingNode( int num ) { place_on_e_node = num; }; // assigns the place of the vessel at the finishing part of the vessel



	void CopyStartNode( cVessel& ); // copies starting node of the input vessel to its own

	void CopyEndNode( cVessel& ); // copies finishing node of the input vessel to its own

	void CopyGrowingStatus( cVessel& ); // copies the information of the input vessel to its own

	void SubtractLength( cVessel& );

	void ConcatenateVessels( cVessel& ); // concatenates segmented vessels to make them a single vessel

	void AddToProhibiteds( int );

	bool CheckNeighbors( int, int, std::vector<cVessel> );



	void SolveWallShearStressStimulus();

	void SolvePressureStimulus();

	void SolveMetabolicStimulus();

	void FindDeltaR();

	void NormalizeShear();

	void AddToOldDiameters( double );

	bool CompareToOldDiameters( double );

	void AddToOldMus( double );

	bool CompareToOldMus( double );

	double GetOld0() { return old_mu[0]; };

	double GetOld1() { return old_mu[1]; };

	double GetOld2() { return old_mu[2]; };

	double FindMu() { return ( mu_rel * mu_plasma ); };

	void StartVesselB( int, int, unsigned char ); // defines the starting point of the vessel from the position which is given in shear branching function

	void CopyVessel( cVessel& );


	void Print( std::ofstream& );

// ==================================================================================================================================================================================


//************************************************************ PRIVATE METHODS AND VARIABLES ****************************************************************************************

private:
	
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VARIABLES ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	static int quantity; // the number of all vessels created from the beginning of the process

	static double mu_plasma; // viscosity of plasma

	static double k_m; // constant characterizing the relative intensity of the metabolic stimulus

	static double k_p; // coefficient of pressure stimulus

	static double k_s; // represents the shrinking tendency of a vessel

	static double taw_ref; // refernce wall shear stress

	static double q_ref; // blood flow rate in parent vessel

	static double shear_ref; // reference shear rate

	static double dt;

	int identity; // the identity number of the vessel

	int unit_length; // the steps moved by a distinct capillary

	double l; // SetLength of each distinct capillary

	double old_d[3]; // previous diameter of the capillary

	double d; // diameter of each distinct capillary

	double r; // resistance of the capillary for flow equation

	double q; // volumetric flow rate of blood in each distinct capillary

	double e; // volumetric flow rate of erythrocyte in each distinct capillary

	double hemaetocrit; // hemaetocrit in blood vessels

	double mu_45; // mu(0.45) of flow inside the capillary which is dependent upon diameter

	double C; // Coefficient for finding mu_rel inside the capillary

	double mu_rel; // mu_rel of flow inside the capillary which is dependent upon diameter 

	double mu; // mu of flow inside the capillary which is dependent upon diameter

	double old_mu[3];

	int x_st; // starting point x coordinate

	int y_st; // starting point y coordinate

	int TEC_x; // X coordiante of Tip Endothelial Cell

	int TEC_y; // Y coordinate of Tip Endothelial Cell

	int s_node; // Starting node of each distinct capillary (It will be used when solving for blood flow since we have to know where each capillary has started)

	int e_node; // Finishing node of each distinct capillary

	int age; // Elapsed Time After Branching

	unsigned char prohibited_direction; // the direction which the vessel is not allowed to move

	unsigned char forced_direction; // the direction which the vessel is forced to move to prevent collision with mother and siblings

	int mother_vessel; // mother vessel of the vessel

	std::vector<int> prohibiteds; // vector of prohibited vessels which the vessel must not encounter

	bool path[a_dim][a_dim]; // all the traversed path of each distinct capillary

	unsigned char path_storer[a_dim][a_dim]; // the next direction where the vessel will move if it starts to move

	unsigned char pre_path_storer[a_dim][a_dim]; // the previous direction whrer the vessel was before moving to the current position

	int place_on_s_node; // place of the vessel on starting node

	int place_on_e_node; // place of the vessel on finishing node

	bool inlet_status; // the starting part of the vessel's status to see if it is open or closed

	bool outlet_status; // the finishing part of the vessel's status to see if it is open or closed

	double s_wss; // Wall Shear Stress stimulus of the capillary

	double taw_w; // shear on the wall

	double p; // intravascular pressure

	double taw_e; // shear induced by intravascular pressure

	double s_p; // pressure stimulus

	double s_m; // Metabolic Stimulus

	double delta_r; // the estimated modification to the vessel radius

	double norm_shear; // normalized shear stress based on (20 dyn/cm^2) reference shear stress


	double prln; // proliferation parameter of the vessel

	int stationary_time; // number of subsequent stationary conditions
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// FRIEND FUNCTIONS -----------------------------------------------------------------------------------------------------------------------------------------------------------------

	friend int GetMotherVesselPosition( std::vector<cVessel>&, cVessel&, int, int ); //this function checks to see if the mother vessel exists in the point or not
																											  // gets vector of vessels, mother vessel, the position to check if it exists in this position or not

	friend void BranchTracker ( int&, int&, cVessel&, cVessel& ); // this function trackes the vessel and assign the sweeped path to a new vessel
																				  // gets position to start, the old vessel and new vessel to store the information

	friend void BranchTracker( int, int, cVessel&, int& ); // this function sweeps the vessel and gets its length to see if it is long enough to segment it or not
																					// gets position to start and the vessel and also a variable to store the length sweeped	
	friend void BranchTracker( cVessel&, int&, int&, std::vector<int>&, int&, double& );
	
	friend void BranchTracker( cVessel&, int&, int&, int&, int& );

	friend void VesselRemover( std::vector<cVessel>&, cVessel& ); // this function removes the vessel from the vector and also removes it from the nodes it belongs
																// gets the vessel and the vector to remove it

	friend bool TipToStalkCollision ( cVessel& v1, cVessel& v2 ); // this function checks to see if tip to stalk cell collision has happened or not
																// checks to see if v2's tip cell has encountered v1's stalk cells

	friend void InletInletConcatenator( cVessel&, cVessel&, int, int, bool );

	friend void InletOutletConcatenator( cVessel&, cVessel&, int, int, bool );

	friend void OutletOutletConcatenator( cVessel&, cVessel&, int, int, bool );

	friend void ChangeProhibitedVessels( std::vector<cVessel>&, cVessel&, cVessel& );

	friend void RemoveFromMotherVessels( std::vector<cVessel>&, cVessel& );

	friend void AddToProhibitedVessels( std::vector<cVessel>&, cVessel&, cVessel& );

	friend void HemaetocritSolver();

	friend void DirectionModifier();

// ==================================================================================================================================================================================

};
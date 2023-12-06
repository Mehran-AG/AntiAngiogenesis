#include "MigrationOfImmatureVessel.h"

#include "cVessel.h"

#include "RangeCalculator.h"

#include "TipToTipAnastomosis.h"

#include "TipToStalkAnastomosis.h"

#include "GetMotherVesselPosition.h"

#include "MovementPreventer.h"

#include "ForceMovementDirection.h"

#include "ECProliferation.h"

#include <vector>

#include <iostream>

#include <cstdlib>

#include <conio.h>

#include <fstream>

#include "dimension.h"


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MigrationOfImmatureVessel( size_t& migrating_vessel_num ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	int stopper = 8;

	int kk, ll;

	extern int x_d, y_d;

	extern std::vector<cVessel> vessels;

	extern double p_0[a_dim][a_dim], p_1[a_dim][a_dim], p_2[a_dim][a_dim], p_3[a_dim][a_dim], p_4[a_dim][a_dim];

	extern double r_0_l[a_dim][a_dim], r_0_u[a_dim][a_dim], r_1_l[a_dim][a_dim], r_1_u[a_dim][a_dim], r_2_l[a_dim][a_dim], r_2_u[a_dim][a_dim], r_3_l[a_dim][a_dim], r_3_u[a_dim][a_dim], r_4_l[a_dim][a_dim], r_4_u[a_dim][a_dim];


	extern int stationaries;

	extern int rights;

	extern int lefts;

	extern int ups;

	extern int downs;


// ---------------------------------------------------------------------------------------------------------------------------------------
// Movement of Vessel Inside the Domain
// ---------------------------------------------------------------------------------------------------------------------------------------

	// assigning new name for the migrating vessel
	cVessel& migrating_vessel = vessels[migrating_vessel_num];

	// Getting the x & y Position of Tip Endothelial Cell
	int i = migrating_vessel.Get_X_CoordianteOfTEC();

	int j = migrating_vessel.Get_Y_CoordianteOfTEC();

	// When a daughter vessel has emerged, we have to prevent it from encountering its sibling, so we don't let the vessel to move toward its sibling
	MovementPreventer( i, j,  migrating_vessel.GetProhibitedDirection() );
	
	double r_num_m = (double) rand() / RAND_MAX;

	// Now it is checked to see in which limit the generated random number falls to decide the direction of movement
	if ( ( r_0_l[i][j] <= r_num_m ) && ( r_num_m <= r_0_u[i][j] ) ) {

		printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

		stationaries++;

		migrating_vessel.IncreaseAge();

	}

	else if ( ( r_1_l[i][j] < r_num_m ) && ( r_num_m <= r_1_u[i][j] ) ) {

		if ( ( migrating_vessel.GetPath( i+1, j ) == 1 ) || ( migrating_vessel.CheckNeighbors( i+1, j, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) {

			printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

			stationaries++;

			migrating_vessel.IncreaseAge();

		}
        
		else {

			printf ("\nEC NUMBER, %d, MOVED RIGHT", migrating_vessel.GetIDNumber() );

			rights++;

			migrating_vessel.MoveRight( i, j );
    
			kk = i + 1;
			ll = j;
    
			bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
			if (a_indicator == false) 
				a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
		};

	}

	else if ( ( r_2_l[i][j] < r_num_m ) && ( r_num_m <= r_2_u[i][j] ) ) {

		if ( ( migrating_vessel.GetPath( i-1, j ) == 1 ) || ( migrating_vessel.CheckNeighbors( i-1, j, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) {
         
			printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

			stationaries++;

			migrating_vessel.IncreaseAge();

		}
        
		else {

			printf ("\nEC NUMBER, %d, MOVED LEFT", migrating_vessel.GetIDNumber() );

			lefts++;

			migrating_vessel.MoveLeft( i, j );
    
			kk = i - 1;
			ll = j;
    
			bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
			if (a_indicator == false) 
				a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
			};

		}

	else if ( ( r_3_l[i][j] < r_num_m ) && ( r_num_m <= r_3_u[i][j] ) ) {

		if ( ( migrating_vessel.GetPath( i, j+1 ) == 1 ) || ( migrating_vessel.CheckNeighbors( i, j+1, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) {
         
			printf ( "\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

			stationaries++;

			migrating_vessel.IncreaseAge();

			}
        
		else {

			printf ( "\nEC NUMBER, %d, MOVED UP", migrating_vessel.GetIDNumber() );

			ups++;

			migrating_vessel.MoveUp( i, j );
    
			kk = i;
			ll = j + 1;
    
			bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
			if (a_indicator == false) 
				a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
		};

	}

	else if ( ( r_4_l[i][j] < r_num_m ) && ( r_num_m <= r_4_u[i][j] ) ) {

		if ( ( migrating_vessel.GetPath( i, j-1 ) == 1 ) || ( migrating_vessel.CheckNeighbors( i, j-1, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) {
        
			printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

			stationaries++;

			migrating_vessel.IncreaseAge();

		}
        
		else {

			printf ( "\nEC NUMBER, %d, MOVED DOWN", migrating_vessel.GetIDNumber() );

			downs++;

			migrating_vessel.MoveDown( i, j );
    
			kk = i;
			ll = j - 1;
    
			bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
			if (a_indicator == false) 
				a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
		};

	};

};
// ==================================================================================================================================================================================
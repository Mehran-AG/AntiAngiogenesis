#include "MigrationOfMatureVessel.h"

#include "cVessel.h"

#include "RangeCalculator.h"

#include "TipToTipAnastomosis.h"

#include "TipToStalkAnastomosis.h"

#include "GetMotherVesselPosition.h"

#include "ECProliferation.h"

#include <vector>

#include <iostream>

#include <cstdlib>

#include <conio.h>

#include <fstream>

#include "dimension.h"


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MigrationOfMatureVessel( size_t& migrating_vessel_num ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	int kk, ll;

	extern int x_d, y_d;

	extern double r_0_l[a_dim][a_dim], r_0_u[a_dim][a_dim], r_1_l[a_dim][a_dim], r_1_u[a_dim][a_dim], r_2_l[a_dim][a_dim], r_2_u[a_dim][a_dim], r_3_l[a_dim][a_dim], r_3_u[a_dim][a_dim], r_4_l[a_dim][a_dim], r_4_u[a_dim][a_dim];

	extern std::vector<cVessel> vessels;


	extern int stationaries;

	extern int rights;

	extern int lefts;

	extern int ups;

	extern int downs;


// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// assigning new name for the migrating vessel to prevent writing vessels vector each time
	cVessel& migrating_vessel = vessels[migrating_vessel_num];

	// Setting i & j to Tip Endothelial Cell's position
	int i = migrating_vessel.Get_X_CoordianteOfTEC();

	int j = migrating_vessel.Get_Y_CoordianteOfTEC();

	// A random number between 0 and 1 is generated to decide the direction of movement
	double r_num_m = (double) rand() / RAND_MAX;

	if ( ( r_0_l[i][j] <= r_num_m ) && ( r_num_m <= r_0_u[i][j] ) ) { // if2

		printf ( "\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

		stationaries++;

		migrating_vessel.IncreaseAge();

	} // if2

	else if ( ( r_1_l[i][j] < r_num_m ) && ( r_num_m <= r_1_u[i][j] ) ) { // if2

		if ( ( migrating_vessel.GetPath( i+1, j ) == 1 ) || ( migrating_vessel.CheckNeighbors( i+1, j, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) {// if3

			printf ( "\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

			stationaries++;

			migrating_vessel.IncreaseAge();

		} // if3
        
		else { // if3

			printf ( "\nEC NUMBER, %d, MOVED RIGHT", migrating_vessel.GetIDNumber() );

			rights++;

			migrating_vessel.MoveRight( i,j );
    
			kk = i + 1;
			ll = j;
    
			bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
			
			if (a_indicator == false) 
				a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
			}; // if3

		} // if2

		else if ( ( r_2_l[i][j] < r_num_m ) && ( r_num_m <= r_2_u[i][j] ) ) { // if2

			if ( ( migrating_vessel.GetPath( i-1, j ) == 1 ) || ( migrating_vessel.CheckNeighbors( i-1, j, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) { // if4
				
				printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

				stationaries++;

				migrating_vessel.IncreaseAge();

			} // if4
        
			else { // if4

				printf ("\nEC NUMBER, %d, MOVED LEFT", migrating_vessel.GetIDNumber() );

				lefts++;
    
				migrating_vessel.MoveLeft(i, j);

				kk = i - 1;
				ll = j;
    
				bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
				if (a_indicator == false) 
					a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
			}; // if4

		} // if2

		else if ( ( r_3_l[i][j] < r_num_m ) && ( r_num_m <= r_3_u[i][j] ) ) { // if2

			if ( ( migrating_vessel.GetPath( i, j+1 ) == 1 ) || ( migrating_vessel.CheckNeighbors( i, j+1, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) { // if5

				printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

				stationaries++;

				migrating_vessel.IncreaseAge();

			} // if5
        
			else { // if5

				printf ("\nEC NUMBER, %d, MOVED UP", migrating_vessel.GetIDNumber() );

				ups++;
    
				migrating_vessel.MoveUp(i, j);

				kk = i;
				ll = j + 1;
    
				bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
				if (a_indicator == false) 
					a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
			}; // if5

		} // if2

		else if ( ( r_4_l[i][j] < r_num_m ) && ( r_num_m <= r_4_u[i][j] ) ) { // if2

			if ( ( migrating_vessel.GetPath( i, j-1 ) == 1 ) || ( migrating_vessel.CheckNeighbors( i, j-1, vessels ) ) || ( ECProliferation( i, j, migrating_vessel ) ) ) { // if6

				printf ("\nEC NUMBER, %d, STAYED STATIONARY", migrating_vessel.GetIDNumber() );

				stationaries++;

				migrating_vessel.IncreaseAge();

			} // if6
        
			else { // if6

				printf ("\nEC NUMBER, %d, MOVED DOWN", migrating_vessel.GetIDNumber() );

				downs++;
    
				migrating_vessel.MoveDown(i, j);

				kk = i;
				ll = j - 1;
    
				bool a_indicator = TipToTipAnastomosis( kk, ll, migrating_vessel_num );
    
				if (a_indicator == false) 
					a_indicator = TipToStalkAnastomosis( kk, ll, migrating_vessel_num );
   
			}; // if6

		}; // if2


};
// ==================================================================================================================================================================================
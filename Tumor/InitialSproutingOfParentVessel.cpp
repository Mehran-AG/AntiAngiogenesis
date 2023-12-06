#include "InitialSproutingOfParentVessel.h"

#include "dimension.h"

#include <cstdlib>

#include <vector>

#include <iostream>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION REMOVES DEFINED NUMBER OF NEARBY POINTS AROUND A NEWLY EMERGED POINT THAT MUST BE REMOVED WHEN A NEW SPORUT EMERGES IN A POINT -------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ClearSurrounding( int, int, bool*, bool*  );
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS STRUCTURE STORES THE POINTS WHICH ARE NOMINIZED FOR SPROUTING, BUT AS PROBABILITY OF THE SPROUTING NEEDS TO DETERMINE THE NEW SPROUT FORMATION, IT MUST KEEP THE PROBABILITY
// FOR THE POINT, SO IF THE PRBABILITY IS NOT SATISFIED, IT WILL BE EXCLUDED FROM THE POINTS ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct points {

	int i;

	double p;

};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION RANDOMLY DEFINES THE LOCATION OF SPROUTS ON PARENT VESSEL ----------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InitialSproutingOfParentVessel() {

	extern double dt;

	extern double k_p;

	extern double l_seg;

	extern double dim_t;

	extern double c_th;

	extern double c_th_50;

	extern double c_ref;

	extern double c[a_dim][a_dim];

	double cd[a_dim]; // dimensional VEGF concentration

	extern std::vector<int> sprouts;

	extern int ny;

	extern bool uncheckedVEGF[a_dim];

	extern bool available_spots[a_dim];

	extern int distance;

	int first = distance;

	int last = ny - distance;

	extern double coef;

	// since concentration of VEGF was normalized, here it will be denormalized with the reference value of concentration for normalization of the gradient
	for ( int i = 0; i < ny; ++i ) {

		cd[i] = c[1][i] * c_ref * coef; // 1500 is added to obey the rules imposed by the paper, I added it heuristically

	};


	// concentration in different points are checked to see if the points are eligible for sprouting or not based on the threshold value
	for( int i = first; i < last; ++i ) {

		if ( cd[i] > c_th ) {

			uncheckedVEGF[i] = 0;

			available_spots[i] = 1;

		};

	};

	// a vector is defined to store the spots (points) which are nominized, because I want to generate a random number based on the number of spots to choose them randomly
	std::vector<points> spots;

	for( int i = first; i < last; ++i ) {

		if ( available_spots[i] != 0 ) {

			points new_p;

			new_p.i = i;

			new_p.p = k_p * l_seg * dt * dim_t * ( ( cd[i] - c_th ) / ( cd[i] - c_th + c_th_50 ) );

			spots.push_back(new_p);

		};

	};

	while ( spots.size() ) {

		int sprouted = 0;

		while ( !sprouted ) { // this loop will iterate until the value for sprouted which shows the y coordiante of sprout is not equal to zero

			int r_num = rand() % spots.size();

			double r_num_p = (double) rand() / RAND_MAX;

			if ( r_num_p <= spots[r_num].p ) {

				sprouted = spots[r_num].i;

				sprouts.push_back( sprouted );

			};

		};


		// after a sprout emerges, its surrounding must be cleaned in case there are any other nominated spots
		ClearSurrounding( sprouted, distance, available_spots, uncheckedVEGF );

		// Then the vector of nominated points are cleared to start filling it again in case some spots are removed due to emergence of a nearby sprout
		spots.clear();

		// the spots vector is filled with nominated points to start the loop again
		for( int i = first; i < last; ++i ) {

			if ( available_spots[i] != 0 ) {

				points new_p;

				new_p.i = i;

				new_p.p = k_p * l_seg * dt * dim_t * ( ( cd[i] - c_th ) / ( cd[i] - c_th + c_th_50 ) );

				spots.push_back(new_p);

			};

		};
	};

	std::cout << "NO. OF SPROUTS ARE: " << sprouts.size() << std::endl;

	// When the sprouts vector is defined, it should be sorted from the lowest value starting the vector to the highest value at the end of the vector
	for( size_t i = 0; i < sprouts.size(); ++i ) {

		for( size_t j = i+1; j < sprouts.size(); ++j ) {

			if ( sprouts[i] > sprouts[j] ) {

				int temp = sprouts[i];
				sprouts[i] = sprouts[j];
				sprouts[j] = temp;

			};

		};	

	};

};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITION OF FUNCTION -----------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ClearSurrounding( int sprout, int distance, bool* a, bool* b ) {

	int lower = sprout - distance;

	int upper = sprout + distance;

	for ( int i = lower; i < upper; ++i ) {

		a[i] = 0;

		b[i] = 0;

	};

};
// ==================================================================================================================================================================================
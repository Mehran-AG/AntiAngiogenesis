#include "BranchTracker.h"

#include "dimension.h"

#include <vector>

#include <iostream>

#include <conio.h>

#pragma warning( disable: 4129 )

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function traverses the vessel which is going to be segmented and puts the data related to segmented part to a new vessel class ----------------------------------------------
void BranchTracker( int& i, int& j, cVessel& existing, cVessel& new_segment ) {

	char path = existing.path_storer[i][j];

	// If the vessel has ended, we can distinguish it by checking whether it has STOP (=s) in its Path_Storer or
	// its Tip Cell Position is the same as i and j that we are now

	if ( ( path == 's' ) || ( ( existing.TEC_x == i ) && ( existing.TEC_y == j ) ) ) {

		existing.path[i][j] = 0;
		new_segment.path[i][j] = 1;

		new_segment.path_storer[i][j] = 's';
		new_segment.pre_path_storer[i][j] = existing.pre_path_storer[i][j];

		existing.pre_path_storer[i][j] = '\0';
		existing.path_storer[i][j] = '\0';

		goto end;

	}

	else {

		switch ( path ) {
		
		case 'r' :

			// If for the first time we enter here, so we are in the segment point of new vessel and existing one
			// Therefore, we have to STOP both of them in their path storers, one in path storer and the other in pre path storer
			if ( new_segment.GetUnitLength() == 0 ) {

				new_segment.path_storer[i][j] = 'r';
				new_segment.pre_path_storer[i][j] = 's';
				existing.path_storer[i][j] = 's';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 1;
			
				// as brachtracker moves, a uint mustbe added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				++i;

			}

			else {

				new_segment.path_storer[i][j] = 'r'; // assign the path for the new vessel
				existing.path_storer[i][j] = '\0'; // make path storer of the sweeped vessel NULL
				new_segment.pre_path_storer[i][j] = existing.pre_path_storer[i][j];
				existing.pre_path_storer[i][j] = '\0';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 0;
			
				// as brachtracker moves, a uint mustbe added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				++i;

			};
			
			BranchTracker( i, j, existing, new_segment );

			break;

		case 'l' :
			
			if ( new_segment.GetUnitLength() == 0 ) {

				new_segment.path_storer[i][j] = 'l';
				new_segment.pre_path_storer[i][j] = 's';
				existing.path_storer[i][j] = 's';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 1;
			
				// as brachtracker moves, a uint mustbe added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				--i;

			}

			else {

				new_segment.path_storer[i][j] = 'l';
				existing.path_storer[i][j] = '\0';
				new_segment.pre_path_storer[i][j] = existing.pre_path_storer[i][j];
				existing.pre_path_storer[i][j] = '\0';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 0;
			
				// as brachtracker moves, a uint mustbe added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				--i;

			};
			
			BranchTracker( i, j, existing, new_segment );

			break;

		case 'u' :
			
			if ( new_segment.GetUnitLength() == 0 ) {

				new_segment.path_storer[i][j] = 'u';
				new_segment.pre_path_storer[i][j] = 's';
				existing.path_storer[i][j] = 's';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 1;
			
				// as brachtracker moves, a uint mustbe added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				++j;

			}

			else {

				new_segment.path_storer[i][j] = 'u';
				existing.path_storer[i][j] = '\0';
				new_segment.pre_path_storer[i][j] = existing.pre_path_storer[i][j];
				existing.pre_path_storer[i][j] = '\0';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 0;
			
				// as brachtracker moves, a uint mustbe added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				++j;

			};
			
			BranchTracker( i, j, existing, new_segment );

			break;

		case 'd' :
			
			if ( new_segment.GetUnitLength() == 0 ) {

				new_segment.path_storer[i][j] = 'd';
				new_segment.pre_path_storer[i][j] = 's';
				existing.path_storer[i][j] = 's';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 1;
			
				// as brach_tracker moves, a uint must be added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				--j;

			}

			else {

				new_segment.path_storer[i][j] = 'd';
				existing.path_storer[i][j] = '\0';
				new_segment.pre_path_storer[i][j] = existing.pre_path_storer[i][j];
				existing.pre_path_storer[i][j] = '\0';

				new_segment.path[i][j] = 1;
				existing.path[i][j] = 0;
			
				// as brach_tracker moves, a uint must be added to unit length
				new_segment.IncreaseLength();

				existing.DecreaseLength();

				--j;

			};
			
			BranchTracker( i, j, existing, new_segment );

			break;

		default:

			printf( "\nOOPS\! NONE OF THE DIRECTIONS MATCHES THE PATH\n" );

			system("pause");

		};

	};

end:;

};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function is used to just find the length of new_segment of the segmented capillary to check for the required length
// If the length of the segmented capillaries are below a size, they must be deleted
void BranchTracker( int i, int j, cVessel& v, int& unit_length_tracked ) {

	char path = v.path_storer[i][j];

	if ( ( path == 's' ) || ( ( v.TEC_x == i ) && ( v.TEC_y == j ) ) ) {

		goto end;

	}

	else {

		switch ( path ) {
			
		case 'r' :

			// as brachtracker moves, a uint mustbe added to unit length
			++unit_length_tracked;

			++i;
			
			BranchTracker( i, j, v, unit_length_tracked );

			break;

		case 'l' :
			
			// as brachtracker moves, a uint mustbe added to unit length
			++unit_length_tracked;

			--i;
			
			BranchTracker( i, j, v, unit_length_tracked );

			break;

		case 'u' :
			
			// as brachtracker moves, a uint mustbe added to unit length
			++unit_length_tracked;

			++j;
			
			BranchTracker( i, j, v, unit_length_tracked );

			break;

		case 'd' :
			
			// as brach_tracker moves, a uint must be added to unit length
			++unit_length_tracked;

			--j;
			
			BranchTracker( i, j, v, unit_length_tracked );

			break;

		default:

			printf( "\nOOPS\! NONE OF THE DIRECTIONS MATCHES THE PATH" );

			printf( "\n" );
			system("pause");

		};

	};

end:;

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This function traverses the vessel which is going to be segmented and puts the spots susceptible for branching in a vector -------------------------------------------------------
void BranchTracker( cVessel& v, int& i, int& j, std::vector<int>& vec, int& counter, double& criterion ) {

	extern double c[a_dim][a_dim];

	char path = v.path_storer[i][j];

	// If the vessel has ended, we can distinguish it by checking whether it has STOP (=s) in its Path_Storer or
	// its Tip Cell Position is the same as i and j that we are now

	if ( path == 's' ) {

		goto end;

	}

	else {

		switch ( path ) {
		
		case 'r' :

			++counter;

			// If for the first time we enter here, so we are in the segment point of new vessel and existing one
			// Therefore, we have to STOP both of them in their path storers, one in path storer and the other in pre path storer
			if ( ( counter > 3 ) && ( counter < ( v.unit_length - 3 ) ) ) {

				if ( c[i][j] >= criterion )
					vec.push_back( counter );

			};

			++i;
			
			BranchTracker( v, i, j, vec, counter, criterion );

			break;

		case 'l' :
			
			++counter;

			if ( ( counter > 3 ) && ( counter < ( v.unit_length - 3 ) ) ) {

				if ( c[i][j] >= criterion )
					vec.push_back( counter );

			};

			--i;
			
			BranchTracker( v, i, j, vec, counter, criterion );

			break;

		case 'u' :
			
			++counter;

			if ( ( counter > 3 ) && ( counter < ( v.unit_length - 3 ) ) ) {

				if ( c[i][j] >= criterion )
					vec.push_back( counter );

			};

			++j;
			
			BranchTracker( v, i, j, vec, counter, criterion );

			break;

		case 'd' :
			
			++counter;

			if ( ( counter > 3 ) && ( counter < ( v.unit_length - 3 ) ) ) {

				if ( c[i][j] >= criterion )
					vec.push_back( counter );

			};

			--j;
			
			BranchTracker( v, i, j, vec, counter, criterion );

			break;

		default:

			printf( "\nOOPS\! NONE OF THE DIRECTIONS MATCHES THE PATH\n" );

			system("pause");

		};

	};

end:;

};
// ==================================================================================================================================================================================



void BranchTracker( cVessel& v, int& i, int& j, int& fnl, int& counter ) {

	char path = v.path_storer[i][j];

	// If the vessel has ended, we can distinguish it by checking whether it has STOP (=s) in its Path_Storer or
	// its Tip Cell Position is the same as i and j that we are now

	if ( counter >= fnl ) {

		goto end;

	}

	else {

		switch ( path ) {
		
		case 'r' :

			++counter;

			++i;
			
			BranchTracker( v, i, j, fnl, counter );

			break;

		case 'l' :
			
			++counter;

			--i;
			
			BranchTracker( v, i, j, fnl, counter );

			break;

		case 'u' :
			
			++counter;

			++j;
			
			BranchTracker( v, i, j, fnl, counter );

			break;

		case 'd' :
			
			++counter;

			--j;
			
			BranchTracker( v, i, j, fnl, counter );

			break;

		default:

			printf( "\nOOPS\! NONE OF THE DIRECTIONS MATCHES THE PATH\n" );

			system("pause");

		};

	};

end:;

};
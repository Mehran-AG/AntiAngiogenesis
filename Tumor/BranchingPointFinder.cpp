#include "BranchingPointFinder.h"

#include "dimension.h"

#include "BranchTracker.h"

char BranchingPointFinder( std::vector<cVessel>& vec, cVessel& v, int pnt, int& i, int& j ) {

	int counter = 0;

	BranchTracker( v, i, j, pnt, counter );

	char flag = 'r';

	for ( size_t count = 0; count < vec.size(); ++count ) {

		if ( vec[count].GetPath( i+1, j ) )
			flag = '\0';

	};

	if ( flag == '\0' ) {

		if ( j < 101 ) {

			flag = 'u';

			for ( size_t count = 0; count < vec.size(); ++count ) {

				if ( vec[count].GetPath( i, j+1 ) )
					flag = '\0';

			};

			if ( flag == '\0' ) {

				flag = 'd';

				for ( size_t count = 0; count < vec.size(); ++count ) {

					if ( vec[count].GetPath( i, j-1 ) )
						flag = '\0';

				};

			};

		}

		else {

			flag = 'd';

			for ( size_t count = 0; count < vec.size(); ++count ) {

				if ( vec[count].GetPath( i, j-1 ) )
					flag = '\0';

			};

			if ( flag == '\0' ) {

				flag = 'u';

				for ( size_t count = 0; count < vec.size(); ++count ) {

					if ( vec[count].GetPath( i, j+1 ) )
						flag = '\0';

				};

			};

		};

	};

	return flag;

};
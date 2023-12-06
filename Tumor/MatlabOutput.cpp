#include "MatlabOutput.h"

#include "dimension.h"

#include "cVessel.h"

#include "PositionFinder.h"

#include <vector>

#include <string>

#include <direct.h>

using std::string;

void MatlabOutput() {

	extern std::vector<cVessel> vessels;

	extern double c[a_dim][a_dim];

	extern double f[a_dim][a_dim];

	extern double hemaetocrit[a_dim][a_dim];

	extern int nx, ny;

	extern double h;

	int final_path[a_dim][a_dim] = {0};

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( int k = 0; k != vessels.size(); k++ ) {

		for ( int i = 0; i != nx; i++ )
			for ( int j = 0; j != ny; j++ ) {

				final_path[i][j] = final_path[i][j] + vessels[k].GetPath( i, j );

			};

	};

	for ( int i = 0; i != nx; i++ )
		for ( int j = 0; j != ny; j++ ) {

			if ( final_path[i][j] > 1 )
				final_path[i][j] = 1;

		};



	extern char dir[100];

	FILE *xfile;

	char xtempdir[100];

	strcpy( xtempdir, dir );

	strcat( xtempdir, "\\X.dat" );

	xfile = fopen ( xtempdir, "w" );

	if (!xfile) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	for( size_t i = 0; i < a_dim; ++i ) {

		for( size_t j = 0; j < a_dim; ++j ) {

			fprintf( xfile, "%4u", i );

		};

		fprintf( xfile, "\n" );

	};


	FILE *yfile;

	char ytempdir[100];

	strcpy( ytempdir, dir );

	strcat( ytempdir, "\\Y.dat" );

	yfile = fopen ( ytempdir, "w" );

	if (!yfile) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	for( size_t i = 0; i < a_dim; ++i ) {

		for( size_t j = 0; j < a_dim; ++j ) {

			fprintf( yfile, "%4u", j );

		};

		fprintf( yfile, "\n" );

	};


	FILE *vfile;

	char vtempdir[100];

	strcpy( vtempdir, dir );

	strcat( vtempdir, "\\TEC.dat" );

	vfile = fopen ( vtempdir, "w" );

	if (!vfile) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	for( size_t i = 0; i < a_dim; ++i ) {

		for( size_t j = 0; j < a_dim; ++j ) {

			fprintf( vfile, "%3u", final_path[i][j] );

		};

		fprintf( vfile, "\n" );

	};

};
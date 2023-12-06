#include "OutputWriter.h"

#include "dimension.h"

#include "cVessel.h"

#include "PositionFinder.h"

#include <vector>

#include <string>

#include <direct.h>


using std::string;


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void OutputWriter() {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cVessel> vessels;

	extern double c[a_dim][a_dim];

	extern double f[a_dim][a_dim];

	extern double e[a_dim][a_dim];

	extern double hemaetocrit[a_dim][a_dim];

	extern int nx, ny;

	extern double h;

	int final_path[a_dim][a_dim] = {0};

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	FILE *file;

	string header = "TITLE=\"TUMOR&CAPILLARY NETWORK\"";

	string variables = "VARIABLES= \"X (mm)\", \"Y (mm)\", \"VEGF\", \"FIBRONECTIN\", \"ENDOSTATIN\", \"TEC\", \"HEMAETOCRIT\"";

	char zone1[200] = "ZONE T=\"First\", I = ";
		
	char zone2[] = " , J = ";
	
	char zone3[] = ", DATAPACKING = POINT";

	char dim[20];

	_itoa( a_dim, dim, 10 );

	strcat( zone1, dim );

	strcat( zone1, zone2 );

	strcat( zone1, dim );

	strcat( zone1, zone3 );

	string zone( zone1 );

	extern char dir[100];

	char tempdir[100];

	strcpy( tempdir, dir );

	strcat( tempdir, "\\Results.plt" );

	file = fopen ( tempdir, "w" );

	if (!file) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	fprintf ( file, "%s", header );

	fprintf ( file, "\n%s", variables );

	fprintf ( file, "\n%s", zone );

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

	for ( int i = 0; i < nx; i++ )
		for ( int j = 0; j < ny; j++ ) {

			fprintf(file, "\n%g, %g, %g, %g, %g, %u, %g", i*h, j*h, c[i][j], f[i][j], e[i][j], final_path[i][j], hemaetocrit[i][j] );

		};

		fclose(file);

};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void OutputWriter( int time_step ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cVessel> vessels;

	extern double c[a_dim][a_dim];

	extern double f[a_dim][a_dim];

	extern double e[a_dim][a_dim];

	extern double hemaetocrit[a_dim][a_dim];

	extern double diameter[a_dim][a_dim];

	extern double wallshear[a_dim][a_dim];

	extern double m[a_dim][a_dim];

	extern int nx, ny;

	extern double h;

	int final_path[a_dim][a_dim] = {0};

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	FILE *file;

	string header = "TITLE=\"TUMOR&CAPILLARY NETWORK\"";

	string variables = "VARIABLES= \"X (mm)\", \"Y (mm)\", \"VEGF\", \"FIBRONECTIN\", \"ENDOSTATIN\", \"MMPi\", \"TEC\", \"HEMAETOCRIT\", \"DIAMETER(MICRONS)\", \"WALL SHEAR (DYN/CM^2)\"";

	char zone1[200] = "ZONE T=\"First\", I = ";
		
	char zone2[] = " , J = ";
	
	char zone3[] = ", DATAPACKING = POINT";

	char dim[20];

	_itoa( a_dim, dim, 10 );

	strcat( zone1, dim );

	strcat( zone1, zone2 );

	strcat( zone1, dim );

	strcat( zone1, zone3 );

	string zone( zone1 );

	/*char dir[100];

	printf ("\nENTER THE DIRECTORY YOU WANT TO SAVE YOUR FILE:\n");

	scanf("%s",&dir);

	dir[0] = toupper( dir[0] );

	char maked_dir[] = ":\\Results of Angiogenesis";

	strcat ( dir, maked_dir);

	_mkdir(dir);

	printf ("\nPLEASE FIND THE RESULTS IN THE DIRECTORY %s",dir);*/

	extern char dir[100];

	char tempdir[100];

	strcpy( tempdir, dir );

	char ts[20];

	_itoa( time_step, ts, 10 );

	strcat( tempdir, "\\ResultsNo" );

	strcat( tempdir, ts );

	strcat( tempdir, ".plt" );

	file = fopen ( tempdir, "w" );

	if (!file) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	fprintf ( file, "%s", header );

	fprintf ( file, "\n%s", variables );

	fprintf ( file, "\n%s", zone );

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

	for ( int i = 0; i < nx; i++ )
		for ( int j = 0; j < ny; j++ ) {

			fprintf(file, "\n%g, %g, %g, %g, %g, %g, %u, %g, %g, %g", i*h, j*h, c[i][j], f[i][j], e[i][j], m[i][j], final_path[i][j], hemaetocrit[i][j], diameter[i][j], wallshear[i][j] );

		};

		fclose(file);

};
// ==================================================================================================================================================================================



// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// SeparateOutputWriter writes each capillary in a different zone, so that we can see each one separately but we can have all in a single file --------------------------------------

void SeparateOutputWriter() {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cVessel> vessels;

	extern double c[a_dim][a_dim];

	extern double f[a_dim][a_dim];

	extern int nx, ny;

	extern double h;

	int final_path[a_dim][a_dim] = {0};

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	FILE *file;

	string header = "TITLE=\"TUMOR&CAPILLARY NETWORK\"";

	string variables = "VARIABLES= \"X (mm)\", \"Y (mm)\", \"VEGF\", \"FIBRONECTIN\", \"TEC\"";

	/*char dir[100];

	printf ("\nENTER THE DIRECTORY YOU WANT TO SAVE YOUR FILE:\n");

	scanf("%s",&dir);

	dir[0] = toupper( dir[0] );

	char maked_dir[] = ":\\Results of Angiogenesis";

	strcat ( dir, maked_dir);

	_mkdir(dir);

	printf ("\nPLEASE FIND THE RESULTS IN THE DIRECTORY %s",dir);*/

	extern char dir[100];

	char tempdir[100];

	strcpy( tempdir, dir );

	strcat( tempdir, "\\SeparateResults.plt" );

	file = fopen ( tempdir, "w" );

	if (!file) {

		printf( "C++ CANNOT OPEN THE FILE\n" );

		return;

	};

	fprintf ( file, "%s", header);

	fprintf ( file, "\n%s", variables);

	for ( int k = 0; k != vessels.size(); k++ ) {

		string zonename = std::to_string( vessels[k].GetIDNumber() );

		string zone = " ZONE T=\"" + zonename + "\", I= a_dim , J= a_dim , DATAPACKING=POINT";

		fprintf ( file, "\n%s", zone);

		for ( int i = 0; i != nx; i++ )
			for ( int j = 0; j != ny; j++ ) {

			fprintf(file, "\n%g, %g, %g, %g, %u", i*h, j*h, c[i][j], f[i][j], vessels[k].GetPath( i, j ));

			};

	};

		fclose(file);

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void OutputWriter( int time_step, std::vector<cVessel>& vec ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern double c[a_dim][a_dim];

	extern double f[a_dim][a_dim];

	extern double hemaetocrit[a_dim][a_dim];

	extern int nx, ny;

	extern double h;

	int final_path[a_dim][a_dim] = {0};

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	FILE *file;

	string header = "TITLE=\"TUMOR&CAPILLARY NETWORK\"";

	string variables = "VARIABLES= \"X (mm)\", \"Y (mm)\", \"VEGF\", \"FIBRONECTIN\", \"TEC\", \"HEMAETOCRIT\"";

	char zone1[200] = "ZONE T=\"First\", I = ";
		
	char zone2[] = " , J = ";
	
	char zone3[] = ", DATAPACKING = POINT";

	char dim[20];

	_itoa( a_dim, dim, 10 );

	strcat( zone1, dim );

	strcat( zone1, zone2 );

	strcat( zone1, dim );

	strcat( zone1, zone3 );

	string zone( zone1 );

	/*char dir[100];

	printf ("\nENTER THE DIRECTORY YOU WANT TO SAVE YOUR FILE:\n");

	scanf("%s",&dir);

	dir[0] = toupper( dir[0] );

	char maked_dir[] = ":\\Results of Angiogenesis";

	strcat ( dir, maked_dir);

	_mkdir(dir);

	printf ("\nPLEASE FIND THE RESULTS IN THE DIRECTORY %s",dir);*/

	extern char dir[100];

	char tempdir[100];

	strcpy( tempdir, dir );

	char ts[20];

	_itoa( time_step, ts, 10 );

	strcat( tempdir, "\\ResultsNo" );

	strcat( tempdir, ts );

	strcat( tempdir, ".plt" );

	file = fopen ( tempdir, "w" );

	if (!file) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	fprintf ( file, "%s", header );

	fprintf ( file, "\n%s", variables );

	fprintf ( file, "\n%s", zone );

	for ( int k = 0; k != vec.size(); k++ ) {

		for ( int i = 0; i != nx; i++ )
			for ( int j = 0; j != ny; j++ ) {

				final_path[i][j] = final_path[i][j] + vec[k].GetPath( i, j );

			};

	};

	for ( int i = 0; i != nx; i++ )
		for ( int j = 0; j != ny; j++ ) {

			if ( final_path[i][j] > 1 )
				final_path[i][j] = 1;

		};

	for ( int i = 0; i < nx; i++ )
		for ( int j = 0; j < ny; j++ ) {

			fprintf(file, "\n%g, %g, %g, %g, %u, %g", i*h, j*h, c[i][j], f[i][j], final_path[i][j], hemaetocrit[i][j]);

		};

		fclose(file);

};
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CurveDrawer( unsigned time_step ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<double> v_cell_area;

	extern std::vector<double> time;


	extern std::vector<int> stationary;

	extern std::vector<int> right;

	extern std::vector<int> left;

	extern std::vector<int> up;

	extern std::vector<int> down;

	extern std::vector<double> stationary_p;
	extern std::vector<double> right_p;
	extern std::vector<double> left_p;
	extern std::vector<double> up_p;
	extern std::vector<double> down_p;


// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	FILE *file;

	string header = "TITLE=\"TUMOR CELLS vs. TIME\"";

	string variables = "VARIABLES= \"TIME (DAYS)\", \"ENDOTHELIAL CELLS (AREA)\", \"STATIONARY\", \"RIGHT\", \"UP\", \"DOWN\", \"LEFT\", \"STATIONARY_P\", \"RIGHT_P\", \"UP_P\", \"DOWN_P\", \"LEFT_P\"";

	extern char dir[100];

	char tempdir[100];

	strcpy( tempdir, dir );

	char ts[20];

	_itoa( time_step, ts, 10 );

	strcat( tempdir, "\\TCellCurvesNo" );

	strcat( tempdir, ts );

	strcat( tempdir, ".plt" );

	file = fopen ( tempdir, "w" );

	if (!file) {

		printf( "\nC++ CANNOT OPEN THE FILE" );

		return;

	};

	fprintf ( file, "%s", header );

	fprintf ( file, "\n%s", variables );

	for ( size_t count = 0; count < time.size(); ++count ) {

		fprintf( file, "\n%g, %g, %d, %d, %d, %d, %d, %g, %g, %g, %g, %g", time[count], v_cell_area[count], stationary[count], right[count], up[count], down[count], left[count], stationary_p[count], right_p[count], up_p[count], down_p[count], left_p[count] );

	};

	fclose(file);

};
// ==================================================================================================================================================================================
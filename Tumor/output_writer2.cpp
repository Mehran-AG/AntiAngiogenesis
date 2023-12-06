#include "output_writer2.h"

#include <vector>

#include <string>

void output_writer2(vessel& v1, unsigned int** v2, vessel& v3) {

	printf ("\n  Entered writer");

	extern std::vector<vessel> vessels;

	extern unsigned int nx, ny;

	extern float h;

	FILE *file;

	std::string header = "TITLE=\"TUMOR&CAPILLARY NETWORK\"";

	std::string variables = "VARIABLES= \"X (mm)\", \"Y (mm)\", \"m\", \"ncn\", \"counter\"";

	std::string zone = " ZONE T=\"First\", I= 201 , J= 201 , DATAPACKING=POINT";

	const char name[] = "C:\\Users\\Mehran\\Desktop\\vs.plt";

	file = fopen (name, "w" );

	fprintf ( file, "%s", header);

	fprintf ( file, "\n%s", variables);

	fprintf ( file, "\n%s", zone);

	typedef std::vector<vessel>::size_type vec_sz;

	vec_sz s = vessels.size();

	for ( unsigned int k = 0; k != s; k++ ) {


	for ( unsigned int i = 0; i < nx; i++ )
		for ( unsigned int j = 0; j < ny; j++ ) {

			fprintf(file, "\n%f, %f, %u, %u, %u", i*h, j*h, v1.path[i][j], v2[i][j], v3.path[i][j]);

		};

	};

};
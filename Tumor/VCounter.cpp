#include "VCounter.h"

#include "dimension.h"

#include <vector>

#include "cVessel.h"

void VCounter() {

	extern int cap_network[a_dim][a_dim];

	extern std::vector<cVessel> vessels;

	extern int nx, ny;

	unsigned vc_no = 0;

	double vc_area = 0.;

	extern int steps;

	extern double dim_t;

	extern double dt;

	extern std::vector<double> time;

	extern std::vector<double> v_cell_area;


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


	extern int stationaries;
	extern int rights;
	extern int lefts;
	extern int ups;
	extern int downs;

	double ttl = stationaries + rights + lefts + ups + downs;


	for ( size_t i = 0; i < a_dim; ++i )
		for ( size_t j = 0; j < a_dim; ++j )
			cap_network[i][j] = 0;

	for ( int k = 0; k != vessels.size(); k++ ) {

		for ( int i = 0; i != nx; i++ )
			for ( int j = 0; j != ny; j++ ) {

				cap_network[i][j] = cap_network[i][j] + vessels[k].GetPath( i, j );

			};

	};

	for ( size_t i = 0; i < a_dim; ++i )
		for ( size_t j = 0; j < a_dim; ++j ) {

			if ( cap_network[i][j] > 1 )
				cap_network[i][j] = 1;

		};

	for ( size_t i = 0; i < a_dim; ++i )
		for ( size_t j = 0; j < a_dim; ++j )
			vc_no += cap_network[i][j];

	vc_area = vc_no * 1E-4;

	v_cell_area.push_back( vc_area );

	time.push_back( steps * dim_t * dt );

	stationary.push_back( stationaries );

	right.push_back( rights );

	left.push_back( lefts );

	up.push_back( ups );

	down.push_back( downs );

	stationary_p.push_back( stationaries / ttl );

	right_p.push_back( rights / ttl );

	left_p.push_back( lefts / ttl );

	up_p.push_back( ups / ttl );

	down_p.push_back( downs / ttl );

};
#include "ShearBranching.h"

#include "dimension.h"

#include <vector>

#include <cstdlib>

#include "cVessel.h"

#include "cNode.h"

#include "ShearBranching.h"

#include "BranchingPointFinder.h"

#include "Brancher.h"

#include "PositionFinder.h"

void ShearBranching() {

	printf( "\nEntered Shear Branching" );

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern double c[a_dim][a_dim];

	extern double e[a_dim][a_dim];

	std::vector<unsigned> shear;

	double cf = 0.2;

	for ( size_t i = 0; i < vessels.size(); ++i )
		if ( vessels[i].GetWallShear() != 0 )
			shear.push_back( i );

	for ( size_t i = 0; i < shear.size(); ++i )
		vessels[shear[i]].NormalizeShear();

	for ( size_t v = 0; v < shear.size(); ++v ) {

		if ( ( vessels[shear[v]].GetNormShear() < 0.6 ) && ( vessels[shear[v]].GetNormShear() >= 0.4 ) ) {

			if ( vessels[shear[v]].GetUnitLength() > 6 ) {

				cVessel& vessel = vessels[shear[v]];

				std::vector<int> spots;

				int counter = 0;

				int i = vessel.GetStartingI();

				int j = vessel.GetStartingJ();

				double criterion = 0.1; //0.4

				BranchTracker( vessel, i, j, spots, counter, criterion );

				if ( spots.size() != 0 ) {

					char dir;

					bool flag = false;

					do {

						int bp = rand() % spots.size();

						i = vessel.GetStartingI();

						j = vessel.GetStartingJ();

						dir = BranchingPointFinder( vessels, vessel, spots[bp], i, j );

						if ( dir == '\0' ) {

							spots.erase( spots.begin() + bp );

							if ( spots.size() == 0 )
								flag = true;

							continue;

						};

						if ( ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.1 ) ) {
						//if ( ( c[i][j] < 0.4 ) ) {

							spots.erase( spots.begin() + bp );

							if ( spots.size() == 0 )
								flag = true;

							continue;
							
						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.1 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) <= 0.5 ) ) {
						//else if ( ( c[i][j] >= 0.4 ) && ( c[i][j] <= 0.8 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.6 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( c[i][j] - ( cf * e[i][j] ) ) > 0.5 ) {
						//else if ( c[i][j] > 0.8 ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.8 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						};

					} while ( flag == false );

				};

			};

		}

		else if ( ( vessels[shear[v]].GetNormShear() < 0.8 ) && ( vessels[shear[v]].GetNormShear() >= 0.6 ) ) {

			if ( vessels[shear[v]].GetUnitLength() > 6 ) {

				cVessel& vessel = vessels[shear[v]];

				std::vector<int> spots;

				int counter = 0;

				int i = vessel.GetStartingI();

				int j = vessel.GetStartingJ();

				double criterion = 0.1;//0.3

				BranchTracker( vessel, i, j, spots, counter, criterion );

				if ( spots.size() != 0 ) {

					char dir;

					bool flag = false;

					do {

						int bp = rand() % spots.size();

						i = vessel.GetStartingI();

						j = vessel.GetStartingJ();

						dir = BranchingPointFinder( vessels, vessel, spots[bp], i, j );

						if ( dir == '\0' ) {

							spots.erase( spots.begin() + bp );

							if ( spots.size() == 0 )
								flag = true;

							continue;

						};

						if ( ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.1 ) ) {
						//if ( ( c[i][j] < 0.3 ) ) {

							spots.erase( spots.begin() + bp );

							if ( spots.size() == 0 )
								flag = true;

							continue;

						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.1 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.3 ) ) {
						//else if ( ( c[i][j] >= 0.3 ) && ( c[i][j] < 0.5 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.4 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.3 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.5 ) ) {
						//else if ( ( c[i][j] >= 0.5 ) && ( c[i][j] < 0.7 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.7 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.5 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.75 ) ) {
						//else if ( ( c[i][j] >= 0.7 ) && ( c[i][j] < 0.9 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.9 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.75 ) {
						//else if ( c[i][j] >= 0.9 ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 1. ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						};

					} while ( flag == false );

				};

			};

		}

		else if ( vessels[shear[v]].GetNormShear() >= 0.8 ) {

			if ( vessels[shear[v]].GetUnitLength() > 6 ) {

				cVessel& vessel = vessels[shear[v]];

				std::vector<int> spots;

				int counter = 0;

				int i = vessel.GetStartingI();

				int j = vessel.GetStartingJ();

				double criterion = 0.1; //0.3

				BranchTracker( vessel, i, j, spots, counter, criterion );

				int bp = rand() % spots.size();

				if ( spots.size() != 0 ) {

					char dir;

					bool flag = false;

					do {

						int bp = rand() % spots.size();

						i = vessel.GetStartingI();

						j = vessel.GetStartingJ();

						dir = BranchingPointFinder( vessels, vessel, spots[bp], i, j );

						if ( dir == '\0' ) {

							spots.erase( spots.begin() + bp );

							if ( spots.size() == 0 )
								flag = true;

							continue;

						};

						if ( ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.1 ) ) {
						//if ( ( c[i][j] < 0.3 ) ) {

							spots.erase( spots.begin() + bp );

							if ( spots.size() == 0 )
								flag = true;

							continue;

						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.1 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.35 ) ) {
						//else if ( ( c[i][j] >= 0.3 ) && ( c[i][j] < 0.5 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.45 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.35 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.5 ) ) {
						//else if ( ( c[i][j] >= 0.5 ) && ( c[i][j] < 0.7 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.7 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.5 ) && ( ( c[i][j] - ( cf * e[i][j] ) ) < 0.7 ) ) {
						//else if ( ( c[i][j] >= 0.7 ) && ( c[i][j] < 0.8 ) ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 0.9 ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						}

						else if ( ( c[i][j] - ( cf * e[i][j] ) ) >= 0.7 ) {
						//else if ( c[i][j] >= 0.8 ) {

							double r_num_b = (double) rand() / RAND_MAX;

							if ( r_num_b <= 1. ) {

								Brancher( vessel, i, j, dir );

								flag = true;

							}
							else {

								spots.erase( spots.begin() + bp );

								if ( spots.size() == 0 )
									flag = true;

								continue;

							};

						};

					} while ( flag == false );

				};

			};

		};

	};
			
	printf( "\nExited Shear Branching" );

};
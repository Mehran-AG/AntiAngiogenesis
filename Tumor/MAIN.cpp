#include <iostream>

#include <fstream>

#include <vector>

#define _USE_MATH_DEFINES

#include <conio.h>

#include <string>

#include <direct.h>

#include "dimension.h"

#include "math.h"

#include "cVessel.h"

#include "cNode.h"

#include "Initials.h"

#include "Probabilities.h"

#include "Branching.h"

#include "MigrationOfVessels.h"

#include "FibronectinConsumption.h"

#include "VEGF_Consumption.h"

#include "MMPiConsumption.h"

#include "OutputWriter.h"

#include "printer.h"

#include "Greetings.h"

#include "InitialSproutingOfParentVessel.h"

#include "InitialConcentrations.h"

#include "FlowDistributionSolver.h"

#include "UnendedCapillaryRemover.h"

#include "CoefficientsMatrix.h"

#include "EmptyCapillaryRemover.h"

#include "DirectionModifier.h"

#include "HemaetocritSolver.h"

#include "ViscositySolver.h"

#include "SproutingOfParentVessel.h"

#include "MatlabOutput.h"

#include "ShearBranching.h"

#include "VCounter.h"

using namespace std;


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DECLARATION OF GLOBAL VARIABLES ---------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double pi = M_PI;

double r_0_l[a_dim][a_dim], r_0_u[a_dim][a_dim], r_1_l[a_dim][a_dim], r_1_u[a_dim][a_dim], r_2_l[a_dim][a_dim], r_2_u[a_dim][a_dim], r_3_l[a_dim][a_dim], r_3_u[a_dim][a_dim], r_4_l[a_dim][a_dim], r_4_u[a_dim][a_dim];

double p_0[a_dim][a_dim], p_1[a_dim][a_dim], p_2[a_dim][a_dim], p_3[a_dim][a_dim], p_4[a_dim][a_dim];

double q_0[a_dim][a_dim], q_1[a_dim][a_dim], q_2[a_dim][a_dim], q_3[a_dim][a_dim], q_4[a_dim][a_dim];

double c[a_dim][a_dim] = {0};

double f[a_dim][a_dim] = {0};

double m[a_dim][a_dim] = {0};

double e[a_dim][a_dim] = {0};

double p_sum[a_dim][a_dim]= {0};

double hemaetocrit[a_dim][a_dim] = {0};

double diameter[a_dim][a_dim] = {0};

double wallshear[a_dim][a_dim] = {0};

int nx = a_dim;

int ny = a_dim;

int x_d = nx - 1;

int y_d = ny - 1;

double d = 0.00035;

double L = 1;

double h = L / y_d;

int neighbor_checker = 3;  // this variable defines the distance which must not be any other vessels from the sprout which is going to branch
						   // it means that if in this radius of the vessel there is another vessel present, the vessel is not allowed to branch

int shorest_vessel_length = 3;

int maturity_time = 5; // This is the time needed for the new daughter capillaries to mature and be allowed to branch

double Q = 0.; // blood flow rate in parent vessel

double DeltaP = 8000;

double H = 0.45; // hemaetocrit in parent vessel

bool uncheckedVEGF[a_dim] = {1};

bool available_spots[a_dim] = {0};

int distance = 20; // 10 spatial distance which is equal to 100 micrometers

double dt = 0.02;

double chi_0 = 0.38;

double delta = 0.6;

double alpha = 1.89;

double psi = 0.16;

double k_p = 2E-3; // maximum probabilty of sprouting (1/(micrometer.day))

double l_seg = 2000; // length of parent vessel in micrometers

double dim_t = 1.5; // dimensional time (days)

double c_th = 0.8E-9; // Threshold of VEGF for sprouting (mol/lit)

double c_th_50 = 0.5E-9; // constant variable in sprouting equation (mol/lit)

double c_ref = 1E-9; // reference amount of VEGF concentration

double coef = 1500;

double rho = 0.3;

double rho_0 = 0.35;

double sigma = 0.2;

vector<double> time;

std::vector<double> v_cell_area;

int cap_network[a_dim][a_dim] = {0};


vector<int> stationary;

vector<int> right;

vector<int> left;

vector<int> up;

vector<int> down;

vector<double> stationary_p;
vector<double> right_p;
vector<double> left_p;
vector<double> up_p;
vector<double> down_p;

int stationaries = 0;
int rights = 0;
int lefts = 0;
int ups = 0;
int downs = 0;


vector<cVessel> vessels;

vector<cVessel> vessels_backup;

vector<cNode> nodes;

vector<cNode> nodes_backup;

std::vector<int> sprouts;

std::vector<int> sprouts_backup;

ofstream printer( "check.txt", ios::out );

char dir[100];

int steps;
// ==================================================================================================================================================================================

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION INITIATION ---------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){

	//Greetings();

	//_getch();

	printf ("ENTER THE DIRECTORY YOU WANT TO SAVE YOUR FILE:\n");

	scanf("%s",&dir);

	dir[0] = toupper( dir[0] );

	char maked_dir[] = ":\\Results of Angiogenesis (anti)";

	strcat ( dir, maked_dir);

	_mkdir(dir);

	printf ("\nPLEASE FIND THE RESULTS IN THE DIRECTORY \"\"%s\"\"\n",dir);

	printf( "\nPRESS \"ENTER\" TO CONTINUE" );

	//_getch();

	InitialConcentrations();

	InitialSproutingOfParentVessel();

	Initials();

	srand(975); //15480 //510

	for ( steps = 1; steps != 801; ++steps ) {

		printf( "\n\nTIME STEP IS %d", steps );

		SproutingOfParentVessel();

		Probabilities();

		Branching();

		MigrationOfVessels();

		FibronectinConsumption();

		VEGF_Consumption();

		MMPiConsumption();

		VCounter();


		/*if ( steps > 400 ) {

			for ( int i = 0; i < nx; ++i )
				for ( int j = 0; j < ny; ++j )
					e[i][j] = 0;
		};*/
			
		if ( ( steps % 10 ) == 0 ) {

			OutputWriter( steps );

		};

		if ( ( ( steps % 25 ) == 0 ) && ( steps >= 200 ) ) {

			try {

				FlowDistributionSolver();

				ShearBranching();

				CurveDrawer( steps );

			}

			catch ( char* err ) {

				cout << "\n" << err << endl;

				vessels.clear();

				nodes.clear();

				sprouts.clear();

				copy ( vessels_backup.begin(), vessels_backup.end(), back_inserter (vessels) );

				copy ( nodes_backup.begin(), nodes_backup.end(), back_inserter(nodes) );

				copy ( sprouts_backup.begin(), sprouts_backup.end(), back_inserter(sprouts) );

				vessels_backup.clear();

				nodes_backup.clear();

				sprouts_backup.clear();

			};

		};

	};

	CurveDrawer( steps );

	OutputWriter();

	return 0;

}
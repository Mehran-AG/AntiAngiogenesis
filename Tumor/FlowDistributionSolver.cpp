#include "FlowDistributionSolver.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

#include "UnendedCapillaryRemover.h"

#include "CoefficientsMatrix.h"

#include "EmptyCapillaryRemover.h"

#include "DirectionModifier.h"

#include "HemaetocritSolver.h"

#include "ViscositySolver.h"

#include "VesselAdaptionSolver.h"

#include "OutputWriter.h"

#include "PositionFinder.h"

#include <vector>

#include <iterator>

#include <fstream>

#include <iostream>

#include <iomanip>


void FlowDistributionSolver() {

	printf( "\n\nCALCULATING FLOW . . . . . . . ." );

	extern std::vector<cVessel> vessels;

	extern std::vector<cVessel> vessels_backup;

	extern std::vector<cNode> nodes;

	extern std::vector<cNode> nodes_backup;

	extern std::vector<int> sprouts;

	extern std::vector<int> sprouts_backup;

	extern double hemaetocrit[a_dim][a_dim];

	extern double diameter[a_dim][a_dim];

	extern double wallshear[a_dim][a_dim];

	extern std::ofstream printer;

	extern int steps;

	std::vector<double> mu;

	std::vector<double> d_diameter;

	OutputWriter( steps - 1 );

	try {

		// COPYING THE CONDITIONS OF VESSELS TO BACK_UP FILES TO RESTORE THEM AFTER FINISHING CALCULATION OF BLOOD FLOW IN CAPILLARIES ------------------------------------------------------
		copy ( vessels.begin(), vessels.end(), back_inserter (vessels_backup) );

		copy ( nodes.begin(), nodes.end(), back_inserter(nodes_backup) );

		copy ( sprouts.begin(), sprouts.end(), back_inserter(sprouts_backup) );

		// removing unended and void of flow capillaries at first iteration of blood flow solution -------------------------------------------------------------------------------------------
		UnendedCapillaryRemover();

		CoefficientsMatrix();

		EmptyCapillaryRemover();
	
		if ( vessels.size() == 0 ) throw "\nNO VESSELS REMAINED AFTER PRUNING";

		DirectionModifier();

		if ( vessels.size() == 0 ) throw "\nNO VESSELS REMAINED AFTER PRUNING";

		HemaetocritSolver();

		ViscositySolver();
		// =====================================================================================================================================================================================

		// initiating vessel adaptation process ------------------------------------------------------------------------------------------------------------------------------------------------
		double d_error = 0.;

		int l_counter = -1;

		//do {

		for ( size_t count = 0; count < 1000; ++count ) {

			++l_counter;

			printf("\nSTEP %d", l_counter );

			printer << l_counter << std::endl;

			d_error = 0.;

			for ( size_t f_counter = 0; f_counter < vessels.size(); ++f_counter ) {

				d_diameter.push_back( vessels[f_counter].GetDiameter() );

			};

			// hemaetocrit solver initiation ----------------------------------------
			double mu_error = 0.;

			int numm = 0;

			do {

				mu_error = 0.;

				

				for ( size_t f_counter = 0; f_counter < vessels.size(); ++f_counter ) {

					mu.push_back( vessels[f_counter].GetMu() );

				};

				CoefficientsMatrix();

				DirectionModifier();

				if ( vessels.size() == 0 ) throw "\nNO VESSELS REMAINED AFTER PRUNING";

				HemaetocritSolver();

				ViscositySolver();

				for ( size_t f_counter = 0; f_counter < vessels.size(); ++f_counter ) {

					if ( abs( vessels[f_counter].GetMu() - mu[f_counter] ) > mu_error ) {

						mu_error = abs( vessels[f_counter].GetMu() - mu[f_counter] );

					};

				};

				mu.clear();

			} while ( mu_error > 0.1 );
			// ======================================================================================================

			VesselAdaptionSolver();

			for ( size_t f_counter = 0; f_counter < vessels.size(); ++f_counter ) {

				if ( abs( vessels[f_counter].GetDiameter() - d_diameter[f_counter] ) > d_error ) {

					d_error = abs( vessels[f_counter].GetDiameter() - d_diameter[f_counter] );

				};

			};

			d_diameter.clear();

		};

		//} while ( d_error > 0.001 );
		// ===========================================================================================================================================================================================


		// copying vessel hemaetocrits to the hemaetocrit matrix -------------------------------------------------------------------------------------------------------------------------------------
		for ( size_t i = 0; i < a_dim; ++i )
			for ( size_t j = 0; j < a_dim; ++j ) {

				hemaetocrit[i][j] = 0.;
				diameter[i][j] = 0.;
				wallshear[i][j] = 0.;

			};

		for ( size_t v = 0; v < vessels.size(); ++v ) {

			for ( size_t i = 0; i < a_dim; ++i )
				for ( size_t j = 0; j < a_dim; ++j ) {

					if ( vessels[v].GetPath( i, j ) ) {

						hemaetocrit[i][j] = vessels[v].GetHemaetocrit();

						diameter[i][j] = vessels[v].GetDiameter();

						wallshear[i][j] = vessels[v].GetWallShear();

						if ( wallshear[i][j] > 20 )
							wallshear[i][j] = 20;

					};

				};

		};
		// =============================================================================================================================================================================================

		// copying vessel segment specifications to the main vessel vector -----------------------------------------------------------------------------------------------------------------------------
		for ( size_t v = 0; v < vessels.size(); ++v ) {

			unsigned num = vessels[v].GetIDNumber();

			unsigned ps = PositionFinder( vessels_backup, num );

			vessels_backup[ps].CopyVessel( vessels[v] );

		};

		// copying node specifications (pressure) to the main node vector -----------------------------------------------------------------------------------------------------------------------------
		for ( size_t n = 0; n < nodes.size(); ++n ) {

			unsigned num = nodes[n].GetIDNumber();

			unsigned ps = PositionFinder( nodes_backup, num );

			nodes_backup[ps].CopyNode( nodes[n] );

		};
		// ===========================================================================================================================================================================================

	}

	catch ( char * s ) {

		printf( "%s", s );

		goto end;

	};

end:

	OutputWriter( steps );

	vessels.clear();

	nodes.clear();

	sprouts.clear();

	copy ( vessels_backup.begin(), vessels_backup.end(), back_inserter (vessels) );

	copy ( nodes_backup.begin(), nodes_backup.end(), back_inserter(nodes) );

	copy ( sprouts_backup.begin(), sprouts_backup.end(), back_inserter(sprouts) );

	vessels_backup.clear();

	nodes_backup.clear();

	sprouts_backup.clear();

	for ( size_t i = 0; i < vessels.size(); ++i ) {

		printer << "Hemaetocrit of " << vessels[i].GetIDNumber() << " is " << vessels[i].GetHemaetocrit() << std::endl;

	};

	for ( size_t i = 0; i < vessels.size(); ++i ) {

		printer << "Flow of " << vessels[i].GetIDNumber() << " is " << vessels[i].GetFlowRate() << std::endl;

	};

	for ( size_t i = 0; i < vessels.size(); ++i ) {

		printer << "Mu of vessel no " << vessels[i].GetIDNumber() << " is " << vessels[i].GetMu() << std::endl;

	};

	for ( size_t i = 0; i < vessels.size(); ++i ) {

		printer << "Diameter of vessel no " << vessels[i].GetIDNumber() << " is " << vessels[i].GetDiameter() << std::endl;

	};

	for ( size_t i = 0; i < vessels.size(); ++i ) {

		printer << "Wall Shear of vessel no " << vessels[i].GetIDNumber() << " is " << vessels[i].GetWallShear() << std::endl;

	};

	for ( size_t i = 0; i < nodes.size(); ++i ) {

		printer << "PRESSURE of node no " << nodes[i].GetIDNumber() << " is " << nodes[i].GetPressure() << std::endl;

	};

};
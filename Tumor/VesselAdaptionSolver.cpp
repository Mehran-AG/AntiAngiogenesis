#include "VesselAdaptionSolver.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

#include "PositionFinder.h"

#include <vector>

#include <fstream>

void VesselAdaptionSolver() {

	extern std::ofstream printer;

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::vector<int> sprouts;

	std::vector<double> diameter;

	extern double pi;

	double dt = 0.0001;

	for ( size_t i = 0; i < vessels.size(); ++i ) {

		int s_node, e_node;

		s_node = PositionFinder( nodes, vessels[i].GetStartNode() );

		e_node = PositionFinder( nodes, vessels[i].GetEndNode() );

		double pressure = 0.;

		pressure = 0.5 * ( nodes[s_node].GetPressure() + nodes[e_node].GetPressure() );

		vessels[i].SetPressure( pressure );

	};

	vessels[0].SetDeltaT( dt );

	for ( size_t i = ( sprouts.size() - 1 ); i < vessels.size(); ++i ) {

		if ( ( vessels[i].GetDiameter() <= 2 ) || ( vessels[i].GetDiameter() >= 12 ) ) continue;

		double new_d = 0.;

		vessels[i].SolveWallShearStressStimulus();

		vessels[i].SolvePressureStimulus();

		vessels[i].SolveMetabolicStimulus();

		vessels[i].FindDeltaR();

		new_d = vessels[i].GetDiameter() + ( 2 * vessels[i].GetDeltaR() );

		if ( vessels[i].CompareToOldDiameters( new_d ) == false ) {

			vessels[i].SetDiameter( new_d );

			vessels[i].AddToOldDiameters( new_d );

		};

	};

};
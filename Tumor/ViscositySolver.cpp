#include "ViscositySolver.h"

#include "dimension.h"

#include "cVessel.h"

#include <iostream>

#include <fstream>

void ViscositySolver() {

	//printf( "\nViscosity Started" );

	extern std::vector<cVessel> vessels;

	extern std::ofstream printer;

	for ( auto vessel = vessels.begin(); vessel != vessels.end(); ++vessel ) {

		double new_mu = 0.;

		vessel->SetC();

		double hf = vessel->HemaetocritFunction();

		vessel->SetMu45();

		vessel->SetMuRel( hf );

		new_mu = vessel->FindMu();

		if ( vessel->CompareToOldMus( new_mu ) == false ) {

			vessel->SetMu();

			vessel->AddToOldMus( new_mu );

		};

	};

	//printf( "\nViscosity Ended" );

};
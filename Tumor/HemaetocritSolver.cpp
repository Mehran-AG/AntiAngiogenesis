#include "HemaetocritSolver.h"

#include "dimension.h"

#include "cNode.h"

#include "cVessel.h"

#include "PositionFinder.h"

#include <cmath>

#include <vector>

#include <fstream>

#include <iostream>

#include <cmath>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THE LOGIT FUNCTION USED IN THE EQUATION OF HEMAETOCRIT DISTRIBUTION --------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double logit( double );
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A STRUCTURE TO HOLD TEMPORARY VARIABLES OF HEMAETOCRIT, BLOOD FLOW RATE AND ERYTHROCYTE FLOW RATE --------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct temp {

	double q; // temporary blood flow rate

	double h; // temporary hemaetocrit

	double e; // temporary erythrocyte

	temp() : q(0), h(0), e(0) {};

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THE FUNCTION FINDS HEMAETOCRIT IN CAPILLARIES BASED ON THE DISTRIBUTION LAW IN BIFURCATIONS PROPOSED BY PRIS ET AL. [2005] -------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void HemaetocritSolver() {

	//printf( "\nHemaetocrit Started" );

// DECLARATION OF VARIABLES ---------------------------------------------------------------------------------------------------------------------------------------------------------

	extern std::vector<cNode> nodes;

	extern std::vector<cVessel> vessels;

	extern std::vector<int> sprouts;

	extern std::ofstream printer;

	std::vector<temp> vec;

	double A, B, X_0;

	int in1, in2, out1, out2;

	double FE_1; // fraction of erythrocyte flow rate of one daughter vessel to mother vessel

	double FQ_1; // fraction of blood flow rate of one daughter vessel to mother vessel

	// putting the variables of vessels into the structure declared to store temporary variables
	// this is done in order to make the code able to compare updated results with old ones to see if calculation is finished or not
	for ( size_t i = 0; i < vessels.size(); ++i ) {

		temp t;

		t.h = vessels[i].hemaetocrit;

		t.q = vessels[i].q;

		t.e = vessels[i].e;

		vec.push_back( t );

	};


	extern double Q; // blood flow rate in parent vessel

	extern double H; // hemaetocrit in parent vessel


	// finding blood flow rate in parent vessel -------------------------------------------------------------------------------------------------------------------------------------
	if ( nodes[0].GetInletVesselNumber( 1 ) >= 0 ) {

		try {

			in1 = PositionFinder( vessels, nodes[0].GetInletVesselNumber( 1 ) );

		}

		catch ( int wrong ) {

			printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

			system("pause");

		};

		if ( nodes[0].GetInletVesselNumber( 2 ) >= 0 ) {

			try {

				in2 = PositionFinder( vessels, nodes[0].GetInletVesselNumber( 2 ) );

			}
	
			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

				system("pause");

			};

		}

		else {

			try {

				in2 = PositionFinder( vessels, nodes[0].GetInletVesselNumber( 3 ) );

			}
	
			catch ( int wrong ) {

				printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

				system("pause");

			};

		};

	}

	else {

		try {

			in1 = PositionFinder( vessels, nodes[0].GetInletVesselNumber( 2 ) );

			in2 = PositionFinder( vessels, nodes[0].GetInletVesselNumber( 3 ) );

		}

		catch ( int wrong ) {

			printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

			system("pause");

		};

	};

	extern double Q;
	
	Q = vec[in1].q + vec[in2].q;

	double E = H * Q; // erythrocyte flow rate in parent vessel
	// ==============================================================================================================================================================================


	// FINDING HEMAETOCRITS ---------------------------------------------------------------------------------------------------------------------------------------------------------
	// error that should be achieved, initial value is zero
	double error = 0.0;

	// it will repeat hemaetocrit distribution analysis until all capillaries' hemaetocrits are determined
	do {

		error = 0.0;


		for ( size_t node_number = 1; node_number < nodes.size(); ++node_number ) {

			cNode& node = nodes[node_number];

			// this node has inlet vessel with known blood flow rate and hemaetocrit
			if ( node_number == ( sprouts.size() - 1 ) ) {

				if ( node.GetOutletVesselNumber( 1 ) >= 0 ) {

					try {

						out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 1 ) );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

						system("pause");

					};

					if ( node.GetOutletVesselNumber( 2 ) >= 0 ) {

						try {

							out2 = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );

						}

						catch ( int wrong ) {

							printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

							system("pause");

						};

					}

					else if ( node.GetOutletVesselNumber( 3 ) >= 0 ) {

						try {

							out2 = PositionFinder( vessels, node.GetOutletVesselNumber( 3 ) );

						}

						catch ( int wrong ) {

							printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

							system("pause");

						};

					};

				}

				else {

					try {

						out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );

						out2 = PositionFinder( vessels, node.GetOutletVesselNumber( 3 ) );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

						system("pause");

					};

				};

				temp& outlet1 = vec[out1];

				temp& outlet2 = vec[out2];

				FQ_1 = outlet1.q / Q;

				A = ( -13.29 * ( 1 - H ) / 14 ) * ( pow( (vessels[out1].d/vessels[out2].d), 2 ) - 1 ) / ( pow( (vessels[out1].d/vessels[out2].d), 2 ) + 1 );

				B = 1 + ( 6.98 * ( 1 - H ) / 14 );

				X_0 = 0.964 * ( 1 - H ) / 14;

				if ( FQ_1 <= X_0 ) {

					FE_1 = 0;

					outlet1.h = 0;

					outlet1.e = 0;

					outlet2.e = E;

					outlet2.h = outlet2.e / outlet2.q;

				}

				else if ( ( FQ_1 > X_0 ) && ( FQ_1 <= ( 1-X_0 ) ) ) {

					double c = A + B * logit( ( FQ_1 - X_0 ) / ( 1 - ( 2*X_0 ) ) );

					double C = exp( c );

					FE_1 = C / ( 1 + C );

					outlet1.e = FE_1 * E;

					outlet1.h = outlet1.e / outlet1.q;

					outlet2.e = E - outlet1.e;

					outlet2.h = outlet2.e / outlet2.q;

				}

				else if ( FQ_1 > ( 1-X_0 ) ) {

					outlet1.e = E;

					outlet1.h = outlet1.e / outlet1.q;

					outlet2.h = 0;

					outlet2.e = 0;

				};

			}

			else if ( node.GetNumberOfBranches() == 2 ) {

				if ( node.GetNumberOfInletVessels() == 2 ) {

					printf("\nThere are 2 vessels in the node and both are INLETS" );

					printf( "\nNode Number is %d\n", node.GetIDNumber() );

					int nm = PositionFinder( nodes, node.GetIDNumber() );

					nodes[nm].Print( printer );

					system("pause");

				}

				else if ( node.GetNumberOfOutletVessels() == 2 ) {

					printf("\nThere are 2 vessels in the node and both are OUTLETS" );

					printf( "\nNode Number is %d\n", node.GetIDNumber() );

					int nm = PositionFinder( nodes, node.GetIDNumber() );

					nodes[nm].Print( printer );

					system("pause");

				}

				else {

					try {

						if ( node.GetInletVesselNumber( 1 ) >=0 )
							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 1 ) );
						else if ( node.GetInletVesselNumber( 2 ) >= 0 )
							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 2 ) );
						else if ( node.GetInletVesselNumber( 3 ) >= 0 )
							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 3 ) );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

						system("pause");

					};

					try {

						if ( node.GetOutletVesselNumber( 1 ) >= 0 )
							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 1 ) );
						else if ( node.GetOutletVesselNumber( 2 ) >= 0 )
							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );
						else if ( node.GetOutletVesselNumber( 3 ) >= 0 )
							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 3 ) );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

						system("pause");

					};

					vec[out1].e = vec[in1].e;

					vec[out1].h = vec[out1].e / vec[out1].q;

				};

			}

			else if ( node.GetNumberOfBranches() == 3 ) {

				if ( node.GetNumberOfInletVessels() == 2 ) {

					if ( node.GetInletVesselNumber( 1 ) >= 0 ) {

						try {

							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 1 ) );

						}

						catch ( int wrong ) {

							printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

							system("pause");

						};

						if ( node.GetInletVesselNumber( 2 ) >= 0 ) {

							try {

								in2 = PositionFinder( vessels, node.GetInletVesselNumber( 2 ) );

							}
	
							catch ( int wrong ) {

								printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

								system("pause");

							};

						}

						else {

							try {

								in2 = PositionFinder( vessels, node.GetInletVesselNumber( 3 ) );

							}
	
							catch ( int wrong ) {

								printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

								system("pause");

							};

						};

					}

					else {

						try {

							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 2 ) );

							in2 = PositionFinder( vessels, node.GetInletVesselNumber( 3 ) );

						}

						catch ( int wrong ) {

							printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

							system("pause");

						};

					};

					try {

						if ( node.GetOutletVesselNumber( 1 ) >= 0 )
							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 1 ) );
						else if ( node.GetOutletVesselNumber( 2 ) >= 0 )
							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );
						else if ( node.GetOutletVesselNumber( 3 ) >= 0 )
							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 3 ) );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

						system("pause");

					};

					vec[out1].e = vec[in1].e + vec[in2].e;

					vec[out1].h = vec[out1].e / vec[out1]. q;

				}

				else if ( node.GetNumberOfOutletVessels() == 2 ) {

					try {

						if ( node.GetInletVesselNumber( 1 ) >=0 )
							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 1 ) );
						else if ( node.GetInletVesselNumber( 2 ) >= 0 )
							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 2 ) );
						else if ( node.GetInletVesselNumber( 3 ) >= 0 )
							in1 = PositionFinder( vessels, node.GetInletVesselNumber( 3 ) );

					}

					catch ( int wrong ) {

						printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

						system("pause");

					};

					if ( node.GetOutletVesselNumber( 1 ) >= 0 ) {

						try {

							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 1 ) );

						}

						catch ( int wrong ) {

							printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

							system("pause");

						};

						if ( node.GetOutletVesselNumber( 2 ) >= 0 ) {

							try {

								out2 = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );

							}

							catch ( int wrong ) {

								printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

								system("pause");

							};

						}

						else if ( node.GetOutletVesselNumber( 3 ) >= 0 ) {

							try {

								out2 = PositionFinder( vessels, node.GetOutletVesselNumber( 3 ) );

							}

							catch ( int wrong ) {

								printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

								system("pause");

							};

						};

					}

					else {

						try {

							out1 = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );

							out2 = PositionFinder( vessels, node.GetOutletVesselNumber( 3 ) );

						}

						catch ( int wrong ) {

							printf( "\nNO MATCHES IN VESSELS VECTOR IN HEMATOCRIT SOLVER AND NO. IS %d\n", wrong );

							system("pause");

						};

					};

					temp& inlet = vec[in1];

					temp& outlet1 = vec[out1];

					temp& outlet2 = vec[out2];

					// all diameters are in micrometers in formulae

					FQ_1 = outlet1.q / inlet.q;

					A = ( -13.29 * ( 1 - inlet.h ) / vessels[in1].d ) * ( pow( (vessels[out1].d/vessels[out2].d), 2 ) - 1 ) / ( pow( (vessels[out1].d/vessels[out2].d), 2 ) + 1 );

					B = 1 + ( 6.98 * ( 1 - inlet.h ) / vessels[in1].d );

					X_0 = 0.964 * ( 1 - inlet.h ) / vessels[in1].d;

					if ( FQ_1 <= X_0 ) {

						FE_1 = 0;

						outlet1.h = 0;
	
						outlet1.e = 0;

						outlet2.e = inlet.e;

						outlet2.h= outlet2.e / outlet2.q;

					}

					else if ( ( FQ_1 > X_0 ) && ( FQ_1 <= ( 1-X_0 ) ) ) {


						double c = A + B * logit( ( FQ_1 - X_0 ) / ( 1 - ( 2*X_0 ) ) );

						double C = exp( c );

						FE_1 = C / ( 1 + C );

						outlet1.e = FE_1 * inlet.e;

						outlet1.h = outlet1.e / outlet1.q;

						outlet2.e = inlet.e - outlet1.e;

						outlet2.h = outlet2.e / outlet2.q;

					}

					else if ( FQ_1 > ( 1-X_0 ) ) {

						outlet1.e = inlet.e;

						outlet1.h = outlet1.e / outlet1.q;

						outlet2.h = 0;

						outlet2.e = 0;

					};

				};

			};

		};

		for ( size_t i = 0; i < vessels.size(); ++i ) {

			if ( abs( vessels[i].hemaetocrit - vec[i].h ) > error )
				error = abs( vessels[i].hemaetocrit - vec[i].h );

		};

		for ( size_t i = 0; i < vessels.size(); ++i ) {

			vessels[i].hemaetocrit = vec[i].h;
			vessels[i].e = vec[i].e;

		};

	} while( error > 0.00001 );

	//printf( "\nHemaetocrit Ended" );

};
// ==================================================================================================================================================================================


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITION OF FUNCTION -----------------------------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
double logit( double x ) {

	double result;

	try {

		if ( x < 0 ) throw 10;

		if ( ( 1 - x ) < 0 ) throw 10;

		result = log( x / ( 1-x ) );

	}

	catch ( int wrong ) {

		printf( "\nVARIABLE IN LOGARITHM IS NEGATIVE AND PARAMETER IN LOG IS %d\n", wrong );

		system("pause");

	};

	return result;

};
// ==================================================================================================================================================================================
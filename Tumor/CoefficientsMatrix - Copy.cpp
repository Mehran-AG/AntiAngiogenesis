#include "CoefficientsMatrix.h"

#include "Matrix.h"

#include "cVessel.h"

#include "cNode.h"

#include "PositionFinder.h"

#include <cmath>

#include <Eigen/IterativeLinearSolvers>
#include<Eigen/SparseLU>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// HERE I SCHEMATICALLY DRAW THE INITIAL PARENT VESSEL AND IMAGINARY SPROUTS AND NUMBERING PROCEDURE --------------------------------------------------------------------------------
//
//               |
//         Q_in  |  1.41431E-13 m^3/s
//               |
//               v
//        NODE 4 o----> SPROUT 8
//               v
//               |
//             3 |
//               |
//               v
//        NODE 3 o----> SPROUT 7
//               v
//               |
//             2 |
//               |
//               v
//        NODE 2 o----> SPROUT 6
//               v
//               |
//             1 |
//               |
//               v
//        NODE 1 o----> SPROUT 5
//               v
//               |
//             0 |
//               |
//               v
//        NODE 0 o----> SPROUT 4
//               v
//               |
//        Q_out  |  1.41431E-13 m^3/s
//               |
//               v
//           MAIN VESSEL => FLOW RATE IS 1.41431E-13 m^3/s AND P_0 IS 0
// ==================================================================================================================================================================================

// IN THIS FUNCTION, UNKNOWNS ARE ASSIGNED TO THE MATRIX BASED ON TODINI AND PILATI 1987
//
// BELOW MATRIX IS CREATED BASED ON THE FIGURE ABOVE, THE POSITION OF THE Q_IN MAY BE DIFFERENT BASED ON THE NODES
//
//        _  Q_0  Q_1  Q_2  Q_3  Q_4 . . .  P_1 P_2 P_3 . . .  _      _  x _       _  b  _
//  V_0  |													    |    |      |     |       |
//  V_1  |													    |    |      |     |       |
//  V_2  |													    |    |      |     |       |
//  V_3  |													    |    |      |     |       |
//  V_4  |													    |    |      |     |       |
//  V_5  |													    |    |      |     |       |
//  V_6  |													    |    |      |     |       |
//    .  |													    |    |      |  =  |       |
//    .  |													    |    |      |     |       |
//    .  |													    |    |      |     |       |
//    .  |													    |    |      |     |       |
//  N_1  |													    |    |      |     |       |
//  N_2  |													    |    |      |     |       |
//  N_3  |													    |    |      |     |       |
//  N_4  |													    |    |      |     | Q_in  |
//    .  |													    |    |      |     |       |
//    .  |_													   _|    |_    _|     |_     _|
//  
// THIS MATRIX IS A SPARSE MATRIX WHICH IS SOLVED USING <<EIGEN>> LIBRARY FOR MATRICES


void CoefficientsMatrix() {

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::vector<int> sprouts;

	extern double pi;

	// assigning new names for types of matrices in Eigen Library
	typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
	typedef Eigen::Triplet<double> T;

	// blood flow in parent vessel
	double Q = 1.41431e-13;

	// dimension of a spatial step in the domain which is equivalent to a stalk cell's dimension
	double stalk_cell_dimension = 20E-6; // micrometer

	// assigning the vessel's real lengths
	for ( size_t i = 0; i < vessels.size(); ++i ) {

		vessels[i].SetLength( stalk_cell_dimension );

	};

	// dimension of the coefficients matrix
	unsigned size = vessels.size() + nodes.size() - 1;

	// index of the last vessel in the matrix since indices of matrix and vector start from zero
	unsigned last_vessel_index = vessels.size() - 1;

	// number of segments on th parent vessel
	unsigned pv_segments = sprouts.size() - 1;

	// coefficient of the flow in the matrix which is equivalent to resistance in electric circuits
	double parent_co = ( -128 * 4E-3 ) / ( pi * pow( ( 14E-6 ) , 4 ) );

	double daughter_co = ( -128 * 4E-3 ) / ( pi * pow( ( 8E-6 ) , 4 ) );

	// Eigen Library variables
	std::vector<T> coefficients;
	Eigen::VectorXd b(size), x(size);

	// Matrix library variable
	ExMat::Matrix<double> test(size,size);

	// initializing the matrix
	for ( size_t i = 0; i < size; ++i )
		for ( size_t j = 0; j < size; ++j )
			test.put(i,j,0);

	// initializing the vectors of unknowns and right hand side
	for ( size_t i = 0; i < size; ++i )
	{ x(i) = 0; b(i) = 0; };

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ASSIGNING THE ELEMENTS OF COEFFICIENTS MATRIX ------------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// At first, pressure loss equation is written for each capillary in the network
	// it should be noted that capillaries connected to the first node are different from the others since pressure is zero at first node
	for ( size_t i = 0; i < vessels.size(); ++i ) {

		double value;

		if ( i < pv_segments )
			value = parent_co * vessels[i].GetLength();
		else
			value = daughter_co * vessels[i].GetLength();

		if ( i == 0 ) {

			test.put( i, i, value );
			coefficients.push_back( T(i,i,value) );

			int s_node, column;

			try {

				s_node = PositionFinder( nodes, vessels[i].GetStartNode() );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN NODES VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			column = last_vessel_index + s_node;

			test.put( i, column, 1 );
			coefficients.push_back( T(i,column,1) );

		}

		else if ( i == pv_segments ) {

			test.put( i, i, value );
			coefficients.push_back( T(i,i,value) );

			int e_node, column;

			try {

				e_node = PositionFinder( nodes, vessels[i].GetEndNode() );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN NODES VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			column = last_vessel_index + e_node;

			test.put( i, column, -1 );
			coefficients.push_back( T(i,column,-1) );

		}

		else {

			int s_node, e_node, column;

			test.put( i, i, value );
			coefficients.push_back( T(i,i,value) );

			try {

				s_node = PositionFinder( nodes, vessels[i].GetStartNode() );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN NODES VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			column = last_vessel_index + s_node;

			test.put( i, column, 1 );
			coefficients.push_back( T(i,column,1) );


			try {

				e_node = PositionFinder( nodes, vessels[i].GetEndNode() );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN NODES VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			column = last_vessel_index + e_node;

			test.put( i, column, -1 );
			coefficients.push_back( T(i,column,-1) );

		};

	};
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// second, inlet and outlet flows to each node is written at separate rows
	for ( size_t i = 1; i < nodes.size(); ++i ) {

		cNode& node = nodes[i];

		int row, column;

		row = last_vessel_index + i;

		if ( node.GetInletVesselNumber( 1 ) >= 0 ) {

			try {

				column = PositionFinder( vessels, node.GetInletVesselNumber( 1 ) );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN VESSELS VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			test.put( row, column, 1 );
			coefficients.push_back( T(row,column,1) );

		};

		if ( node.GetInletVesselNumber( 2 ) >= 0 ) {

			try {

				column = PositionFinder( vessels, node.GetInletVesselNumber( 2 ) );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN VESSELS VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			test.put( row, column, 1 );

			coefficients.push_back( T(row,column,1) );

		};

		if ( node.GetOutletVesselNumber( 1 ) >= 0 ) {

			try {

				column = PositionFinder( vessels, node.GetOutletVesselNumber( 1 ) );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN VESSELS VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			test.put( row, column, -1 );

			coefficients.push_back( T(row,column,-1) );

		};

		if ( node.GetOutletVesselNumber( 2 ) >= 0 ) {

			try {

				column = PositionFinder( vessels, node.GetOutletVesselNumber( 2 ) );

			}

			catch ( double ) {

				printf( "\nNO MATCHES FOR THE VESSEL IN VESSELS VECTOR IN UNKNOWN MATRIX\n" );

				system("pause");

			};

			test.put( row, column, -1 );

			coefficients.push_back( T(row,column,-1) );

		};

	};
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// CALCULATION OF THE ECHELON FORM OF THE MATRIX TO CHECK LINEAR INDEPENDENCE OF ITS EQUATIONS
	test.reducedRowEcholon();

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// TESTING THE MATRIX TO SEE IF THE EQUATIONS ARE LINEARLY INDEPENDENT BY MAKING ITS ECHELON FORM MATRIC ----------------------------------------------------------------------------

	for ( unsigned i = 0; i != size; ++i ) { // 12

		double aamax = 0.0;

		for ( unsigned j = 0; j != size; ++j ) { // 11

			if ( abs(test.get(i,j)) > aamax ) aamax = abs(test.get(i,j));

		};

		try { // t

			if ( aamax == 0.0 ) throw std::runtime_error ( "\nSingular matrix" );

		}

		catch ( std::runtime_error err ) {

			std::cout << err.what() << std::endl;

			system("pause");

			exit(1);

		}; // end of t

	}; // 12

// ==================================================================================================================================================================================
	
	// inlet flow rate is known, therefore it should be witten in the rhs matrix
	int row = last_vessel_index + pv_segments;

	b( row ) = -Q;

	// Sparse Matrix for the Eigen Library is created
	SpMat U(size,size);
	
	// The Sparse Matrix is initialized using its function
	U.setFromTriplets(coefficients.begin(), coefficients.end());
	
	// Solver is initialized and solved based on the Eigen Library functions
	Eigen::SparseLU<SpMat> solver;
	
	solver.analyzePattern(U);
	
	solver.factorize(U);
	
	x = solver.solve(b);
	
	// assigning vessels their corresponding flow
	for ( size_t i = 0; i < vessels.size(); ++i ) {

		vessels[i].SetFlowRate( x(i) );

	};

	std::cout << std::endl;

	// capillaries which are void of flow are removed from the network
	for ( size_t i = 0; i < vessels.size(); ++i ) {

		if ( ( !( abs( vessels[i].GetFlowRate() ) > 0 ) )  || ( abs( vessels[i].GetFlowRate() ) < 1E-18 ) ) {

			vessels.erase( vessels.begin() + i );

			--i;

		};

	};

};
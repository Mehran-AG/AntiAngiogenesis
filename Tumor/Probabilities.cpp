#include "Probabilities.h"

#include "dimension.h"

#include <cmath>


double Z_rho ( double );

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Probabilities() {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern double dt;

	extern double chi_0;

	extern double psi;

	extern double alpha;

	extern double rho;

	extern double delta;

	extern int nx, ny, x_d, y_d;

	extern double h, d;

	extern double c[a_dim][a_dim], f[a_dim][a_dim], e[a_dim][a_dim];

	double chi[a_dim][a_dim];

	extern double p_0[a_dim][a_dim], p_1[a_dim][a_dim], p_2[a_dim][a_dim], p_3[a_dim][a_dim], p_4[a_dim][a_dim];

	extern double p_sum[a_dim][a_dim];

	extern double q_0[a_dim][a_dim], q_1[a_dim][a_dim], q_2[a_dim][a_dim], q_3[a_dim][a_dim], q_4[a_dim][a_dim];

	extern double r_0_l[a_dim][a_dim], r_0_u[a_dim][a_dim], r_1_l[a_dim][a_dim], r_1_u[a_dim][a_dim], r_2_l[a_dim][a_dim], r_2_u[a_dim][a_dim], r_3_l[a_dim][a_dim], r_3_u[a_dim][a_dim], r_4_l[a_dim][a_dim], r_4_u[a_dim][a_dim];

// INITIATION OF THE PROCEDURE ----------------------------------------------------------------------------------------------------------------------------------------------------------

	for ( int i = 1; i < x_d; i++ ) {

		for ( int j = 1; j < y_d; j++ ) {

			chi[i][j]= chi_0 * ( 1 + delta * c[i][j] ) / ( 1 + alpha * e[i][j] );
 
			p_0[i][j]= 1 - ( 4 * dt * d / pow (h,2) ) + ( dt * alpha * chi[i][j] ) * ( pow ( ( c[i+1][j] - c[i-1][j] ),2) + pow ( ( c[i][j+1] - c[i][j-1] ),2) )
					 / ( 4 * pow (h,2) * ( 1 + alpha * e[i][j] ) ) - ( dt * chi[i][j] / pow (h,2) ) * ( c[i+1][j] + c[i-1][j] - 4 * c[i][j] + c[i][j+1] + c[i][j-1] )
					 - ( dt * chi_0 * delta / ( ( 4 * pow(h,4) ) ) * ( 1 + alpha * e[i][j] ) ) * ( pow ( ( c[i+1][j] - c[i-1][j] ),2) + pow ( ( c[i][j+1] - c[i][j-1] ),2) )
					 - ( dt * psi / pow (h,2) ) * ( f[i+1][j] + f[i-1][j] - 4 * f[i][j] + f[i][j+1] + f[i][j-1] );

			p_1[i][j]= ( dt * d / pow (h,2) ) + ( ( 0.25 * dt / pow (h,2) ) * ( ( chi[i][j] * ( c[i+1][j] - c[i-1][j] ) ) + ( psi * ( f[i+1][j] - f[i-1][j] ) ) ) );

			p_2[i][j]= ( dt * d / pow (h,2) ) - ( ( 0.25 * dt / pow (h,2) ) * ( ( chi[i][j] * ( c[i+1][j] - c[i-1][j] ) ) + ( psi * ( f[i+1][j] - f[i-1][j] ) ) ) );

			p_3[i][j]= ( dt * d / pow (h,2) ) + ( ( 0.25 * dt / pow (h,2) ) * ( ( chi[i][j] * ( c[i][j+1] - c[i][j-1] ) ) + ( psi * ( f[i][j+1] - f[i][j-1] ) ) ) );

			p_4[i][j]= ( dt * d / pow (h,2) ) - ( ( 0.25 * dt / pow (h,2) ) * ( ( chi[i][j] * ( c[i][j+1] - c[i][j-1] ) ) + ( psi * ( f[i][j+1] - f[i][j-1] ) ) ) );

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// check for negative probabilities and set them to zero ----------------------------------------------------------------------------------------------------------------------------

			if (p_0[i][j]<0)
				p_0[i][j] = 0;
  
			if (p_1[i][j]<0)
				p_1[i][j] = 0;

			if (p_2[i][j]<0)
				p_2[i][j] = 0;

			if (p_3[i][j]<0)
				p_3[i][j] = 0;

			if (p_4[i][j]<0)
				p_4[i][j] = 0;

			};

		};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// prohibit motion towards the boundaries -------------------------------------------------------------------------------------------------------------------------------------------
	for ( int j = 1; j < y_d; j++ ) {

		p_2[1][j] = 0;
		p_1[a_dim-2][j] = 0;

	};

	for ( int i = 1; i < x_d; i++ ) {

		p_4[i][1] = 0;                              
		p_3[i][a_dim-2] = 0;

	};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// normalize the probabilities between 0 and 1 -------------------------------------------------------------------------------------------------------------------------------------
	for ( int i = 1; i < x_d; i++)
		for ( int j = 1; j < y_d; j++) {

 
		// compute sum of probabilities for right vessel
		p_sum[i][j] = p_0[i][j] + p_1[i][j] + p_2[i][j] + p_3[i][j]+ p_4[i][j];

		// compute normalized probabilities for right vessel
		q_0[i][j] = p_0[i][j] / p_sum[i][j];
		q_1[i][j] = p_1[i][j] / p_sum[i][j];
		q_2[i][j] = p_2[i][j] / p_sum[i][j];
		q_3[i][j] = p_3[i][j] / p_sum[i][j];
		q_4[i][j] = p_4[i][j] / p_sum[i][j];
  
		// determine upper and lower bands for probability extensions
		r_0_l[i][j] = 0;
		r_0_u[i][j] = q_0[i][j];

		r_1_l[i][j] = q_0[i][j];
		r_1_u[i][j] = q_0[i][j] + q_1[i][j];

		r_2_l[i][j] = q_0[i][j] + q_1[i][j];
		r_2_u[i][j] = q_0[i][j] + q_1[i][j] + q_2[i][j];

		r_3_l[i][j] = q_0[i][j] + q_1[i][j] + q_2[i][j];
		r_3_u[i][j] = q_0[i][j] + q_1[i][j] + q_2[i][j] + q_3[i][j];
   
		r_4_l[i][j] = q_0[i][j] + q_1[i][j] + q_2[i][j] + q_3[i][j];
		r_4_u[i][j] = q_0[i][j] + q_1[i][j] + q_2[i][j] + q_3[i][j] + q_4[i][j];
		
		};


};
// ==================================================================================================================================================================================



double Z_rho ( double rho ) {

	extern double rho_0;

	extern double sigma;

	return exp( -pow( ( rho - rho_0 ), 2 ) / ( 2 * pow( sigma, 2 ) ) );

};
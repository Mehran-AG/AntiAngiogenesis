#include "RangeCalculator.h"

#include "dimension.h"

#include "cVessel.h"

#include <vector>


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void RangeCalculator( int i, int j ) {

// DECARATION OF VARIABLES ----------------------------------------------------------------------------------------------------------------------------------------------------------

	extern double p_0[a_dim][a_dim], p_1[a_dim][a_dim], p_2[a_dim][a_dim], p_3[a_dim][a_dim], p_4[a_dim][a_dim];

	extern double r_0_l[a_dim][a_dim], r_0_u[a_dim][a_dim], r_1_l[a_dim][a_dim], r_1_u[a_dim][a_dim], r_2_l[a_dim][a_dim], r_2_u[a_dim][a_dim], r_3_l[a_dim][a_dim], r_3_u[a_dim][a_dim], r_4_l[a_dim][a_dim], r_4_u[a_dim][a_dim];

	extern double q_0[a_dim][a_dim], q_1[a_dim][a_dim], q_2[a_dim][a_dim], q_3[a_dim][a_dim], q_4[a_dim][a_dim];

	extern double p_sum[a_dim][a_dim];
	
// INITIATION OF THE PROCEDURE ------------------------------------------------------------------------------------------------------------------------------------------------------

	// compute sum of probabilities
	p_sum[i][j] = p_0[i][j] + p_1[i][j] + p_2[i][j] + p_3[i][j]+ p_4[i][j];


	// compute normalized probabilities
	q_0[i][j]= p_0[i][j]/p_sum[i][j];
	q_1[i][j]= p_1[i][j]/p_sum[i][j];
	q_2[i][j]= p_2[i][j]/p_sum[i][j];
	q_3[i][j]= p_3[i][j]/p_sum[i][j];
	q_4[i][j]= p_4[i][j]/p_sum[i][j];


  
	// determine upper and lower bands for probability extensions
	r_0_l[i][j]= 0;
	r_0_u[i][j]= q_0[i][j];

	r_1_l[i][j]= q_0[i][j];
	r_1_u[i][j]= q_0[i][j] + q_1[i][j];

	r_2_l[i][j]= q_0[i][j] + q_1[i][j];
	r_2_u[i][j]= q_0[i][j] + q_1[i][j] + q_2[i][j];

	r_3_l[i][j]= q_0[i][j] + q_1[i][j] + q_2[i][j];
	r_3_u[i][j]= q_0[i][j] + q_1[i][j] + q_2[i][j] + q_3[i][j];
   
	r_4_l[i][j]= q_0[i][j] + q_1[i][j] + q_2[i][j] + q_3[i][j];
	r_4_u[i][j]= q_0[i][j] + q_1[i][j] + q_2[i][j] + q_3[i][j] + q_4[i][j];

};
// ==================================================================================================================================================================================
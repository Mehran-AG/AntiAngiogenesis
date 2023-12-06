#include "ECProliferation.h"

#include "dimension.h"

bool ECProliferation( int i, int j, cVessel& v ) {

	extern double e[a_dim][a_dim];

	extern double dim_t;

	extern double dt;

	bool prol = true;

	double I_0 = 1.99E-9; // (M)

	double IC_50 = 2.288E-8; // (M)

	double eps_max = 1.;

	double alpha_r = 5.56E-5; // (1/sec)

	double alpha_d = 1.54E-9; // (1/sec) // 5.56E-6 (1/h)

	double p_d = 14.; // parent vessel diameter

	double pr = 0.;

	double c_star = 8.477E-12;

	double c_0 = 4.2385E-11;

	double prl = v.GetPrln();
	
	if ( prl >= 0.039 ) {
	
		prol = false;

		prl -= 0.039;

		v.SetPrln( prl );

	}
	else {

		pr = ( alpha_r * dt * 86400 * dim_t ) * ( 1 - ( v.GetDiameter() / p_d ) ) * ( v.GetDiameter() / p_d ) * ( 1 - ( ( eps_max * e[i][j] * I_0  ) / ( IC_50 + I_0 * e[i][j] ) ) ) - ( alpha_d * dt * 86400 * dim_t );

		prl += pr;

		if ( prl >= 0.039 ) {

			prol = false;

			prl -= 0.039;

		};

		v.SetPrln( prl );

	};

	return prol;

};
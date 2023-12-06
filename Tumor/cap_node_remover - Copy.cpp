#include "cap_node_remover.h"

#include "position_finder.h"

void cap_node_remover() {

	printf ( "\nENTERED CAP NODE REMOVER" );

	void DeleteLastVessel( std::vector<vessel>&, node& );

	extern unsigned int cn;

	extern unsigned int nnum;

	extern std::vector<vessel> vessels;

	extern std::vector<vessel> vessels_backup;
	
	copy ( vessels.begin(), vessels.end(), back_inserter (vessels_backup) );
	
	extern std::vector<node> nodes;

	extern std::vector<node> nodes_backup;

	copy ( nodes.begin(), nodes.end(), back_inserter(nodes_backup) );

	unsigned int d_B_node = 0;

	unsigned int n_d_indicator = 0;

	bool search_finish = false;

	unsigned int r_cap = 0;

	unsigned int node_number;

	for ( auto i = vessels.begin(); i != vessels.end(); i++ ) {


		i->backup_values();

	};

	for ( std::vector<node>::iterator i = nodes.begin(); i < nodes.end(); i++ ) {

		i->backup_values();

	};

	while ( search_finish != true ) {

		search_finish = true;

		for ( auto i = vessels.begin(); i < vessels.end(); ++i ) { // for1
			printf ( "\nentered vessel number %u", i->GetNumber() );
			if ( ( i->GetEndStatus() == 1 ) || ( i->GetEndStatus() == 4 ) ) { // if1

				search_finish = false;

				printf ( "\nvessel %u is removed", i->GetNumber() );

				if ( i->GetEndStatus() == 1 )
					i->SetEndStatus( 2 );

				if ( i->GetEndStatus() == 4 )
					i->SetEndStatus( 5 );

				node_number = position_finder ( nodes, i->GetStartingNode() );

				printf ( "\nnode number: %u", node_number );

				nodes[node_number].DeleteOutputVessel( i->GetPlaceOnStartingNode() );

				i = vessels.erase ( i );

				--i;

			}; // end of if1

		}; // end of for1

		for ( auto i = nodes.begin(); i < nodes.end(); ++i ) { // for2

			if ( i->GetNumberOfBranches() == 1 ) {

				printf ( "\nentered if branches and branches is: %u", i->GetNumberOfBranches() );

				printf ( "\nentered if branches node number: %u", i->GetNumber() );

				i->DeleteBranches();

				search_finish = false;

				DeleteLastVessel( vessels, *i );

				i = nodes.erase ( i );

				--i;

			};

		}; // end of for2

	}; // end of while

	printf ( "\ncap node remover ended" );

};





void DeleteLastVessel( std::vector<vessel>& v, node& n ) {

	if ( n.inlet == 1 ) {

		if ( n.inlet1 >= 0 ) {

			printf ( "\nentered if inlet1" );

			printf ( "\nremoved vessel is %u", n.inlet1 );

			unsigned int vv = position_finder ( v, n.inlet1 );

			v[vv].SetEndStatus( 4 );

			n.inlet1 = -1;

			n.inlet --;

		}

		else if ( n.inlet2 >= 0 ) {

			printf ( "\nentered if inlet2");

			printf ( "\nremoved vessel is %u", n.inlet2 );

			unsigned int vv = position_finder ( v, n.inlet2 );

			v[vv].SetEndStatus( 4 );

			n.inlet2 = -1;

			n.inlet --;

		};

	};

	if ( n.outlet == 1 ) {

		if ( n.outlet1 >= 0 ) {

			printf ( "\nentered if outlet1");

			printf ( "\nremoved vessel is %u", n.outlet1 );

			unsigned vv = position_finder ( v, n.outlet1 );

			v[vv].SetEndStatus( 4 );

		}

		else if ( n.outlet2 >= 0 ) {

			printf ( "\nentered if outlet2");

			printf ( "\nremoved vessel is %u", n.outlet2 );

			unsigned vv = position_finder ( v, n.outlet2 );

			v[vv].SetEndStatus( 4 );

		};

	};

};
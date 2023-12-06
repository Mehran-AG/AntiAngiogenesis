#include "ConcatenateVessels.h"

#include "dimension.h"

#include "PositionFinder.h"

#include <vector>

#include <fstream>

#include <iostream>

#include "ChangeProhibitedVessels.h"

#include "RemoveNodeVessel.h"

#include "Concatenators.h"


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// THE MAIN FUNCTION USED TO DO CONCATENATION ON VESSEL SEGMENTS --------------------------------------------------------------------------------------------------------------------
// THIS FUNCTION GETS THE NODE AS INPUT AND CONCATENATES ITS VESSELS ----------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ConcatenateVessels( cNode& n ) {

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	extern std::vector<int> sprouts;

	extern std::ofstream printer;

	extern bool uncheckedVEGF[a_dim];

	extern bool available_spots[a_dim];

	extern int distance;

	unsigned n_position;

	if ( sprouts.size() == 1 ) return;

	try {

		n_position = PositionFinder( nodes, n.GetIDNumber() );

	}

	catch ( int wrong ) {

		printf( "\nIDENTITY NUMBER OF NODES CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

		system("pause");

	};

	if ( n_position == 0 ) {

		RemoveNodeVessel( nodes[0] );

		int point = sprouts[0];

		for ( int counter = (point - distance); counter < (point + distance); ++counter ) {

			uncheckedVEGF[counter] = 1;

			available_spots[counter] = 0;

		};

		sprouts.erase( sprouts.begin() );

	}

	else if ( n_position == ( sprouts.size() - 1 ) ) {

		RemoveNodeVessel( nodes[sprouts.size()-1] );

		int point = sprouts[sprouts.size()-1];

		for ( int counter = (point - distance); counter < (point + distance); ++counter ) {

			uncheckedVEGF[counter] = 1;

			available_spots[counter] = 0;

		};

		sprouts.erase( sprouts.begin() + sprouts.size() - 1 );

	}
		
	else if ( n_position < ( sprouts.size() - 1 ) ) {

		// outlet vessel's identity
		int outlet;

		if ( n.GetOutletVesselNumber( 1 ) >= 0 ) {

			outlet = n.GetOutletVesselNumber( 1 );

		}

		else if ( n.GetOutletVesselNumber( 2 ) >= 0 ) {

			outlet = n.GetOutletVesselNumber( 2 );

		}

		else if ( n.GetOutletVesselNumber( 3 ) >= 0 ) {

			outlet = n.GetOutletVesselNumber( 3 );

		};

		// inlet vessel's identity
		int inlet;

		if ( n.GetInletVesselNumber( 1 ) >= 0 ) {

			inlet = n.GetInletVesselNumber( 1 );

		}

		else if ( n.GetInletVesselNumber( 2 ) >= 0 ) {

			inlet = n.GetInletVesselNumber( 2 );

		}

		else if ( n.GetInletVesselNumber( 3 ) >= 0 ) {

			inlet = n.GetInletVesselNumber( 3 );

		};

		int inlet_num, outlet_num;

		try {

			// outlet vessel's position in the vector
			outlet_num = PositionFinder( vessels, outlet );

			// inlet vessel's position in the vector
			inlet_num = PositionFinder( vessels, inlet );

		}

		catch ( int wrong ) {

			printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

			system("pause");

		};

		// assigning new names for the vessels
		cVessel& main = vessels[inlet_num];

		cVessel& secondary = vessels[outlet_num];

		// identity of end node is get to remove secondary vessel from it
		int e_node_identity = secondary.GetEndNode();

		int e_node_pos;
				
		try {
				
			e_node_pos = PositionFinder( nodes, e_node_identity );

		}

		catch ( int wrong ) {

			printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

			system("pause");

		};

		// specifications of the secondary vessel is copied to main vessel
		main.CopyEndNode( secondary );

		int place = secondary.GetPlaceOnEndingNode();

		nodes[e_node_pos].ReplaceInletVessel( main.GetIDNumber(), place );

		// length and age of the concatenated vessel is assigned
		int total_unit_length = main.GetUnitLength() + secondary.GetUnitLength();

		int age = main.GetAge() + secondary.GetAge();

		main.SetVesselUnitLength( total_unit_length );

		main.SetAge( age );

		size_t c;

		for ( c = 0; c < sprouts.size(); ++c ) {

			if ( n.GetYPosition() == sprouts[c] ) break;

		};

		int point = sprouts[c];

		for ( int counter = (point - distance); counter < (point + distance); ++counter ) {

			uncheckedVEGF[counter] = 1;

			available_spots[counter] = 0;

		};

		sprouts.erase( sprouts.begin() + c );

		int removed_position;
			
		try {
			
			removed_position = PositionFinder( nodes, n.GetIDNumber() );

		}

		catch ( int wrong ) {

			printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

			system("pause");

		};

		nodes.erase( nodes.begin() + removed_position );

		vessels.erase( vessels.begin() + outlet_num );

	}

	else {

		int vessel1_num, vessel2_num;

		if ( n.GetNumberOfInletVessels() == 2 ) { // if1

			// ************************************************************************************
			// *              main vessel          node       secondary vessel     start_node     *
			// *    o------------------------------>o<-------------------------------o            *
			// *                           inlet->     <-inlet                                    *
			// ************************************************************************************

			n.Print( printer );

			if ( n.GetInletVesselNumber( 1 ) >= 0 ) {

				try {

					// since both vessels are inlets, their identity numbers are achieved by getting both inlets of the node
					vessel1_num = PositionFinder( vessels, n.GetInletVesselNumber( 1 ) );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				if ( n.GetInletVesselNumber( 2 ) >= 0 ) {

					try {

						// since both vessels are inlets, their identity numbers are achieved by getting both inlets of the node
						vessel2_num = PositionFinder( vessels, n.GetInletVesselNumber( 2 ) );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

						system("pause");

					};

				}

				else if (n.GetInletVesselNumber( 3 ) >= 0 ) {

					try {

						// since both vessels are inlets, their identity numbers are achieved by getting both inlets of the node
						vessel2_num = PositionFinder( vessels, n.GetInletVesselNumber( 3 ) );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

						system("pause");

					};

				};

			}

			else {

				try {

					// since both vessels are inlets, their identity numbers are achieved by getting both inlets of the node
					vessel1_num = PositionFinder( vessels, n.GetInletVesselNumber( 2 ) );
					vessel2_num = PositionFinder( vessels, n.GetInletVesselNumber( 3 ) );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

			};

			// identity of starting node of secondary vessel is 
			int s_node_identity = vessels[vessel2_num].GetStartNode();
		
			// position of node in the vector
			int s_node_pos;

			try {

				s_node_pos = PositionFinder( nodes, s_node_identity );

			}

			catch ( int wrong ) {

				printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

				system("pause");

			};

			// if s_node of secondary vessel has two inlets, so we cannot assign one more inlet to it
			// therefore we change places of main and secondary vessels
			if ( nodes[s_node_pos].GetNumberOfInletVessels() > 1 ) {

				int s_node_identity_t = vessels[vessel1_num].GetStartNode();

				try {

					s_node_pos = PositionFinder( nodes, s_node_identity_t );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				if ( nodes[s_node_pos].GetNumberOfInletVessels() > 2 ) goto here;

				int temp;

				temp = vessel2_num;

				vessel2_num = vessel1_num;

				vessel1_num = temp;

				s_node_identity = vessels[vessel2_num].GetStartNode();

			};

			here:

			// vessels are given new names to make the implementations easy
			cVessel& main = vessels[vessel1_num];

			cVessel& secondary = vessels[vessel2_num];

			// assigning new name to the starting node
			cNode& start_node = nodes[s_node_pos];

			main.Print( printer );

			secondary.Print( printer );

			start_node.Print( printer );

			// now it is time to remove the secondary vessel from the node
			start_node.RemoveOutletVessel( secondary.GetPlaceOnStartingNode() );

			// main vessel is assigned to the starting node of the secondary vessel and its place is stored in a variable
			int place = start_node.AssignInletVesselGetPlace( main.GetIDNumber() );

			// place of the main vessel on its ending node is assigned
			main.AssignPlaceOnEndingNode( place );

			// ending node of the vessel is updated
			main.AssignEndingNode( s_node_identity );

			// position of the node is defined to start concatenation from that point
			int x = n.GetXPosition();
			int y = n.GetYPosition();

			// first move in concatenation of vessel segments is different, so this variable is defined for making first move different from the others
			bool indicator = true;

			// concatenation starts based on the inlets and outlets
			InletInletConcatenator( main, secondary, x, y, indicator );

			// total unit length and ages are defined to assign it to the remaining vessel
			int total_unit_length = main.GetUnitLength() + secondary.GetUnitLength();

			int age = main.GetAge() + secondary.GetAge();

			main.SetVesselUnitLength( total_unit_length );

			main.SetAge( age );

			main.Print( printer );

			int removed_position;

			try {

				// position of the current node to remove it from the node vector
				removed_position = PositionFinder( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

				system("pause");

			};

			nodes.erase( nodes.begin() + removed_position );

			// changning the mother vessel of the vessel whose mother vessels were secondary vessel to main vessel
			ChangeProhibitedVessels( vessels, main, secondary );

			try {
		
				// getting the position of secondary vessel in the vector to remove it
				removed_position = PositionFinder( vessels, secondary.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nIDENTITY NUMBER OF VESSEL CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

				system("pause");

			};

			vessels.erase( vessels.begin() + removed_position );

		}

		else if ( ( n.GetNumberOfInletVessels() == 1 ) && ( n.GetNumberOfOutletVessels() == 1 ) ) {

			//  *******************************************************************************************************
			//  *                main vessel              node          secondary vessel          e_node              *
			//  *      o---------------------------------->o--------------------------------------->o                 *
			//  *                                inlet->     ->outlet                                                 *
			//  *******************************************************************************************************
		

			// outlet vessel's identity
			int outlet;

			if ( n.GetOutletVesselNumber( 1 ) >= 0 ) {

				outlet = n.GetOutletVesselNumber( 1 );

			}

			else if ( n.GetOutletVesselNumber( 2 ) >= 0 ) {

				outlet = n.GetOutletVesselNumber( 2 );

			}

			else if ( n.GetOutletVesselNumber( 3 ) >= 0 ) {

				outlet = n.GetOutletVesselNumber( 3 );

			};

			// inlet vessel's identity
			int inlet;

			if ( n.GetInletVesselNumber( 1 ) >= 0 ) {

				inlet = n.GetInletVesselNumber( 1 );

			}

			else if ( n.GetInletVesselNumber( 2 ) >= 0 ) {

				inlet = n.GetInletVesselNumber( 2 );

			}

			else if ( n.GetInletVesselNumber( 3 ) >= 0 ) {

				inlet = n.GetInletVesselNumber( 3 );

			};

			int inlet_num, outlet_num;

			try {

				// outlet vessel's position in the vector
				outlet_num = PositionFinder( vessels, outlet );

				// inlet vessel's position in the vector
				inlet_num = PositionFinder( vessels, inlet );

			}

			catch ( int wrong ) {

				printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

				system("pause");

			};

			// assigning new names for the vessels
			cVessel& main = vessels[inlet_num];

			cVessel& secondary = vessels[outlet_num];

			main.Print( printer );

			secondary.Print( printer );

			// since we have outlet vessels, it is checked to see if it is ended or not
			if ( secondary.GetOutletStatus() == true ) {

				// the vessel is not ended since its outlet status is open
				main.SetOutletStatus( true );

				// getting position of the node to start concatenation
				int x = n.GetXPosition();

				int y = n.GetYPosition();

				bool indicator = true;

				InletOutletConcatenator( main, secondary, x, y, indicator );

				// getting coordinates of Tip Endothelial Cell of secondary vessel to assign it to main vessel
				x = secondary.Get_X_CoordianteOfTEC();

				y = secondary.Get_Y_CoordianteOfTEC();

				main.SetTipCellPosition( x, y );

				main.AssignPlaceOnEndingNode( 0 );

				main.AssignEndingNode( 0 );

			}

			else if ( secondary.GetOutletStatus() == false ) {

				// the vessel is ended
				int x = n.GetXPosition();

				int y = n.GetYPosition();

				bool indicator = true;

				InletOutletConcatenator( main, secondary, x, y, indicator );

				// identity of end node is get to remove secondary vessel from it
				int e_node_identity = secondary.GetEndNode();

				int e_node_pos;
				
				try {
				
					e_node_pos = PositionFinder( nodes, e_node_identity );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				// specifications of the secondary vessel is copied to main vessel
				main.CopyEndNode( secondary );

				int place = secondary.GetPlaceOnEndingNode();

				nodes[e_node_pos].ReplaceInletVessel( main.GetIDNumber(), place );

			};

			// length and age of the concatenated vessel is assigned
			int total_unit_length = main.GetUnitLength() + secondary.GetUnitLength();

			int age = main.GetAge() + secondary.GetAge();

			main.SetVesselUnitLength( total_unit_length );

			main.SetAge( age );

			main.Print( printer );

			// changning the mother vessel of the vessel whose mother vessels were secondary vessel to main vessel
			ChangeProhibitedVessels( vessels, main, secondary );

			int removed_position;
			
			try {
			
				removed_position = PositionFinder( nodes, n.GetIDNumber() );

			}

			catch ( int wrong ) {

				printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

				system("pause");

			};

			nodes.erase( nodes.begin() + removed_position );

			vessels.erase( vessels.begin() + outlet_num );

		}

		else if ( n.GetNumberOfOutletVessels() == 2 ) {

			//  *********************************************************************************************
			//  *                main vessel          node    secondary vessel                              *
			//  *         o<---------------------------o------------------------------->o                   *
			//  *                            outlet<-     ->outlet                ending node               *
			//  *********************************************************************************************


			if ( n.GetOutletVesselNumber( 1 ) >= 0 ) {

				try {

					// identity number of vessels
					vessel1_num = PositionFinder( vessels, n.GetOutletVesselNumber( 1 ) );


				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				if ( n.GetOutletVesselNumber( 2 ) >= 0 ) {

					try {

						// identity number of vessels
						vessel2_num = PositionFinder( vessels, n.GetOutletVesselNumber( 2 ) );


					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

						system("pause");

					};

				}

				else {

					try {

						// identity number of vessels
						vessel2_num = PositionFinder( vessels, n.GetOutletVesselNumber( 3 ) );


					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF VESSELS CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

						system("pause");

					};

				};


			};

			// since both vessels are outlets, it is checked to see if they are ended
			if ( vessels[vessel1_num].GetOutletStatus() == true ) {

				// new names are assigned to vessels
				cVessel& main = vessels[vessel1_num];

				cVessel& secondary = vessels[vessel2_num];

				main.Print( printer );

				secondary.Print( printer );

				// identity of ending node of secondary vessel is defined
				int e_node_identity = secondary.GetEndNode();

				int e_node_pos;

				try {

					e_node_pos = PositionFinder( nodes, e_node_identity );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				cNode& ending_node = nodes[e_node_pos];

				// if the number of outlet vessels to the ending node of secondary vessel has 2 outlet vessels
				// -> it is not possible to assign new outlet to it
				if ( ending_node.GetNumberOfOutletVessels() > 1 ) {
				
					printf( "\nOOOPS, TWO OUTLETS TWO THE NODE" );

					system("pause");

					exit(2);

				};

				// getting the position of node to start concatenation
				int x = n.GetXPosition();

				int y = n.GetYPosition();

				bool indicator = true;

				OutletOutletConcatenator( main, secondary, x, y, indicator );

				// place of secondary vessel on its ending node is got to remove it
				int place = secondary.GetPlaceOnEndingNode();

				ending_node.RemoveInletVessel( place );

				// main vessel is assigned to node and its place is determined
				place = ending_node.AssignOutletVesselGetPlace( main.GetIDNumber() );

				// after getting place, it is assigned to the vessel as its plcae on starting node
				main.AssignPlaceOnStartingNode( place );

				main.Print( printer );

				// changning the mother vessel of the vessel whose mother vessels were secondary vessel to main vessel
				ChangeProhibitedVessels( vessels, main, secondary );

				int removed_position;

				try {

					removed_position = PositionFinder( nodes, n.GetIDNumber() );

				}

				catch (int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				nodes.erase( nodes.begin() + removed_position );

				vessels.erase( vessels.begin() + vessel2_num );

			}

			else if ( vessels[vessel2_num].GetOutletStatus() == true ) {

				// if outlet status of first chosen vessel is closed, the other one's is checked
				cVessel& main = vessels[vessel2_num];

				cVessel& secondary = vessels[vessel1_num];

				main.Print( printer );

				secondary.Print( printer );

				// ending node identity of the secondary vessel is determined
				int e_node_identity = secondary.GetEndNode();

				int e_node_pos;

				try {

					e_node_pos = PositionFinder( nodes, e_node_identity );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				cNode& ending_node = nodes[e_node_pos];

				if ( ending_node.GetNumberOfOutletVessels() > 1 ) {
				
					printf( "\nOOOPS, TWO OUTLETS TWO THE NODE\n" );

					system("pause");

					exit(2);

				};

				// position of the current node is determined to start concatenation
				int x = n.GetXPosition();

				int y = n.GetYPosition();

				bool indicator = true;

				OutletOutletConcatenator( main, secondary, x, y, indicator );

				// place of the vessel on ending node is determined to remove it
				int place = secondary.GetPlaceOnEndingNode();

				ending_node.RemoveInletVessel( place );

				// main vessel is assigned to ending node of secondary vessel
				place = ending_node.AssignOutletVesselGetPlace( main.GetIDNumber() );

				main.AssignPlaceOnStartingNode( place );

				// changning the mother vessel of the vessel whose mother vessels were secondary vessel to main vessel
				ChangeProhibitedVessels( vessels, main, secondary );

				main.Print( printer );

				int removed_position;

				try {

					removed_position = PositionFinder( nodes, n.GetIDNumber() );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				nodes.erase( nodes.begin() + removed_position );

				vessels.erase( vessels.begin() + vessel1_num );

			}

			else {

				// identity of ending node of secondary vessel is achieved
				int e_node_identity = vessels[vessel2_num].GetEndNode();

				int e_node_pos;

				try {

					e_node_pos = PositionFinder( nodes, e_node_identity );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				// if the other vessel's ending node's outlet vessels are 2, we cannot assign new outlet vessel to it
				// -> so we have to change main and secondary vessels
				if ( nodes[e_node_pos].GetNumberOfOutletVessels() > 1 ) {

					int e_node_identity_t = vessels[vessel1_num].GetEndNode();

					try {

						e_node_pos = PositionFinder( nodes, e_node_identity_t );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

						system("pause");

					};

					if ( nodes[e_node_pos].GetNumberOfOutletVessels() > 2 ) goto here2;

					int temp;

					temp = vessel2_num;

					vessel2_num = vessel1_num;

					vessel1_num = temp;

					e_node_identity = vessels[vessel2_num].GetEndNode();

					try {

						e_node_pos = PositionFinder( nodes, e_node_identity );

					}

					catch ( int wrong ) {

						printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

						system("pause");

					};

				};

				here2:

				// assigning new names to the vessels
				cVessel& main = vessels[vessel1_num];

				cVessel& secondary = vessels[vessel2_num];

				cNode& ending_node = nodes[e_node_pos];

				main.Print( printer );

				secondary.Print( printer );

				ending_node.RemoveInletVessel( secondary.GetPlaceOnEndingNode() );

				int place = ending_node.AssignOutletVesselGetPlace( main.GetIDNumber() );

				main.AssignPlaceOnStartingNode( place );

				main.AssignStartingNode( e_node_identity );

				int x = n.GetXPosition();

				int y = n.GetYPosition();

				bool indicator = true;

				OutletOutletConcatenator( main, secondary, x, y, indicator );

				ChangeProhibitedVessels( vessels, main, secondary );

				main.Print( printer );

				int removed_position;

				try {

					removed_position = PositionFinder( nodes, n.GetIDNumber() );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF NODE CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				nodes.erase( nodes.begin() + removed_position );

				try {

					removed_position = PositionFinder( vessels, secondary.GetIDNumber() );

				}

				catch ( int wrong ) {

					printf( "\nIDENTITY NUMBER OF VESSEL CANNOT BE FOUND IN CONCATENATION AND NO. IS %d", wrong );

					system("pause");

				};

				vessels.erase( vessels.begin() + removed_position );

			};

		};

	};

};
// ==================================================================================================================================================================================
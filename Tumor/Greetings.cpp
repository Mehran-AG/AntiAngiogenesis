#include "Greetings.h"

#include "dimension.h"

#include <iostream>

#include <string>

#include <stdlib.h>

using namespace std;

void Greetings() {

	string name;

	cout << "PLEASE ENTER YOUR NAME: ";

	cin >> name;

	//for ( int i = 0; i < name.length(); ++i )
		//name[i] = toupper( name[i] );

	name[0] = toupper( name[0] );

	for ( size_t i = 1; i < name.length(); ++i )
		name[i] = tolower( name[i] );

	system("CLS");

	string sentence[5];

	sentence[0] = "HELLO DEAR " + name + '!' + " THIS CODE IS DEVELOPED TO SIMULATE A VASCULAR TUMOR GROWTH";

	sentence[1] = "THE MODEL MAKES USE OF A DISCRETE ANGIOGENESIS MODEL";

	sentence[2] = "THE SIMULATION DOMAIN IS A 4 MM * 4 MM SQUARE";

	sentence[3] = "THANKS A LOT, MEHRAN AKBARPOUR GHAZANI";

	sentence[4] = "IF YOU WANT TO CONTINUE PLEASE PRESS \"ENTER\"";

	int max = 0;

	for ( int i = 0; i < 5; ++i ) {

		int size = 0;

		size = sentence[i].size();

		if ( size > max ) max = size;

	};

	char star = '*';

	string first( max + 10 , star );

	first = first;

	cout << "\t" << first << endl;

	string second( max + 8, ' ' );

	second = star + second;

	second = second + star;

	second = second;

	cout << "\t" << second << endl;

	for ( int i = 0; i < 5; ++i ) {

		int size = max + 8;

		int free = ( size - sentence[i].size() ) / 2;

		string space1( free, ' ' );

		string space2;

		if ( ( ( size - sentence[i].size() ) % 2 ) != 0 )
			space2 = space1 + ' ' ;
		else
			space2 = space1;

		string line = star + space1 + sentence[i] + space2 + star;

		cout << "\t" << line << endl;

	};

	cout << "\t" << second << endl;

	cout << "\t" << first << endl;

};
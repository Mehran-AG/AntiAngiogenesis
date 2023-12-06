#pragma once

#include <vector>


template<typename T>

int PositionFinder( std::vector<T>& v, int pp ) {

	size_t i;

	try {

		for ( i = 0; i < v.size(); ++i ) {
			
			if ( v[i].GetIDNumber() == pp ) {

				return i;

			};

		};

		if ( i == v.size() ) throw pp;

	}

	catch ( double ) {


	};

	return -1;

};
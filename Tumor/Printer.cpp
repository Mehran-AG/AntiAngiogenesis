#include "Printer.h"

#include "dimension.h"

#include "cVessel.h"

#include "cNode.h"

void Printer() {

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	std::ofstream writer ( "D:\\check.txt" );

	for ( auto i = vessels.begin(); i < vessels.end(); ++i ) {

		i->Print(writer);

	};

	for ( auto i = nodes.begin(); i < nodes.end(); ++i ) {

		i->Print(writer);

	};

};

void Printer2() {

	extern std::vector<cVessel> vessels;

	extern std::vector<cNode> nodes;

	std::ofstream writer ( "E:\\check.txt" );

	for ( auto i = vessels.begin(); i < vessels.end(); ++i ) {

		i->Print(writer);

	};

	for ( auto i = nodes.begin(); i < nodes.end(); ++i ) {

		i->Print(writer);

	};

};
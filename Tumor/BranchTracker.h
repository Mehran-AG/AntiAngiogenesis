#pragma once

#include "cVessel.h"

void BranchTracker( int&, int&, cVessel&, cVessel& );

void BranchTracker( int, int, cVessel&, int& );

void BranchTracker( cVessel&, int&, int&, std::vector<int>&, int&, double& );

void BranchTracker( cVessel&, int&, int&, int&, int& );
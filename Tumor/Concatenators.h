#pragma once

#include "cVessel.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// DECLARATION OF FUNCTIONS ONLY USED IN THIS FILE. THESE FUNCTIONS CONCATENATE SEGMENTS BASED ON THEIR STATUS ON THE NODE THAT IS GOING TO BE REMOVED -------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void InletInletConcatenator( cVessel&, cVessel&, int, int, bool );

void InletOutletConcatenator( cVessel&, cVessel&, int, int, bool );

void OutletOutletConcatenator( cVessel&, cVessel&, int, int, bool );
// ==================================================================================================================================================================================
#pragma once

#include <iostream>

#include <fstream>

#include <vector>

#include <conio.h>

#include "cVessel.h"

void SeparateOutputWriter();

void OutputWriter();

void OutputWriter( int );

void OutputWriter( int, std::vector<cVessel>& );

void CurveDrawer( unsigned );
#pragma once
#ifndef SOLVER_H
#define SOLVER_H
#include "system.h"
#include "point.h"
class Solver
{
private:
	System S;
public:
	Solver(System _s): S(_s) {}
	double solve(Point x);
};

#endif
